#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_malloc.h"

#define HEADER_SIZE sizeof(size_t) * 3

static FreeBlock *head_ptr;
static void *brk_p; // Указатель (program break)

void *my_malloc(size_t size)
{
    // Свободный блоков нет
    if (head_ptr == NULL)
    {
        FreeBlock* tmp_p = NULL;
        void *ptr;
        // Увеличиваем размер 
        ptr = sbrk(CHUNK_SIZE);

        if (ptr == (void *) - 1)
        {
            perror("sbrk");
            exit(EXIT_FAILURE);
        }

        // Получаем позицию крайней точки программы (program break)
        brk_p = sbrk(0);

        // Записываем данные заголовка free в кучу и сохраняем head_ptr
        head_ptr = (FreeBlock*) ptr;
        head_ptr->next = NULL;
        head_ptr->prev = NULL;
        head_ptr->size = CHUNK_SIZE - sizeof(size_t);
    }

    // Выравниваем size
    size = size % sizeof(size_t) == 0 ? size : size + (sizeof(size_t) - size % sizeof(size_t));

    if (size < sizeof(size_t) * 2) 
    {
        size = sizeof(size_t) * 2;
    }

    // Ищем подходящий свободный блок
    FreeBlock *tmp = head_ptr, *ptr_next;
    void *ret;

    do
    {
        if (size > tmp->size)
        {
            // Не нашли подходящий
            if (tmp->next == NULL)
            {
                void *ptr;
                size_t heap_size_add = CHUNK_SIZE * ((size + HEADER_SIZE) / CHUNK_SIZE + 1);

                // Увеличиваем размер
                ptr = sbrk(heap_size_add);

                if (ptr == (void *) - 1)
                {
                    perror("sbrk");
                    exit(EXIT_FAILURE);
                }
                
                // Получаем позицию крайней точки программы (program break)
                brk_p = sbrk(0);

                FreeBlock *new_block = (FreeBlock *)ptr;
                new_block->size = heap_size_add - sizeof(size_t);
                new_block->prev = tmp;
                new_block->next = NULL;

                tmp->next = new_block; // Привязываем его в конец списка
                tmp = new_block;       // Теперь работаем с ним, цикл сам пойдет по ветке else
                continue;
            }
        }
        else
        {
            // Нашли подходящий
            ret = (size_t *) tmp + 1;
            
            // Влезает впритык
            if (tmp->size - size <= HEADER_SIZE)
            {

                // Единственный свободный блок
                if (tmp->prev == NULL && tmp->next == NULL)
                {
                    // Зануляем head и в следующем вызове malloc куча увеличиться
                    head_ptr = NULL;
                }
                else if (tmp->prev == NULL)
                {
                    // Свободный блок в начале, смещаем голову
                    head_ptr = head_ptr->next;
                }
                else
                {
                    // В середине
                    tmp->prev->next = tmp->next;

                    if (tmp->next != NULL) 
                        tmp->next->prev = tmp->prev;
                }
                
                return ret;
            }
            // Можно поделить
            else
            {
                // Сдвигаемся на size байт вправо
                ptr_next = (FreeBlock*)((size_t*) tmp + 1 + size / sizeof(size_t));
                ptr_next->size = tmp->size - size - sizeof(size_t);
                ptr_next->next = tmp->next;
                ptr_next->prev = tmp->prev;

                if (tmp->prev != NULL)
                {
                    tmp->prev->next = ptr_next;
                }
                else
                {
                    head_ptr = ptr_next;
                }
                
                if (tmp->next != NULL) 
                {
                    tmp->next->prev = ptr_next;
                }

                tmp->size = size;
                return ret;
            }
        }

        tmp = tmp->next;
    } while (tmp != NULL);

}

void my_free(void *ptr)
{
    if (ptr == NULL) return;

    FreeBlock *p = (FreeBlock *) ((size_t *) ptr - 1);

    p->next = head_ptr;
    p->prev = NULL;
    if (head_ptr != NULL)
    {
        head_ptr->prev = p;
    }

    head_ptr = p;
}

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

void print_vector(Vector *vec)
{
    printf("Vector elements: [ ");
    // Временно создаем обертку или используем vec_get для обхода
    // Так как длина у нас внутри vector_internal.h, проверяем доступные элементы
    for (size_t i = 0; ; i++)
    {
        int *val = (int*)vec_get(vec, i);
        if (val == NULL) break;
        printf("%d ", *val);
    }
    printf("]\n");
}

int main(void)
{
    printf("=== Test: vec_create ===\n");
    Vector *vector = vec_create(sizeof(int));
    assert(vector != NULL);

    printf("\n=== Test: vec_push ===\n");
    for (int i = 10; i <= 50; i += 10)
    {
        vec_push(vector, &i);
    }
    print_vector(vector); // Ожидается: [ 10 20 30 40 50 ]

    printf("\n=== Test: vec_get ===\n");
    int *item = (int*)vec_get(vector, 2);
    if (item) printf("Element at index 2: %d\n", *item); // Ожидается: 30

    printf("\n=== Test: vec_set ===\n");
    int new_val = 99;
    vec_set(vector, 2, &new_val);
    print_vector(vector); // Ожидается: [ 10 20 99 40 50 ]

    printf("\n=== Test: vec_insert ===\n");
    int ins_val = 777;
    vec_insert(vector, 1, &ins_val); // Вставка в середину
    print_vector(vector); // Ожидается: [ 10 777 20 99 40 50 ]

    printf("\n=== Test: vec_remove ===\n");
    vec_remove(vector, 3); // Удаляем элемент по индексу 3 (99)
    print_vector(vector); // Ожидается: [ 10 777 20 40 50 ]

    printf("\n=== Test: vec_pop ===\n");
    vec_pop(vector); // Удаляем последний элемент (50)
    print_vector(vector); // Ожидается: [ 10 777 20 40 ]

    printf("\n=== Test: vec_free ===\n");
    vec_free(vector);
    printf("Vector successfully freed!\n");

    return 0;
}
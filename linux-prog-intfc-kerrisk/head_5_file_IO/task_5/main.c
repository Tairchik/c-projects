#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    char *filename = "test.txt";
    int newfd, oldfd, newfl, oldfl;
    off_t newoff, oldoff;

    oldfd = open(filename, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0666);
    if (oldfd == -1)
    {
        if (errno != EEXIST)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        oldfd = open(filename, O_RDWR | O_TRUNC);
    }

    // Дублируем дескриптор oldfd

    newfd = dup(oldfd);
    if (newfd == -1)
    {
        perror("dup");
        exit(EXIT_FAILURE);
    }

    // Проверка совместного использования файлового смещения
    // 1) Сместим указатель от начала на 4 байта
    oldoff = lseek(oldfd, 4, SEEK_SET);
    if (oldoff == -1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    
    // 2) Проверим сместился ли указатель у второго дескриптора
    newoff = lseek(newfd, 0, SEEK_CUR);
    if (newoff == -1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    
    printf("Новое смещение: %ld\nСтарое смещение: %ld\n", newoff, oldoff);
    if (newoff == oldoff)
        printf("Смещения одинаковы.\n\n");
    else 
        printf("Смещения разные.\n\n");

    // Проверка флагов открытого файла
    // 1) Изменим флаги у старого дескриптора
    oldfl = fcntl(oldfd, F_GETFL);
    printf("Маска до изменения флагов: %d\n", oldfl);

    fcntl(oldfd, F_SETFL, O_APPEND | oldfl);

    // 2) Сравним флаги
    newfl = fcntl(newfd, F_GETFL);
    oldfl = fcntl(oldfd, F_GETFL);

    printf("Маска флагов состояния нового дескриптора: %d\nМаска флагов состояния старого дескриптора: %d\n", newfl, oldfl);
    if (newfl == oldfl)
        printf("Маски одинаковы.\n");
    else 
        printf("Маски разные.\n");

    close(newfd);
    close(oldfd);
    unlink(filename);
    exit(EXIT_SUCCESS);
}
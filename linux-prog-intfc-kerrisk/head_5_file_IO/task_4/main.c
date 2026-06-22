#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "my_dup.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Неверный формат. Формат: [filename] [op]\n");
        fprintf(stderr, "[op] - принимает значение 1 или 2, для использования dup и dup2 соответственно\n");
        exit(EXIT_FAILURE);
    }

    char *filename;
    int op = 0, fd, newfd, ret, test;

    filename = argv[1];
    op = atoi(argv[2]);

    if (op != 1 && op != 2)
    {
        fprintf(stderr, "Неверный формат. Формат: [filename] [op]\n");
        fprintf(stderr, "[op] - принимает значение 1 или 2, для использования dup и dup2 соответственно\n");
        exit(EXIT_FAILURE);
    }

    fd = open(filename, O_RDWR | O_CREAT | O_EXCL | O_APPEND | O_TRUNC, 0666);

    if (fd == -1)
    {
        if (errno == EEXIST)
        {
            fd = open(filename, O_RDWR | O_APPEND | O_TRUNC);
        }
        else 
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    // Записываем данные через старый дескриптор
    char *msg1 = "Old descriptor. ";
    char *msg2 = "New descriptor. ";
    ret = write(fd, msg1, strlen(msg1));

    if (ret == -1)
    {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    switch (op)
    {
    case 1:
        newfd = dup_my(fd);
        // Записываем данные через новый и старый дескриптор
        ret = write(newfd, msg2, strlen(msg2));
        ret = write(fd, msg1, strlen(msg1));

        if (ret == -1)
        {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }

        break;
    case 2:
        // Тест 1. Перезапись на неиспользуемый дескриптор 
        test = 1;
        
        newfd = 10;
        newfd = dup2_my(fd, newfd);
        if (newfd == -1)
        {
            close(fd);
            exit(EXIT_FAILURE);
        }

        ret = dprintf(newfd, "Test %d. %s", test, msg2);
        ret = dprintf(fd, "Test %d. %s", test, msg1);

        if (ret == -1)
        {
            perror("Test 1. dprintf");
            close(fd);
            exit(EXIT_FAILURE);
        }

        close(newfd);
        
        // Тест 2. Перезапись на используемый дескриптор
        // Сначала создадим его (дублируем дескриптор ошибок и потом передадим его)
        test = 2;
        newfd = dup_my(2);
        if (newfd == -1) 
        {
            perror("Test 2. dup_my");
            close(fd);
            exit(EXIT_FAILURE);
        }

        newfd = dup2_my(fd, newfd);
        if (newfd == -1) 
        {
            perror("Test 2. dup2_my");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Запись
        ret = dprintf(newfd, "Test %d. %s", test, msg2);
        ret = dprintf(fd, "Test %d. %s", test, msg1);

        if (ret == -1)
        {
            perror("Test 2. dprintf");
            close(fd);
            exit(EXIT_FAILURE);
        }

        close(newfd);

        // Тест 3. Передаем один и тот же существующий дескриптор
        test = 3;

        newfd = fd;
        newfd = dup2_my(fd, newfd);

        if (newfd == -1)
        {
            perror("Test 3. dup2_my");
            close(fd);
            exit(EXIT_FAILURE);
        }

        ret = dprintf(newfd, "Test %d. %s", test, msg2);
        ret = dprintf(fd, "Test %d. %s", test, msg1);

        if (ret == -1)
        {
            perror("Test 3. dprintf");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Тест 4. Передаем один и тот же НЕсуществующий дескриптор
        newfd = dup2_my(100, 100);
        if (newfd == -1)
        {
            if (errno == EBADF)
            {
                printf("Success\n");
                break;
            }
            perror("Test 3. dup2_my");
            close(fd);
            exit(EXIT_FAILURE);
        }
        break;
    default:
        break;
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
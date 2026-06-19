#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
    int fd;
    char* pathname = "test.txt";
    char test_str[15] = "Hello!!! ";
    char lseek_str[15] = "Hi!!! ";
    char buf[30];
    int ret;

    fd = open(pathname, O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);

    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ret = write(fd, test_str, strlen(test_str));
    if (ret == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    ret = lseek(fd, 0, SEEK_SET);
    if (ret == -1)
    {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    // Для проверки применился ли lseek прочитаем данные в буффер

    ret = read(fd, buf, sizeof(buf));
    if (ret == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buf[ret] = '\0';
    printf("String: %s\n", buf);

    ret = write(fd, lseek_str, strlen(lseek_str));
    if (ret == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
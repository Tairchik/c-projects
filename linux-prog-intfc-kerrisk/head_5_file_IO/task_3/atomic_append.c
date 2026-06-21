#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int file_write_append(char *argv[])
{
    char *filename, word = 'A';
    int bytes = 0, fd, ret;

    filename = argv[1];
    bytes = atoi(argv[2]);
    
    fd = open(filename, O_RDWR | O_CREAT | O_APPEND | O_EXCL, 0666);
    
    if (fd == -1)
    {
        if (errno == EEXIST)
        {
            fd = open(filename, O_RDWR | O_APPEND);
        }
        else 
        {
            perror("open");
            return -1;
        }
    }
    
    for (int i = 0; i < bytes; i++)
    {
        ret = write(fd, &word, 1);
        if (ret == -1)
        {
            perror("write");
            return -1;
        }
    }

    return 0;
}

int file_write_lseek(char *argv[])
{
    char *filename, word = 'A';
    int bytes = 0, fd, ret;

    filename = argv[1];
    bytes = atoi(argv[2]);
    
    fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0666);
    
    if (fd == -1)
    {
        if (errno == EEXIST)
        {
            fd = open(filename, O_RDWR);
        }
        else 
        {
            perror("open");
            return -1;
        }
    }
    
    for (int i = 0; i < bytes; i++)
    {
        lseek(fd, 0, SEEK_END);

        ret = write(fd, &word, 1);
        if (ret == -1)
        {
            perror("write");
            return -1;
        }
    }

    return 0;
}


int main(int argc, char *argv[])
{
    int ret;
    if (argc < 3 || argc > 4)
    {
        fprintf(stderr, "Неверный формат. Формат: [file name] [num-bytes]\n\tOR\n[file name] [num-bytes] x\n") ;
        exit(EXIT_FAILURE);
    }

    if (argc == 3)
        ret = file_write_append(argv);

    else if (argc == 4)
        ret = file_write_lseek(argv);
    
    if (ret == -1)
        exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}
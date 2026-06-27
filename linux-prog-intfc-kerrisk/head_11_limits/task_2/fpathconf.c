#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void /* Выводит 'msg' плюс значение fpathconf(fd, name) */
fpathconfPrint(const char *msg, int fd, int name)
{
    long lim;
    errno = 0;
    lim = fpathconf(fd, name);
    if (lim != -1)
    { /* Вызов прошел успешно, ограничение определено */
        printf("%s %ld\n", msg, lim);
    }
    else
    {
        if (errno == 0)
            /* Вызов прошел успешно, ограничение не определено */
            printf("%s (indeterminate)\n", msg);
        else /* Вызов не удался */
            perror("fpathconf");
    }
}

int main(int argc, char *argv[])
{
    fpathconfPrint("_PC_NAME_MAX: ", STDIN_FILENO, _PC_NAME_MAX);
    fpathconfPrint("_PC_PATH_MAX: ", STDIN_FILENO, _PC_PATH_MAX);
    fpathconfPrint("_PC_PIPE_BUF: ", STDIN_FILENO, _PC_PIPE_BUF);
    exit(EXIT_SUCCESS);
}
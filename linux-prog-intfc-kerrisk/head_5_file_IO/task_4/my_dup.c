#include <errno.h>
#include <unistd.h>
#include "my_dup.h"

int dup_my(int oldfd)
{
    int newfd;

    newfd = fcntl(oldfd, F_DUPFD, 0);

    return newfd;
}

int dup2_my(int oldfd, int newfd)
{
    int flags, ret, fd;

    if (fcntl(oldfd, F_GETFL) == -1) 
    {
        errno = EBADF;
        return -1;
    }

    if (oldfd == newfd)
    {
        return newfd;
    }

    // Дескриптор открыт
    if (fcntl(newfd, F_GETFL) != -1)
    {
        ret = close(newfd);
    }

    fd = fcntl(oldfd, F_DUPFD, newfd);
    
    if (fd != newfd)
    {
        close(fd);
        errno = EBUSY;
        return -1;
    }
    
    return fd;
}

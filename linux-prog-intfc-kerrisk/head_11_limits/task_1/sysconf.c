#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void /* Выводит 'msg' плюс значение sysconf() для 'name' */
sysconfPrint(const char *msg, int name)
{
    long lim;
    errno = 0;
    lim = sysconf(name);
    if (lim != -1) /* Вызов прошел успешно, ограничение определено */
    { 
        printf("%s %ld\n", msg, lim);
    }
    else
    {
        /* Вызов прошел успешно, ограничение не определено */
        if (errno == 0) 
            printf("%s (indeterminate)\n", msg);
        else /* Вызов не удался */
            perror("sysconf");
    }
}
int main(int argc, char *argv[])
{
    sysconfPrint("_SC_ARG_MAX:        ", _SC_ARG_MAX);
    sysconfPrint("_SC_LOGIN_NAME_MAX: ", _SC_LOGIN_NAME_MAX);
    sysconfPrint("_SC_OPEN_MAX:       ", _SC_OPEN_MAX);
    sysconfPrint("_SC_NGROUPS_MAX:    ", _SC_NGROUPS_MAX);
    sysconfPrint("_SC_PAGESIZE:       ", _SC_PAGESIZE);
    sysconfPrint("_SC_RTSIG_MAX:      ", _SC_RTSIG_MAX);
    exit(EXIT_SUCCESS);
}
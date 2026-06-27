# Задание
Попробуйте запустить программу из листинга 11.2 в других файловых системах

## Понятия
`fpathconf()` - возвращает значение ограничения параметра конфигурации name для открытого файлового дескриптора fd.
```
#include <unistd.h>

long fpathconf(int fd, int name);
```

`pathconf()` - возвращает значение ограничения параметра конфигурации name для файлового по пути path.
```
#include <unistd.h>

long pathconf(const char *path, int name);
```

Единственное различие между pathconf() и fpathconf() заключается в способе указания файла или каталога. Для pathconf() — в виде путевого имени в аргументе pathname, а для fpathconf() — через дескриптор предварительно открытого файла.

Аргумент name является одной из констант вида _PC_*, определенных в <unistd.h>

       _PC_LINK_MAX
              The maximum number of links to the file.  If fd or path refer to a directory, then the value applies to the whole directory.  The corresponding macro is _POSIX_LINK_MAX.

       _PC_MAX_CANON
              The maximum length of a formatted input line, where fd or path must refer to a terminal.  The corresponding macro is _POSIX_MAX_CANON.

       _PC_MAX_INPUT
              The maximum length of an input line, where fd or path must refer to a terminal.  The corresponding macro is _POSIX_MAX_INPUT.

       _PC_NAME_MAX
              The maximum length of a filename in the directory path or fd that the process is allowed to create.  The corresponding macro is _POSIX_NAME_MAX.

       _PC_PATH_MAX
              The maximum length of a relative pathname when path or fd is the current working directory.  The corresponding macro is _POSIX_PATH_MAX.

       _PC_PIPE_BUF
              The maximum number of bytes that can be written atomically to a pipe of FIFO.  For fpathconf(), fd should refer to a pipe or FIFO.  For fpathconf(), path should refer  to
              a FIFO or a directory; in the latter case, the returned value corresponds to FIFOs created in that directory.  The corresponding macro is _POSIX_PIPE_BUF.

       _PC_CHOWN_RESTRICTED
              This  returns  a  positive value if the use of chown(2) and fchown(2) for changing a file's user ID is restricted to a process with appropriate privileges, and changing a
              file's group ID to a value other than the process's effective group ID or one of its supplementary group IDs is restricted to a process with appropriate privileges.   Ac‐
              cording to POSIX.1, this variable shall always be defined with a value other than -1.  The corresponding macro is _POSIX_CHOWN_RESTRICTED.

              If fd or path refers to a directory, then the return value applies to all files in that directory.

       _PC_NO_TRUNC
              This returns nonzero if accessing filenames longer than _POSIX_NAME_MAX generates an error.  The corresponding macro is _POSIX_NO_TRUNC.

       _PC_VDISABLE
              This returns nonzero if special character processing can be disabled, where fd or path must refer to a terminal.

## Вывод

ext4
```
./run 
_PC_NAME_MAX:  255
_PC_PATH_MAX:  4096
_PC_PIPE_BUF:  4096
```

tmpfs (виртуальная ФС в оперативной памяти):
```
./run < /dev/shm/test_file 
_PC_NAME_MAX:  255
_PC_PATH_MAX:  4096
_PC_PIPE_BUF:  4096
```

procfs (виртуальная ФС ядра):
```
./run < /proc/version 
_PC_NAME_MAX:  255
_PC_PATH_MAX:  4096
_PC_PIPE_BUF:  4096
```

sysfs (виртуальная ФС):
```
./run < /sys/kernel/profiling
_PC_NAME_MAX:  255
_PC_PATH_MAX:  4096
_PC_PIPE_BUF:  4096
```
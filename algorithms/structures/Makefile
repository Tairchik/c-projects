CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -pthread

SHARED ?= 0

ifeq ($(DEBUG),1)
    CFLAGS += -g -O0 -DDEBUG
else
    CFLAGS += -O2
endif

# Базовая директория для всех модулей
SRC_DIR = src

# Список модулей
MODULES = vectror

MODULE_PATHS = $(addprefix $(SRC_DIR)/, $(MODULES))

# Находим все .c файлы во всех указанных модулях
SRCS = $(wildcard $(addsuffix /*.c, $(MODULE_PATHS)))
OBJS = $(SRCS:.c=.o)

# Добавляем пути к заголовочным файлам всех модулей (-I src/vectror)
CFLAGS += $(addprefix -I , $(MODULE_PATHS))

ifeq ($(SHARED),1)
    CFLAGS += -fPIC
    TARGET = libvector.so
else
    TARGET = libvector.a
endif

all: $(TARGET)

libvector.a: $(OBJS)
	ar rcs $@ $^

libvector.so: $(OBJS)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f libvector.a libvector.so

re: fclean all

.PHONY: all clean fclean re
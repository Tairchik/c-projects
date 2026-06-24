CC = gcc
CFLAGS = -Wall -Wextra -I. -pthread

SORTS = bubble
TARGETS = $(addsuffix _sort, $(SORTS))

all: $(TARGETS)

bubble_sort: main.o bubble/bubble.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c sort.h
	$(CC) $(CFLAGS) -c main.c

%/%.o: %/%.c sort.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGETS) main.o */*.o

.PHONY: all clean
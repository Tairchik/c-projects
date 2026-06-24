CC = gcc
TARGET = run

OBJS = main.o my_malloc.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	rm -f *.o

main.o: main.c
	$(CC) -c main.c

my_dup.o: my_malloc.c my_malloc.h
	$(CC) -c my_malloc.c

clean: 
	rm -f $(TARGET) *.o
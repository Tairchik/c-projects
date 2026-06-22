CC = gcc
TARGET = run

OBJS = main.o my_dup.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	rm -f *.o

main.o: main.c
	$(CC) -c main.c

my_dup.o: my_dup.c my_dup.h
	$(CC) -c my_dup.c

clean: 
	rm -f $(TARGET) *.o
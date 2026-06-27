CC = gcc
TARGET = run

OBJS = sysconf.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	rm -f *.o

sysconf.o: sysconf.c
	$(CC) -c sysconf.c

clean: 
	rm -f $(TARGET) *.o
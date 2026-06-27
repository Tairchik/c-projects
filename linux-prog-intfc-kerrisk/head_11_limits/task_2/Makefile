CC = gcc
TARGET = run

OBJS = fpathconf.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	rm -f *.o

fpathconf.o: fpathconf.c
	$(CC) -c fpathconf.c

clean: 
	rm -f $(TARGET) *.o
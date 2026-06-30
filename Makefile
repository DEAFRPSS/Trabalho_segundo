CC = gcc
RM = rm
TARGET = ex

all: objetos
	$(CC) main.o src.o -o $(TARGET)

objetos: main.c src.c
	$(CC) -c main.c
	$(CC) -c src.c

clean:
	$(RM) *.o
	$(RM) $(TARGET)

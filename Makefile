CC = gcc -Wall -g
all: frequency

frequency: frequency.o
	$(CC) frequency.o -o frequency

frequency.o: frequency.c frequency.h
	$(CC) -c frequency.c -o frequency.o

.PHONY: clean all

clean:
	rm *.o frequency
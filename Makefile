# Utilisation de variables pour faciliter les changements
CC = gcc
CFLAGS = -Wall -ansi -std=c17 -g

test: my_malloc.o main.o
	$(CC) -o main my_malloc.o main.o $(CFLAGS)

my_malloc.o: my_malloc.c my_malloc.h
	$(CC) -c my_malloc.c -o my_malloc.o $(CFLAGS)

main.o: main.c my_malloc.h
	$(CC) -c main.c -o main.o $(CFLAGS)

clean:
	rm -f *.o main

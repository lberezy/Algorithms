# Based off supplied makefile


CC=gcc
DEBUG=-g
CFLAGS=-Wall $(DEBUG) -ansi -O0 -pedantic

fresh: clean all

all: helpme

helpme: helpme.o 
	$(CC) $(CFLAGS) -o helpme helpme.o

helpme.o: helpme.c helpme.h graph.o
	$(CC) $(CFLAGS) -c helpme.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c helpme.c

clean:
	rm -rf *.o helpme

test: fresh
	./helpme WestAfricaDatabase 

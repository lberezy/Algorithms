# Based off supplied makefile


CC=gcc
DEBUG=-g
CFLAGS=-Wall $(DEBUG) -ansi

all: listdict skipdict

listdict: misc.o dict.o list.o 
	$(CC) $(CFLAGS) -o listdict dict.o list.o misc.o

skipdict: misc.o dict2.o skiplist.o 
	$(CC) $(CFLAGS) -o skipdict dict2.o skiplist.o misc.o

list.o: list.c list.h 
	$(CC) $(CFLAGS) -c list.c

skiplist.o: skiplist.c skiplist.h
	$(CC) $(CFLAGS) -c skiplist.c

dict.o: dict.c dict.h 
	$(CC) $(CFLAGS) -c dict.c

dict2.o: dict2.c dict2.h
	$(CC) $(CFLAGS) -c dict2.c

misc.o: misc.c misc.h
	$(CC) $(CFLAGS) -c misc.c

clean:
	rm -rf *.o listdict skipdict

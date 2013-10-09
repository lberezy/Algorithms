CC=gcc
DEBUG=-g
CFLAGS=-Wall $(DEBUG)

fresh: clean all

all: helpme

helpme: helpme.o 
	$(CC) $(CFLAGS) -o helpme helpme.o

helpme.o:
	$(CC) $(CFLAGS) -c helpme.c

graph.o:
	$(CC) $(CFLAGS) -c graph.o graph.c graph.h 

clean:
	rm -rf *.o helpme

test: fresh
	./helpme helpfiles/WestAfricanDB.txt
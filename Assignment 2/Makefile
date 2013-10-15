CC=gcc
DEBUG=-g
CFLAGS=-Wall $(DEBUG)

fresh: clean all

all: helpme

helpme: helpme.o graph.o
	$(CC) $(CFLAGS) -o helpme helpme.o graph.o

helpme.o:
	$(CC) $(CFLAGS) -c helpme.c

graph.o:
	$(CC) $(CFLAGS) -c graph.c

clean:
	rm -rf *.o helpme

test: fresh
	./helpme helpfiles/WestAfricanDB.txt

debug: fresh
	gdb  --args ./helpme helpfiles/WestAfricanDB.txt
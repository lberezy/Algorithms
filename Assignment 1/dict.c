/*
	Algorithms and Data Structures - Assignment 1
	Part 1 - Linked List Dictionary

	Lucas Berezy, 2013

	This program implements a dictionary system using a linked-list
	datastructure. A dictionary in this program is represented by a pointer
	to the head node of a linked list (list_t). A wrapper typedef around this
	would only serve to make the code less clear.

	Creation of a new dictionary is as simple as declaring a new variable of
	type *node_t and assigning it to NULL or inseting an initial key-value
	pair with *node_t make_node(key, value).

	Input format:
	Program takes a single command line argument specifying the location of
	a local plain-text file key-value pairs separated by comma and line
	delimited by return symbols.
	The program accepts key lookups as integers between the range of a signed
	integer (system dependent) and returns output on stdout as below.s

	Output format documentation:
	Output begins with a single line comprising:
	<number of data items inserted> "Insertions:" <number of key comparisons 
	during insertion process>

	The following lines correspond to dictionary lookups entered through
	stdin and have the following format:
	<search key> <value returned or "NOTFOUND"> <number of key comparisons
	made during the key search>

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "errorcodes.h"
#include "misc.h"
#include "list.h"
#include "debug.h"

#define MAX_LENGTH 255

int main(int argc, char **argv) {

	int keybuff, item_counter = 0, comp_counter = 0;
	/* file name and pointer */
	char *fname, strbuff[MAX_LENGTH + 1];
	FILE *fp;
	node_t *nodebuff, *dict = NULL;

	if(argc != 2) {
		printf("Usage: %s filename\n",argv[0]);
		exit(EXIT_MISUSE);
	}
	
	/* copy the filename from argv[1] into heap space, same as strdup() */
	fname = strcpy(safe_malloc(strlen(argv[1] + 1)), argv[1]);
	/* attempt to open file for reading */
	fp = safe_fopen(fname, "r");


	/* build the dictionary */
	while (fscanf(fp, "%d %s", &keybuff, strbuff) == 2){
		if (dict == NULL) {
			dict = make_node(keybuff, strbuff);
		} else {
			dict = insert(dict, keybuff, strbuff, &comp_counter);
		}
		item_counter++;
		if (DEBUG) printf("%d %s\n", keybuff, strbuff);
	}
	fclose(fp);
	/* Print number of items and number of comparisons during insertion */
	printf("%d\tInsertions:\t%d\n", item_counter, comp_counter);
	comp_counter = 0; /* reset comparison counter */

	if (DEBUG) {
	printf("\nDone! Printing list:\n\n");
	print_list(dict);
	}

	/* key lookup loop from stdin. Exits on any invalid input. Key must be less
	than INT_MAX */
	while (scanf("%d", &keybuff) == 1) {
		scanf("%*[^\n]"); /* clear stdin line buffer */
		/* printf("Search for a key: ____\b\b\b\b"); */
		nodebuff = search(dict, keybuff, &comp_counter);
		printf("%d\t%s\t%d\n",
				keybuff,
				(nodebuff) ? nodebuff->value : "NOTFOUND",
				comp_counter);
		comp_counter = 0;
	}
	return EXIT_SUCCESS;
}
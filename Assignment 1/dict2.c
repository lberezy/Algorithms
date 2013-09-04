/*
	Algorithms and Data Structures - Assignment 1
	Part 2 - Skip List Dictionary

	Lucas Berezy, 2013
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "errorcodes.h"
#include "misc.h"
#include "skiplist.h"
#include "debug.h"

#define MAX_LENGTH 255

int main(int argc, char **argv) {

	int keybuff, item_counter = 0, comp_counter = 0;
	/* file name, input buffer array and file pointer */
	char *fname, strbuff[MAX_LENGTH + 1];
	FILE *fp;
	skipdict_t *dict = make_dict(MAX_LEVEL, LEVEL_PROB);

	if(argc != 2) {
		printf("Usage: %s filename\n",argv[0]);
		exit(EXIT_MISUSE);
	}
	
	/* copy the filename from argv[1] into heap space, same as strdup() */
	fname = strcpy(safe_malloc(strlen(argv[1] + 1) * sizeof(char)), argv[1]);
	/* attempt to open file for reading */
	fp = safe_fopen(fname, "r");


	/* build the dictionary */
	while (fscanf(fp, "%d %s", &keybuff, strbuff) == 2){
		insert(dict, keybuff, strbuff);
		if (DEBUG) printf("%d %s\n", keybuff, strbuff);
	}
	fclose(fp);
	/* Print number of items and number of comparisons during insertion */
	printf("%d\tInsertions:\t%d\n", item_counter, counter(0));
	counter(-1); /* reset comparison counter */

	if (DEBUG) {
	printf("\nDone! Printing list:\n\n");
	print_skipdict(dict);
	}

	/* key lookup loop from stdin. Exits on any invalid input. Key must be less
	than INT_MAX */
	while (scanf("%d", &keybuff) == 1) {
		scanf("%*[^\n]"); /* clear stdin line buffer */
		/* printf("Search for a key: ____\b\b\b\b"); */
		/* nodebuff = search(dict, keybuff, &comp_counter); */
		/* printf("%d\t%s\t%d\n",
				keybuff,
				(nodebuff) ? nodebuff->value : "NOTFOUND",
				comp_counter); */
		counter(-1); /* reset counter */
	}
	return EXIT_SUCCESS;
}
/*
	Algorithms and Data Structures - Assignment 1
	Part 1 - Linked List Dictionary

	Lucas Berezy, 2013
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

	int i, keybuff;
	/* file name and pointer */
	char *fname, strbuff[MAX_LENGTH + 1];
	FILE *fp;
	node_t list;

	if(argc != 2) {
		printf("Usage: %s filename\n",argv[0]);
		exit(EXIT_MISUSE);
	}
	
	/* copy the filename from argv[1] into heap space, same as strdup()*/
	fname = strcpy(safe_malloc(strlen(argv[1] + 1)), argv[1]);
	fp = safe_fopen(fname, "r");


	
	while (fscanf("%d %s", &keybuff, strbuff) == 2);

	return EXIT_SUCCESS;
}
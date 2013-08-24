/*
	Algorithms and Data Structures - Assignment 1
	Part 2 - Skip List Dictionary

	Lucas Berezy, 2013
*/

#include <stdlib.h>
#include <stdio.h>

#include "skiplist.h"
#include "errorcodes.h"


int main(int argc, char **argv) {



	if(argc != 2) {
		printf("Usage: %s filename\n",argv[0]);
		exit(EXIT_MISUSE);
	}

	return EXIT_SUCCESS;
}
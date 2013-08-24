/*
	Algorithms and Data Structures - Assignment 1
	Part 2 - Skip List

	Lucas Berezy, 2013
*/

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "errorcodes.h"
#include "skiplist.h"

int level(int max_level, double p) {
	/* 
	Returns an integer >= 0 and < MAXLEVEL with a distribution
	such that the probability of receiving 0 is 1/p, 1 is 1/(2p) etc. 
	p(n) = 1/((n+1)*p)
	*/

	int level = 0;
	static int init = 1; /* flag variable */

	if (init) { /* make sure to initialise the generator (and only once) */
		init = 0;
		/* multiply by process ID so when executable is run more than once per
		second it gives a different pseudo-random stream */
		srand(time(NULL) * getpid());
	}

	/* generate the random level number */
	while ( ((float)rand()/RAND_MAX) <= p && level < max_level ) {  
		++level;
	}

	return level;
}

static void* safe_malloc(size_t size) {
	/* 
	Checks to see if malloc has failed, slightly safer than usual.
	Probably pointless because a seg-fault can at least gives you a core
	dump to look through later on, but this is "good practice".
	*/

	assert(size > 0);
	void *tmp = malloc(size);
	if (!tmp) {
		/* printing is kind of pointless because it invokes malloc() again */
		fprintf(stderr, "Memory allocation failed!");
		fflush(stdout);
		sleep(1);
		exit(MALLOC_ERROR);
	}

	return tmp;
}

skipnode_t* make_skipnode(int level, int key, char *value) {
	/* 
	Allocates a skip list node, initialises all the level array pointers to 0
	and stores the key and value string in the node. Returns a pointer to the
	new node.
	*/

	int i;
	skipnode_t *node = (skipnode_t*)malloc(sizeof(skipnode_t));

	node->key = key;
	/* malloc some space for the string and copy it into the node*/
	node->value = safe_malloc(strlen(value) + 1);
	strcpy(node->value, value);
	
	/* could probably use calloc() to initialise node pointer array */
	node->next = (skipnode_t**)malloc((level + 1) * sizeof(skipnode_t*));
	for (i=0;i<=level;i++) {
		node->next[i] = NULL;
	}

	return node;
}

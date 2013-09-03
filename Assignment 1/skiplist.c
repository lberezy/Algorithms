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
#include "misc.h"

skiplist_t* make_skiplist(int max_level, double level_prob) {
	/*
	Allocates space for a pointer to the head skip node and an integer
	representation of the max_level of the list as a skip list container.
	Returns a pointer to the empty list.
	*/

	skiplist_t *list = (skiplist_t*)safe_malloc(sizeof(skipnode_t*)
												+ sizeof(int));
	/* light initialisation */
	list->max_level = max_level;
	list->level_prob = level_prob;
	list->curr_level = 0;
	list->head = NULL;

	return list;
}

void insert(skiplist_t* dict, int key, char *value, int *comp_counter) {
	/*
	Inserts a key:value pair into the given dictionary, counts key comparisons.
	Needs to keep track of list nodes to update at each level.
	*/


	int i = dict->max_level;
	int new_level = level(dict->max_level, dict->level_prob);
	skipnode_t *update[dict->max_level + 1]; /* hold node pointers for update */
	skipnode_t *list = dict->head;
	skipnode_t *tmp = make_skipnode(new_level, key, value);

	while (i > 0) { /* traverse levels of list, from sparse (top) to dense */
		while((list->next[i])->key < key) {
			list = list->next[i];
			(*comp_counter)++; /* record comparison */
		}
		update[i--] = list; /* store pointer to node and go down a level */
	}

	if (list->key == key) { /* update into set of dictionary items - no dupes*/
		list->value = safe_malloc(strlen(value) + 1); /* easier than linking 
		new tmp node */
	} else { /* need to insert the new node */

		if (new_level >= dict->curr_level){ /* handle new tallest node */
			/* when updating, header needs to point to new highest levels */
			for (i = dict->curr_level + 1; i <= new_level; i++) {
				update[i] = dict->head;
			}
			dict->curr_level = new_level; /* update dicts most extended level */
		}
		/* install changes into dict */
		for (i=1; i <= new_level; i++) {
			tmp->next[i] = update[i]->next[i];
			update[i]->next[i] = tmp;
		}
	}
}

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

skipnode_t* make_skipnode(int level, int key, char *value) {
	/* 
	Allocates a skip list node, initialises all the level array pointers to 0, 
	stores the key and value string in the node. Returns a pointer to the
	new node.
	*/

	int i;
	skipnode_t *node = (skipnode_t*)safe_malloc(sizeof(skipnode_t));

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

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

skipdict_t* make_dict(int level_max, double prob_level) {
	/*
	Allocates space for a pointer to the head skip node and an integer
	representation of the max_level of the list as a skip list container.
	Returns a pointer to the empty list.
	*/

	skipdict_t *dict = (skipdict_t*)safe_malloc(sizeof(skipdict_t));

	dict->head = (skipnode_t*)safe_malloc(sizeof(skipnode_t));

	
	/* light initialisation */
	dict->head->next = (skipnode_t**)calloc(level_max + 1, sizeof(skipnode_t*));
	dict->head->key = 0;
	dict->head->value = NULL;
	dict->max_level = level_max;
	dict->level_prob = prob_level;
	dict->curr_level = 0;

	return dict;
}

void insert(skipdict_t* dict, int key, char *value) {
	/*
	Inserts a key:value pair into the given dictionary, counts key comparisons.
	Needs to keep track of list nodes to update at each level.
	*/

	int i = dict->curr_level, j;
	int new_level = getlevel(dict->max_level, dict->level_prob);
	skipnode_t *list = dict->head;
	skipnode_t *tmp = make_skipnode(new_level, key, value); /* new node */
	/* hold node pointers for update */
	skipnode_t **update = (skipnode_t**)safe_malloc((dict->max_level + 1) 
													* sizeof(skipnode_t*));

	assert(tmp != NULL);
	counter(1);

	/* discovered a bug in the llvm-gcc on OSX 10.8 here, maybe. Without the 
	assert or anything referencing tmp, tmp is always 0x0 in the scope of the 
	next 'if' statement. dict->head would always be 0x0. */

	for(j = 0; j <= (dict->max_level); j++){
		update[j] = NULL;
	}
	/* memset(update, 0, dict->max_level + 1); */
	if (dict->head == NULL) { /* insert into empty dict */
		dict->curr_level = new_level;
		dict->head = tmp;
		return;
	}

	/* find location to insert */
	while (i >= 0) { /* traverse levels of list, from sparse (top) to dense */
		while(list->next[i] != NULL && list->next[i]->key < key) {
			list = list->next[i];
			counter(1); /* record comparison */
		}
		update[i--] = list; /* store pointer to node and go down a level */
	}

	list = list->next[0]; /* jump across one place incase key exists already */
	if (list && list->key == key) { /* update into set of dictionary items */
		counter(1); /* record comparison */
		/* update node with new value */
		list->value = strdup(value);
	} else if (list == NULL || list->key != key) { /* need to insert new node */

		if (new_level > dict->curr_level){ /* handle new tallest node */
			/* when updating, header needs to point to new highest levels */
			for (i = dict->curr_level + 1;
				i <= new_level && i <= dict->max_level; i++) {
				update[i] = dict->head;
			}
			dict->curr_level = new_level; /* update dicts most extended level */
		}
		/* install changes into dict */
		for (i=0; i <= new_level; i++) {
			tmp->next[i] = update[i]->next[i];
			update[i]->next[i] = tmp;
		}
	}
}


skipnode_t* search(skipdict_t* dict, int key) {
	/*
	Searches a skipdict for a key. Returns a pointer to the node if found, else
	returns a null pointer.
	*/

	int i = dict->curr_level;
	skipnode_t *list = dict->head;
	counter(1); /* increment counter */
	/* find node just before possible search match */
	while (i >= 0) {
		while (list->next[i] && list->next[i]->key < key) {
			list = list->next[i];
			counter(1); /* record comparison */
		}
		i--;
	}
	list = list->next[0]; /* move to next node */

	counter(1); /* record key comparison */
	/* return the node if it matches, else NULL */
	if (list == NULL || list->key != key) list = NULL;
	return list;
}

int getlevel(int max_level, double p) {
	/* 
	Returns an integer >= 0 and < MAXLEVEL with a distribution
	such that the probability of receiving 0 is n*p, 1 is 2*p etc. 
	p(n) = (n+1)*p
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
	while ( ((double)rand()/RAND_MAX) <= p && level < max_level ) {  
		++level;
	}

	return level;
}

void print_skipdict(skipdict_t *dict) {
	/*
	Traverse the bottom layer of the skipdict and prints each value.
	*/

	skipnode_t *curr = dict->head;
	while(curr) {
		printf("Key: %d Value: %s\n", curr->key, curr->value);
		curr = curr->next[0];
	}

}

skipnode_t* make_skipnode(int level, int key, char *value) {
	/* 
	Allocates a skip list node, initialises all the level array pointers to 0, 
	stores the key and value string in the node. Returns a pointer to the
	new node.
	*/

	int i;
	skipnode_t *tmp = (skipnode_t*)safe_malloc(sizeof(skipnode_t));

	/* bug isntroduced here */
	assert(level >= 0);
	/* could probably use calloc() to initialise node pointer array */
	tmp->next = (skipnode_t**)malloc((level + 1) * sizeof(skipnode_t*));
	for (i=0;i<=level;i++) {
		tmp->next[i] = NULL;
	}

	/* tmp->next = (skipnode_t**)calloc(8, sizeof(skipnode_t*)); */
	tmp->key = key;
	/* copy value string into node */
	tmp->value = strdup(value);
	/*tmp->value = (char*)safe_malloc((strlen(value) + 1) * sizeof(char)); */

	assert(tmp != NULL);
	return tmp;
}

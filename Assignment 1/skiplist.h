/*
	Algorithms and Data Structures - Assignment 1
	Part 2 - Skip List

	Lucas Berezy, 2013
*/
#ifndef SKIPLIST_H
#define SKIPLIST_H

#define MAX_LEVEL 6
#define LEVEL_PROB 0.5
#define MAX_STRING_LEN 255


typedef struct skipnode {
	int key;
	char *value;
	struct skipnode **next;
} skipnode_t;

typedef struct skiplist {
	skipnode_t* head;
	int max_level;
	int curr_level;
	double level_prob;
} skiplist_t;


int level(int max_level, double p);
skiplist_t* make_skiplist(int max_level, double level_prob);
skipnode_t* make_skipnode(int level, int key, char *value);
void insert(skiplist_t* dict, int key, char *value, int *comp_counter);
void print_skipdict(skiplist_t *dict);

/* skip list node, <key:value> pairs and array of pointers to next node */


#endif
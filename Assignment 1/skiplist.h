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

typedef struct skipdict {
	skipnode_t* head;
	int max_level;
	int curr_level;
	double level_prob;
} skipdict_t;


int getlevel(int max_level, double p);
skipdict_t* make_dict(int max_level, double level_prob);
skipnode_t* search(skipdict_t* dict, int key);
skipnode_t* make_skipnode(int level, int key, char *value);
void insert(skipdict_t* dict, int key, char *value);
void print_skipdict(skipdict_t *dict);

/* skip list node, <key:value> pairs and array of pointers to next node */


#endif

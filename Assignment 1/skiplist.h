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


int level(int max_level, double p);
skipnode_t* make_skipnode(int level, int key, char *value);

/* skip list node, <key:value> pairs and array of pointers to next node */


#endif
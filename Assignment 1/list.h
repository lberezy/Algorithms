/*
	Algorithms and Data Structures - Assignment 1
	Part 1 - Linked List

	Lucas Berezy, 2013
*/

#ifndef LIST_H
#define LIST_H


typedef struct node {
	int key;
	char *value;
	struct node *next;
} node_t;

node_t* make_node(int key, char *value);
node_t* insert(node_t *list, int key, char *value, int *comp_counter);
node_t* search(node_t *list, int key, int *counter);
node_t* delete(node_t *list, int key, int *counter);
void print_list(node_t *list);

#endif
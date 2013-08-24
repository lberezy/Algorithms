#ifndef LIST_H
#define LIST_H


typedef struct node {
	int key;
	char *value;
	struct node *next;
} node_t;

node_t* make_node(int key, char *value);

#endif
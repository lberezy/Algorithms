#ifndef LIST_H
#define LIST_H


typedef struct node {
	int key;
	char *value;
	struct node *next;
} node_t;

node_t* make_node(int key, char *value);
node_t* insert(node_t *list, int key, char *value);
node_t* search(node_t *list, int key);
node_t* delete(node_t *list, int key);

#endif
/*
	Algorithms and Data Structures - Assignment 1
	Part 1 - Linked List

	Lucas Berezy, 2013
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "misc.h"
#include "debug.h"


node_t* make_node(int key, char *value) {
	/* 
	Allocates a linked list node and stores the key and value string
	in the node. Returns a pointer to the new node. By default, next
	points to NULL.
	*/

	node_t *node = (node_t*)malloc(sizeof(node_t));

	node->key = key;
	/* malloc some space for the string and copy it into the node*/
	node->value = safe_malloc(strlen(value) + 1);
	strcpy(node->value, value);

	node->next = NULL;

	return node;
}

node_t* insert(node_t *list, int key, char *value) {
	/*
	Takes the head of a linked list and traverses it until it finds
	an ordered place to insert a new node of <key:value>
	
	*/

	node_t *tmp;
	/* hold position to left and right of insertion point */
	node_t *left = NULL, *right = list;

	counter(1);
	if (list == NULL) {
		if (DEBUG) {
			printf("Warning, list == NULL in insert()!\n");
		}
		return list;
	}

	tmp = make_node(key, value); /* node to insert */

	/* find insertion point in tail */
	while (right && right->key < key) {
		left = right; /* bring forward left pointer */
		right = right->next; /* move forward right pointer */
		counter(1); /* increment key comparison counter */

	}

	/* insert the new node in-between left and right */

	if (left == NULL) {
		tmp->next = list;
		list = tmp;
	} else {
		tmp->next = right;
		left->next = tmp;
	}
	return list; /* need to reassign list out of this scope */
}

node_t* search(node_t *list, int key) {
	/*
	Finds the first node that matches 'key' and returns a pointer to it, or
	NULL if key not found.
	*/

	if (list == NULL) {
		if (DEBUG) {
			printf("Warning, list == NULL in insert()!\n");
		}
		return list;
	}
	counter(1); /* prime the counter by 1 */
	while(list != NULL && list->key != key) {
		list = list->next;
		counter(1);
	}
	return list;
}

node_t* delete(node_t *list, int key) {
	/*
	Finds the first node that matches 'key' and unlinks it from the list.
	This deletion method is only applicable to a dictionary where it is known
	that there exists only one node with a particular key.
	Returns a pointer to the updated list (for freeing head node).
	*/

	node_t *tmp, *prev = list;

	/* find the node to free */
	counter(1); /* prime the counter by 1 */

	while(tmp != NULL && list->key != key) {
		prev = list;
		tmp = tmp->next;
		counter(1);
	}
	if(prev == list) {
		free(prev);
		return list->next;
	}
	prev->next = tmp->next;
	free(tmp);
	return list;
}

void print_list(node_t *list) {
	while(list){
		printf("%d %s\n", list->key, list->value);
		list = list->next;
	}
}

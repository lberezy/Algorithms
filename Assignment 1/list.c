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

void insert(node_t *list, int key, char *value) {
	/*
	Takes the head of a linked list and traverses it until it finds
	an ordered place to insert a new node of <key:value>
	*/

	node_t *tmp;
	/* hold position to left and right of insertion point */
	node_t *left = list, *right = list;

	if (list == NULL) {
		if (DEBUG) {
			printf("Warning, list == NULL in insert()!\n");
		}
		return;
	}

	/* find insertion point in list */
	while (right->next && right->key < key) {
		left = right; /* bring forward left pointer */
		right = right->next; /* move forward right pointer */
	}

	/* insert the new node in-between left and right */
	tmp = make_node(key, value);
	left->next = tmp;
	
	if (left == right) {
		tmp->next = NULL;
	} else {
	tmp->next = right; /* BUG */
	}
}

node_t* search(node_t *list, int key) {
	/*
	Finds the first node that matches 'key' and returns a pointer to
	the matching node.
	*/

	while(list->next && list->key != key) {
		list = list->next;
	}
	return list;
}

node_t* delete(node_t *list, int key) {
	/*
	Finds the first node that matches 'key' and unlinks it from the list.
	Returns a pointer to the unlinked node such that it can be freed. Returns
	NULL if there are no matches (not guaranteed, only the value of node->next).
	*/

	node_t *prev = list;

	while(list->next && list->key != key) {
		prev = list;
		list = list->next;
	}

	return prev;
}

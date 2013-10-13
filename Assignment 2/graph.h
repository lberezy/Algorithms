/* 	graph.h
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/

#ifndef GRAPH_H
#define GRAPH_H


typedef struct node {
	/* apparently one can specify the number of bits each item in a struct is
	allocated (e.g. "int supplies : 5" for 5 bits as needed), but this looked
	pretty dangerous. */
	int ID, supplies;
	char *name;
} node_t;

int** new_matrix(int size, int initial);
void floyd_warshall(int **graph, int **next, int size);

#endif

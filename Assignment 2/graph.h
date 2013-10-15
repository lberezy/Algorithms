/* 	graph.h
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/

#ifndef GRAPH_H
#define GRAPH_H


#define INF (INT_MAX / 2 - 1)	/* because INT_MAX + INT_MAX is an overflow */
#define NO_PRED -1 /* value for no predecessor in next[][] */
#define BUFFER_SIZE 256

typedef struct node {
	/* apparently one can specify the number of bits each item in a struct is
	allocated (e.g. "int supplies : 5" for 5 bits as needed), but this looked
	pretty dangerous. */
	int ID, supplies;
	char name[BUFFER_SIZE];
} node_t;

int** new_matrix(int size, int initial);
void floyd_warshall(int **graph, int **next, int size);
void print_matrix(int **matrix, int size);
void print_path(int a, int b, int **next, node_t **nodes);

#endif

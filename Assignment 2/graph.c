l/* 	graph.c
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/

#include <limits.h>

node_t** create_graph(int N)
{
	/* allocates an NxN adjacency matrix of nodes */
	int i;
	node_t* nodes = calloc(N * N, sizeof(node_t));
	node_t** graph = calloc(N * sizeof(node_t*));
	for ( i = 0; i < N; i++) {
		graph[i] = nodes + (i * N);
	}
	return graph;
}

void floyd_warshall(node_t** graph) {
	
}
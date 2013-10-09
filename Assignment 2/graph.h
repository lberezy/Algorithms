/* 	graph.h
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/

#ifndef GRAPH_H
#define GRAPH_H

typedef struct link { /* connects two nodes via time-weighted edge */
	node_t* to, from;
	int time;
} link_t;

typedef struct node { /* represents a source of aid and its connections */
	int supplies : 5; /* bit field only needs 5 bits */
	link_t* links;
} node_t;

node_t** create_graph(int N)

#endif

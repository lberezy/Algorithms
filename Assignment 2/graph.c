/*     graph.c
    Part of COMP20003 Project 2
    Author: Lucas Berezy
*/

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "helpme.h"


int** new_matrix(int size, int initial)
{
    /* returns an N * N matrix with all values initialised to initial */
    int i, j;

    int **matrix = malloc(size * size * sizeof * matrix);
    for ( i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof matrix);
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            matrix[i][j] = initial;
        }
    }
    return matrix;
}

void print_matrix(int **matrix, int size)
{
    /* prints a square matrix of integers */
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        putchar('\n');
    }
}

void print_path(int a, int b, int **next, node_t **nodes)
{
	/* Recursively follow next[] until a==b. As calls stack resolves,
	path will be printed in order (begining -> destination) */

    if (a == b)
    {
        printf("\t%d\t%s\n", nodes[b]->ID, nodes[b]->name);
    }
    /* gap in path */
    else if (next[a][b] == NO_PRED)
    {
        puts("No path found! D:");
    }
    else
    {
        print_path(a, next[a][b], next, nodes);
        /* print as call stack resolves */
        printf("\t%d\t%s\n", nodes[b]->ID, nodes[b]->name);
    }
}



void floyd_warshall(int **graph, int **next, int size)
{
    /* if the shortest path from a->b and b->c is known, then
    the shortest path from a->c is a->b->c */
    int a, b, c;

    /* construct the array of predecessors */
    for (a = 0; a < size; a++)
    {
        for (c = 0; c < size; c++)
        {
            /* because unreadable code is fun */
            /* if node is self or has no connection, record
            no predecessor, else record the node before it (a) */
            next[a][c] = (a == c || graph[a][c] == INF) ? NO_PRED : a;
        }
    }


    /* main Floyd-Warshall loop structure */
    for (b = 0; b < size; b++)
    {
        for (a = 0; a < size; a++)
        {
            for (c = 0; c < size; c++)
            {
            	/* found a better path? record the result */
                if ((graph[a][b] + graph[b][c]) < graph[a][c])
                {
                    graph[a][c] = graph[a][b] + graph[b][c];
                    /* update predecessor */
                    next[a][c] = next[b][c];
                }
            }
        }
    }


}

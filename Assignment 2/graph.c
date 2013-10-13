/*     graph.c
    Part of COMP20003 Project 2
    Author: Lucas Berezy
*/

#include <limits.h>
#include <stdlib.h>

#include "graph.h"



int **new_matrix(int size, int initial)
{
    /* returns an N * N matrix with all values initialised to initial */
    int i, j;

    int **matrix = malloc(size * size * sizeof *matrix);
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


void floyd_warshall(int **graph, int **next, int size)
{
    /* if the shortest path from a->b and b->c is known, then
    the shortest path from a->c is a->b->c */
    int a, b, c;

    for (a = 0; a < size; a++)
    {
        for (c = 0; c < size; c++)
        {
            /* because unreadable code is fun */
            next[a][c] = (a == c || graph[a][c] == INT_MAX) ? -1 : a;
        }
    }

    for (b = 0; b < size; b++)
    {
        for (a = 0; a < size; a++)
        {
            for (c = 0; c < size; c++)
            {
                /* graph[a][c] = MIN(graph[a][c], graph[a][b] + graph[b][c]); */
                if (graph[a][b] + graph[b][c] < graph[a][c])
                {
                    graph[a][c] = graph[a][b] + graph[b][c];
                    next[a][c] = next[b][c];
                }
            }
        }
    }
}

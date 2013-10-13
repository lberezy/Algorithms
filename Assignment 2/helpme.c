/*  helpme.c
    Part of COMP20003 Project 2
    Author: Lucas Berezy
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "graph.h"
#include "helpme.h"





int encode_supplies(char *str)
{
    /* Forms a bit-field (int) as per design.txt from valid string of
    supplies. Returns 0 if X is in the input string.

    There's definitely a simpler way to store this information, but
    I wanted to gain some familiarity with C's bitwise operators. */
    int i;
    unsigned int out = 0;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'X') return NOHELP;
        switch (str[i])
        {
        case BLANKET_C:
        {
            out |= BLANKET_B;
            break;
        }
        case FOOD_C:
        {
            out |= FOOD_B;
            break;
        }
        case WATER_C:
        {
            out |= WATER_B;
            break;
        }
        case DIGGING_C:
        {
            out |= DIGGING_B;
            break;
        }
        case MEDICINE_C:
        {
            out |= MEDICINE_B;
            break;
        }
        }
    }
    return out;
}

int main(int argc, char const *argv[])
{
    char *fname, loc_name[BUFFER_SIZE], supply_string[BUFFER_SIZE];
    char str_buff[BUFFER_SIZE];
    FILE *fp;
    int supply_data, num_nodes = 0;
    /* for tokeniser use */
    int **graph, **next;
    node_t **nodes;



    /* try to load the database */
    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        fname = strdup(argv[1]);
        if ((fp = fopen(fname, "r")) == NULL)
        {
            perror("Error: Could not open file!");
            exit(EXIT_FAILURE);
        }
    }
    puts("Please enter the location of the disaster:");
    scanf("%s", loc_name);
    /* *** check validity */

    puts("What kinds of supplies do you need?");
    scanf("%s", supply_string);
    supply_data = encode_supplies(supply_string);
    printf("%d\n", supply_data);

    /* tokenise input DB */

    /* first line contains number of nodes */
    fgets(str_buff, BUFFER_SIZE, fp);
    num_nodes = atoi(str_buff);
    printf("Number of nodes: %d\n", num_nodes);

    /* allocate data structures */
    nodes = malloc(num_nodes * sizeof (node_t));
    graph = new_matrix(num_nodes, INT_MAX); /* all nodes have infinite travel time */
    next = new_matrix(num_nodes, -1); /* -1 means no previous node */

    /* for each line of the DB, token first two items delimited by */
    while (fgets(str_buff, BUFFER_SIZE, fp) != NULL)
    {
        node_t *tmp;
        tmp = nodefromDB(str_buff, graph); /* insert node into graph */
        nodes[tmp->ID] = tmp; /* store the node for quick lookup by ID */
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

node_t *nodefromDB(char *DBline, int **graph)
{
    /* Constructs a graph node from a well-formatted string as found in the
    database file. */

    node_t *tmp = malloc(sizeof tmp); /* temp node to construct */
    char *str; /* temporary pointer for peeking into string */
    int tmp_id, tmp_weight; /* for tokenisation of node links */

    tmp->ID = atoi(strtok(DBline, DELIM_1));
    tmp->name = strdup(strtok(NULL, DELIM_1));
    tmp->supplies = encode_supplies(strtok(NULL, DELIM_1));
    graph[tmp->ID][tmp->ID] = 0;

    printf("--\nNode: %d\nName: %s\nSupplies: %d\nConnections: \n",
           tmp->ID, tmp->name, tmp->supplies);

    /* parse the residue (stuff with N:T,N:T... etc) and store
    the links to other nodes in the graph */
    while ((str = strtok(strtok(NULL, DELIM_1), DELIM_2)) != NULL)
    {
        /* has issue reading when nothing to tokenise */
        sscanf(str, "%d" DELIM_3 "%d", &tmp_id, &tmp_weight);
        graph[tmp->ID][tmp_id] = tmp_weight;
        printf("Node: %d\tTime: %d\n", tmp_id, tmp_weight);
    }
    return tmp;
}

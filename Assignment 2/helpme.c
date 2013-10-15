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


int main(int argc, char const *argv[])
{
    char *fname, dest_name[BUFFER_SIZE], supply_string[BUFFER_SIZE];
    char str_buff[BUFFER_SIZE];
    FILE *fp;
    int i, mask, supply_data, dest_ID, num_nodes = 0, min_val = INF, 
    	min_node = -1;
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


    /* 
	**************
    Tokenise DB 
    */

    /* first line contains number of nodes */
    fgets(str_buff, BUFFER_SIZE, fp);
    num_nodes = atoi(str_buff);
    printf("Number of nodes: %d\n", num_nodes);

    /* allocate data structures */
    nodes = malloc(num_nodes * sizeof (node_t));
    graph = new_matrix(num_nodes, INF); /* all nodes have infinite travel time */
    next = new_matrix(num_nodes, -1); /* -1 means no previous node */

    /* for each line of the DB, token first two items delimited by */
    while (fgets(str_buff, BUFFER_SIZE, fp) != NULL)
    {
        node_t *tmp;
        tmp = nodefromDB(str_buff, graph); /* insert node into graph */
        nodes[tmp->ID] = tmp; /* store the node for quick lookup by ID */
    }
    fclose(fp);

    /* 
	**************
    Gather info 
    */

    /* print out nodes once stored */
    puts("Please see design.txt!!!");
    for (i = 0; i < num_nodes; i++) {
    	printf("%s\n", nodes[i]->name);
    }

    puts("Please enter the location of the disaster:");
    scanf("%s", dest_name);
    if ((dest_ID = name_to_ID(dest_name, nodes, num_nodes)) == NODE_NOT_FOUND)
    {
        printf("Destination %s not found! Exiting.", dest_name);
        return EXIT_SUCCESS;
    }
    printf("Destination ID: %d\n", dest_ID);

    puts("What kinds of supplies do you need?");
    scanf("%s", supply_string);
    supply_data = encode_supplies(supply_string);

    /* 
	**************
    Compute paths 
    */

    floyd_warshall(graph, next, num_nodes); /* function has side effect */

    /* 
	**************
    Print output 
    */

    /* Find the closest source of any help */

    if (supply_data == NOHELP) /* simply find the closest source of aid */
    {
        for (i = 0; i < num_nodes; i++)
        {
            /* only look at nodes that have some form of help */
            if ((graph[i][dest_ID] < min_val) && (nodes[i]->supplies > NOHELP))
            {
                min_val = graph[i][dest_ID];
                min_node = i;
            }

        }

        if (min_node > 0 && nodes[min_node]->supplies > NOHELP)
        {
        	printf("Closest centre with any aid: %s\n", nodes[min_node]->name);
        	print_path(min_node, dest_ID, next, nodes);
            printf("Has: "); print_supplies(nodes[min_node]->supplies);
            putchar('\n');
        }
        else
        {
            printf("No help available!");
        }
    }
    else
    {
        /* for each supply (as a bitmask), find the shortest path */
        for (mask = 1; mask <= (1 << (NUM_SUPPLIES - 1)); mask <<= 1)
            /* please don't hate me */
        {
            if (!(supply_data & mask)) continue; /* don't need this supply */
            find_supply(mask, dest_ID, supply_data,
                        nodes, graph, next, num_nodes);
        }
    }
    return EXIT_SUCCESS;
}

void print_supplies(int supply_data)
{
    /* Prints out the character representation of the supply data. Does
    not print a new line character when finished. */

    int i;
    if (supply_data == NOHELP)
    {
        printf("%c", NOHELP_C);
    }
    for (i = 1; i <= (1 << (NUM_SUPPLIES - 1)); i <<= 1)
    {
        switch (supply_data & i)
        {
        case BLANKET_B:
        {
            printf("%c", BLANKET_C);
            break;
        }
        case FOOD_B:
        {
            printf("%c", FOOD_C);
            break;
        }
        case WATER_B:
        {
            printf("%c", WATER_C);
            break;
        }
        case DIGGING_B:
        {
            printf("%c", DIGGING_C);
            break;
        }
        case MEDICINE_B:
        {
            printf("%c", MEDICINE_C);
            break;
        }
        }
    }
}

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
        if (str[i] == NOHELP_C) return NOHELP;
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

int name_to_ID(char *name, node_t **nodes, int num_nodes)
{
    /* Looks up a node string name in array of nodes and returns its ID.
    Returns NODE_NOT_FOUND if node not found. */

    int i;
    for (i = 0; i < num_nodes; i++)
    {
        if (strcmp(name, nodes[i]->name) == 0)
        {
            return nodes[i]->ID;
        }
    }
    return NODE_NOT_FOUND;
}



void find_supply(int supply, int dest_ID, int supply_data, node_t **nodes,
                 int **graph, int **next, int num_nodes)
{
    /* finds and prints out the closest location that can supply relief of
    a given kind. */

    int i, min_val = INF, min_node = 0;

    printf("Looking for: "); print_supplies(supply); putchar('\n');
    min_val = INF;
    min_node = -1;
    /* linear search each of the nodes connecting to destination */
    for (i = 0; i < num_nodes; i++)
    {
        /* find the closest that has required resource */
        if ((graph[i][dest_ID] < min_val) &&
                (nodes[i]->supplies & supply))
        {
            min_val = graph[i][dest_ID];
            min_node = i;
        }
    }

    if (min_node == -1) /* Resource not found in any nodes */
    {
        puts("Resource not found!");
        puts("Request may be only partially fulfilled.");
    }
    else /* Resource was found. Print travel time and path. */
    {
        printf("Found at %s!\tTime: %d hours.\n",
               nodes[min_node]->name, graph[min_node][dest_ID]);
        puts("Take the following route:");
        puts("--begin");
        print_path(min_node, dest_ID, next, nodes);
        puts("--end\n");
    }

}

char *strdup(const char *str)
/* because it isn't in ISO-9899 (Standard C) and gcc on the
server complains. */
{
    int n = strlen(str) + 1;
    char *tmp = malloc(2 * n * sizeof(char));
    if(tmp)
    {
        strcpy(tmp, str);
    }
    return tmp;
}

node_t *nodefromDB(char *DBline, int **graph)
{
    /* Constructs a graph node from a well-formatted string as found in the
    database file. */

    node_t *tmp = malloc(sizeof tmp); /* temp node to construct */
    char *str; /* temporary pointer for peeking into string */
    int tmp_id, tmp_weight; /* for tokenisation of node links */
    char *tmpstr;

    /* build the node */
    tmp->ID = atoi(strtok(DBline, DELIM_1));
    tmpstr = strtok(NULL, DELIM_1);
    tmp->name = strdup(tmpstr);
    tmp->supplies = encode_supplies(strtok(NULL, DELIM_1));
    graph[tmp->ID][tmp->ID] = 0; /* add to graph */

    /* parse the residue (stuff with N:T,N:T... etc) and store
    the links to other nodes in the graph */
    while ((str = strtok(strtok(NULL, DELIM_1), DELIM_2)) != NULL)
    {
        /* add the connections in graph */
        sscanf(str, "%d" DELIM_3 "%d", &tmp_id, &tmp_weight);
        graph[tmp->ID][tmp_id] = tmp_weight;
    }
    return tmp;
}

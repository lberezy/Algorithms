/* 	helpme.c
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpme.h"




int encode_supplies(char *str) {
	/* Forms a bit-field (int) as per design.txt from valid string of
	supplies. Returns 0 if X is in the input string.

	There's definitely a simpler way to store this information, but
	I wanted to gain some familiarity with C's bitwise operators. */
	int i;
	unsigned int out = 0;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == 'X') return NOHELP;
		switch (str[i]) {
			case BLANKET_C: {
				out |= BLANKETS_B;
				break;
			}
			case FOOD_C: {
				out |= FOOD_B;
				break;
			}
			case WATER_C: {
				out |= WATER_B;
				break;
			}
			case DIGGING_C: {
				out |= DIGGING_B;
				break;
			}			
			case MEDICINE_C: {
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
	int supply_data, node_n, n_nodes = 0;
	/* for tokeniser use */
	char *weight_str;
	char *node_name;
	int node, weight =10;



	/* try to load the database */
	if(argc != 2) {
		printf("Usage: %s filename\n",argv[0]);
		exit(EXIT_FAILURE);
	} else {
		fname = strdup(argv[1]);
		if ((fp = fopen(fname, "r"))== NULL) {
			perror("Error: Could not open file!");
			exit(EXIT_FAILURE);
		}
	}
	puts("Please enter the location of the disaster:");
	scanf("%s", loc_name);

	puts("What kinds of supplies do you need?");
	scanf("%s", supply_string);
	supply_data = encode_supplies(supply_string);
	printf("%d\n", supply_data);

	/* tokenise input DB */

	/* first line contains number of nodes */
	fgets(str_buff, BUFFER_SIZE, fp);
	n_nodes = atoi(str_buff);
	printf("Number of nodes: %d\n", n_nodes);
	/* for each line of the DB, token first two items delimited by */
	while (fgets(str_buff, BUFFER_SIZE, fp) != NULL) {
		node_n = atoi(strtok(str_buff, DELIM_1));
		node_name = strtok(NULL, DELIM_1);
		supply_data = encode_supplies(strtok(NULL, DELIM_1));
		printf("--\nNode: %d\nName: %s\nSupplies: %d\nConnections: \n", node_n, node_name, supply_data);
		/* parse remainder of line with different delimiter */
		while ((weight_str = strtok(strtok(NULL, DELIM_1), DELIM_2)) != NULL) {
			sscanf(weight_str,"%d" DELIM_3 "%d", &node, &weight);
			printf("Node: %d\tTime: %d\n", node, weight);
		}

	}


	/* don't forget to close file */
	/* fclose(fp); */

	return EXIT_SUCCESS;
}

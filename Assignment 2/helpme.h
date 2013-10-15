/*  helpme.h
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/
#ifndef HELPME_H
#define HELPME_H

/* supply character/bit encoding information */

/* 	information on supplies is stored in a bit-field with the following
	format:
	Boolean True for existance of resource.
	..00000XXXXX
	------------
	..00000BFWDM

	– B: blankets											(16) 	10000
	– F: food												(8)		01000
	– W: water												(4)		00100
	– D: digging equipment									(2)		00010
	– M: medicine											(1)		00001
	– X: no supplies or assistance available from this town	(0) 	00000

	Each supply has the integer representation as above and specified in #define
	Requires 5 bits.
*/

/* in hindsight, an enum of just the character codes and no bit-field
stuff would have probably been easier, sorry. */

#define BLANKET_B (1 << 4)	/* n-th bit in field */
#define BLANKET_C 'B'	/* char code representation */
#define FOOD_B (1 << 3)
#define FOOD_C 'F'
#define WATER_B (1 << 2)
#define WATER_C 'W'
#define DIGGING_B (1 << 1)
#define DIGGING_C 'D'
#define MEDICINE_B (1 << 0)
#define MEDICINE_C 'M'
#define NOHELP_C 0
#define NOHELP 0

#define NUM_SUPPLIES 5


/*
typedef enum resource {
	BLANKET_B  = (1 << 4)	
	BLANKET_C = 'B'	
	FOOD_B = (1 << 3)
	FOOD_C = 'F'
	WATER_B = (1 << 2)
	WATER_C = 'W'
	DIGGING_B = (1 << 1)
	DIGGING_C = 'D'
	MEDICINE_B = (1 << 0)
	MEDICINE_C = 'M'
	NOHELP = 0
} relief_t; */

#define BUFFER_SIZE 256

/* delimiters for tokenizing DB input */
#define DELIM_1 "|"
#define DELIM_2 ",\n\r " /* grr, stupid line endings */
#define DELIM_3 ":\n\r "

#define NODE_NOT_FOUND -1

int encode_supplies(char *str);
void print_supplies(int supply_data);
node_t *nodefromDB(char *DBline, int **graph);
int name_to_ID(char *name, node_t **nodes, int num_nodes);
void find_supply(int supply, int dest_ID, int supply_data, node_t **nodes,
                 int **graph, int **next, int num_nodes);

#endif

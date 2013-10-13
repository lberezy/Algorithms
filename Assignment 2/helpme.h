
#ifndef HELPME_H
#define HELPME_H

/* supply character/bit encoding information */

/* 	information on supplies is stored in a bit-field with the following
	format:
	Boolean values for existance of resource.
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
/* would an enum have helped here? */
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
#define NOHELP 0

#define BUFFER_SIZE 256

/* delimiters for tokenizing DB input */
#define DELIM_1 "|"
#define DELIM_2 ",\n\r "
#define DELIM_3 ":\n\r "

int encode_supplies(char *str);
node_t *nodefromDB(char *DBline, int **graph);

#endif

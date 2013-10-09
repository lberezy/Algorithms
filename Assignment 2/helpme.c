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
	char *fname, loc_name[256], supply_string[32];
	FILE *fp;
	int supply_data;

	/* try to load the database */
	if(argc != 2) {
		printf("Usage: %s filename\n",argv[0]);
		exit(EXIT_FAILURE);
	} else {
		fname = strdup(argv[1]);
		if (fp = (FILE*)fopen(fname, "r") == NULL) {
			puts("Couldn't open file!");
			exit(EXIT_FAILURE);
		}
	}
	puts("Please enter the location of the disaster:");
	scanf("%s", loc_name);

	puts("What kinds of supplies do you need?");
	scanf("%s", supply_string);
	supply_data = encode_supplies(supply_string);
	printf("%d", supply_data);

	return EXIT_SUCCESS;
}

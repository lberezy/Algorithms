/* 	graph.h
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/


#define blankets 32
#define food 16
#define water 8
#define digging 4
#define medicine 2
#define noass 1

/* 	information on supplies is stored in a bit-field with the following
	format:
	Boolean values for existance of resource.
	XXXXX000000
	-----------
	XXXXXBFWDMX

	– B: blankets 											(32)
	– F: food												(16)
	– W: water												(8)
	– D: digging equipment 									(4)
	– M: medicine											(2)
	– X: no supplies or assistance available from this town	(1)

	Each supply has the integer representation as above and specified in #define
*/
typedef struct node {
	int time;
	int supplies;
}
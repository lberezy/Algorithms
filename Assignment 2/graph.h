/* 	graph.h
	Part of COMP20003 Project 2
	Author: Lucas Berezy
*/


#define BLANKETS 16
#define FOOD 8
#define WATER 4
#define DIGGING 2
#define MEDICINE 1
#define NOHELP 0

/* 	information on supplies is stored in a bit-field with the following
	format:
	Boolean values for existance of resource.
	..00000XXXXX
	------------
	..00000BFWDM

	– B: blankets											(16)
	– F: food												(8)
	– W: water												(4)
	– D: digging equipment									(2)
	– M: medicine											(1)
	– X: no supplies or assistance available from this town	(0)

	Each supply has the integer representation as above and specified in #define
	This method allows for testing iteratively testing elements (>>= i &..) and 
	multiple elements at a time.
	This bit representation can fit inside a short int to save space.

*/

typedef struct link { /* connects two nodes via time-weighted edge */
	node_t* to, from;
	int time;
} link_t;

typedef struct node { /* represents a source of aid and its connections */
	int supplies;
	link_t* links;
} node_t;

node_t** create_graph(int N)

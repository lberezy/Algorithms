#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv){

	int i,j;

	if(argc != 2) return EXIT_FAILURE;
	int alpha_size = atoi(argv[1]);
	char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int set_size = 1<<alpha_size;
	printf("Set size: %d\n---------",set_size);

	/* initialise an alpha_size * set_size 2D array */
	int **output = (int**)malloc(set_size*sizeof(int*));
	
	for(i=0;i<set_size;i++){
		output[i] = (int*)malloc(alpha_size*sizeof(int));
	}


	/* allocated 2D array */

	 /* ended up not needing it*/

	for(i=0; i < set_size; i++){
		for(j=alpha_size; j>0; j--){
			i&(1<<(j-1)) ? printf("%c",alpha[j-1]) : printf("");
		}
		printf("\n");
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char **argv){

	int i,j;

	if(argc != 2) return EXIT_FAILURE;
	int alpha_size = atoi(argv[1]);

	int set_size = pow(2,alpha_size);
	printf("Set size: %d\n",set_size);

	/* initialise an alpha_size * set_size 2D array */
	int **output = (int**)malloc(set_size*sizeof(int*));
	
	for(i=0;i<set_size;i++){
		output[i] = (int*)malloc(alpha_size*sizeof(int));
	}
	/* allocated 2D array */

	 /* ended up not needing it*/

	for(i=0; i < set_size; i++){
		for(j=alpha_size; j>0; j--){
			i&(1<<(j-1)) ? printf("1") : printf("0");
		}
		printf("\n");
	}
}

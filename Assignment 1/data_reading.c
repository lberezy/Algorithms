#include <stdio.h>
#include <stdlib.h>  /* for exit() */


/* input first from a file (filename specified by #define), then continue
   reading from stdin

   24 July 2013  LStern
*/
  


/* maximum length of line -- expect weird behavior on counting lines if
   length of input string > NUMBER */
#define NUMBER 256


#define INPUT1  "input1"
#define INPUT3  "input3"

#define ERROR 27
#define OK     0

/* any number for debugging output, turn off by setting DEBUG to 0 */
#define DEBUG 0    




int
main(int argc, char **argv)
{

  int    i=0;
  char   line[NUMBER+1];
  FILE  *fp;
  char  *myfile;


  if(argc != 2)
  {
    printf("Usage: program filename\n");
    exit(5);

  }


  if (( myfile = malloc(strlen(argv[1]+1))) == NULL)
  {

	 printf("malloc() error\n");
      exit(5);
  }


  strcpy(myfile,argv[1]); 
   
  if( (fp=fopen(myfile,"r")) ==NULL)
  {
	 printf("Error opening file %s\n", myfile);
      exit(ERROR);
  }


  /* read from file  */
  i=0;
  while(fgets(line, sizeof(line), fp))
    {
	 i++;
	 if(DEBUG) printf("%s", line);
    }
  printf("read %d lines\n", i);

 
  /* now read from stdin */
  i=0;
  while(fgets(line, sizeof(line), stdin))
    {
	 i++;
	 if(DEBUG) printf("%s\n", line);
    }
  printf("read %d lines\n", i);

  return(OK);
}

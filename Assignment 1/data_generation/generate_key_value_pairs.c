#include<stdio.h>
#include<stdlib.h>

/* Generate key-value pairs.  

   Generate list of length chosen by user, with key value pairs.

   Keys are generated randomly within a user-specified range.  Outside
   limits for lower and upper bounds are 1 and length of
   /usr/dict/words (25143).

   Values are taken from /usr/dict/words: for key i, the i-th word in
   /usr/dict/words is the value.

   Note that no effort has been made to remove duplicate key-value pairs.


Linda Stern
31 July 2013
 
 */


#define LINEMAX 256
#define ARGERROR 3

#define DEBUG 0

#define USRDICT_LEN 235886  /* number of words in /usr/dict/words */


main(int argc, char  *argv[])
{
   int listlen, lower, upper, listrange;   

   char    buffer[LINEMAX];
   int     key;
   int i;   


   if(argc != 4)
   {   printf("Usage: datalist n x y,\n n  length of the list\n");
       printf(" x and y are integer lower and upper bounds for index value\n");
	  exit(ARGERROR);
   }                 

   listlen = atoi(argv[1]);
   lower = atoi(argv[2]);
   upper = atoi(argv[3]);
   listrange = upper - lower + 1;

   if(lower < 1 || upper < 1 || listrange < 1)
   {
       printf(" Bounds must be positive numbers, and upper bound"); 
       printf(" must be greater than lower bound\n");
       exit(ARGERROR);
   }
   
   if(upper >=  USRDICT_LEN)
   {
       printf(" Warning: Bound above length of /usr/dict/words\n");
       printf(" Values may not be random\n");
   }

   for(i=0;i<listlen;i++)
    {  
      key = rand()%listrange + lower; 
 
      snprintf(buffer,LINEMAX,"head -%d /usr/share/dict/words | tail -1", key);
      printf("%5d\t",key);  fflush(stdout);
	 system(buffer);
    }
}

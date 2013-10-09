#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define OK 1



int
main()
{

   char   string[] = "abc";
   int    i;  

   printf("Hello world!\n");


   printf("%s\n",string);    

   for(i=0;i<strlen(string);i++) 
   {
      printf("%c\n",string[i]);
      if(string[i]=='b') printf("Matched b\n");

   }
   return(OK);
}


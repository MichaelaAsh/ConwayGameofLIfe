
#include <string.h>
#include <stdio.h>

int chop ( char *line ) {


   int end = strlen (line) - 1;
   int flag;

   while (end == strlen (line) - 1)  {

      if ( line [end] == '\n') {
         line[end] = '\0';
         flag = 0;
      } else {
         flag = -1;
      }
   }

  return(flag);

}; 

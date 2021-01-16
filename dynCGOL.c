#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chop.h"
#define DEAD 0
#define ALIVE 1


#define NOTEQUAL 0


int main ( int argc, char *argv[]) {


  FILE *seedFile;
  FILE *seedFile2;
  FILE *seedFile3;
  char inputSeed[200];


  int currentSeed[200][200];

  int futureSeed [200][200];

  int i,j;
  int ticks = 0;
  int maxTicks = 50;

  int check, check2;
  int neighbours;
  int ROWS;
  int COL;

  if (argc < 5) {

      printf ( "Usage: ./dynCGOL seedfilename.seed ticks ROWS COLS\n" );
      exit ( 1 );
    } else {
      strcpy (inputSeed, argv[1]);
      maxTicks = atoi ( argv[2] );
      ROWS = atoi ( argv[3]);
      COL = atoi ( argv[4] );

   }   /* argument check */





seedFile = fopen (inputSeed, "r");
seedFile2 =  fopen (inputSeed, "r");
seedFile3 =  fopen (inputSeed, "r");

if (seedFile == NULL || seedFile2 == NULL || seedFile3 == NULL) {
  printf("Invalid File\n");
  return(-1);
}


char checksize2 [500];
int countCols = 0;
/* array to number of rows */
while (fgets (checksize2, 500, seedFile) ) {
    countCols++;

}
fclose(seedFile);

int checksize [500];
int countRows = 0;
/* array to get number of elements*/
while ( (fscanf(seedFile2, "%d", &checksize[countRows]) != EOF ) ){
    countRows++;
}
fclose(seedFile2);

int numCols = ( countRows/countCols);



if (ROWS != countCols || COL != numCols) {
  printf("Wrong dimensions\n");
  return(-1);
}


/* copy seedfile into currentSeed */
for (i = 0; i < ROWS; i++){
  for (j = 0; j< COL; j++){
    fscanf(seedFile3, "%d", &currentSeed[i][j]);
    futureSeed[i][j] = currentSeed[i][j];
  }
}

putc (' ', stdout);
 /* print the top of the grid */
  for (j = 0; j < COL; j++){
    printf("-", currentSeed[i][j]);

  }

printf("\n");
printf("|");

/* print out current grid */

for (i = 0; i < ROWS; i++) {
 for (j = 0; j < COL; j++){


    if (currentSeed[i][j] == DEAD) {
      printf(" ");
    }
    if (currentSeed[i][j] == ALIVE ){
       printf("X");
    }

    if (j == COL - 1 ) {
       printf("|\n|");
    }
  }
}

/* print the bottom of the grid  */
for (j = 0; j < COL; j++){
 printf("-", currentSeed[i][j]);
}

putc ('\n', stdout);

char ques1[200];

printf ("Start? (y or n) ");
fgets(ques1, 200, stdin);
chop(ques1);


int flag = 1;

while ( !(strcmp(ques1, "y") == 0 || strcmp(ques1, "n") == 0 ) ) {
 printf("Input is case sensitive (y or n) " );
 printf ("Start? (y or n) ");
 fgets(ques1, 200, stdin);
 chop(ques1);
}

system ("clear");

if (strcmp(ques1, "y") == 0) {

do {
 while (ticks <  maxTicks) {
    system ("clear");


 for (i = 0; i < ROWS; i++) {
      neighbours = 0;
    for (j = 0; j < COL; j++) {
        neighbours = 0; /* reintilaize neighbours every time it loops */
       /*  print the top of the grid */
        if (i == 0 && j == 0) {
           putc (' ', stdout);
          int k;
          for (k = 0; k < COL; k++){
            printf("-");
          }
        }

             for (check = -1; check < 2; check++) {
                 for (check2 = -1; check2 < 2; check2++) {
                     if ((i + check) >= 0 && (i + check) <= ROWS-1 && (j + check2 ) >= 0 && j +check2 <= COL -1) {
                         neighbours = neighbours + (currentSeed [i+check][j+check2]);

                      }
                  }
          }
            neighbours =  neighbours - currentSeed[i][j];

          /* code to check the rules */
          if (neighbours < 2 && currentSeed[i][j] == ALIVE) {
              futureSeed[i][j] = DEAD;
           } else if ( (neighbours == 2 || neighbours == 3) && currentSeed[i][j] == ALIVE){
             futureSeed[i][j] = ALIVE;
           } else if ( neighbours > 3 && currentSeed[i][j] == ALIVE){
             futureSeed[i][j] = DEAD;
           } else if ( neighbours == 3 && currentSeed[i][j] == DEAD) {
             futureSeed[i][j] = ALIVE;
           }

   } /*  end of COL loop   */

 } /* end of ROWS loop */

 flag = 1;
 for (i = 0; i < ROWS; i++){
   for (j = 0; j< COL; j++){
      if (futureSeed[i][j] != currentSeed[i][j]){
        flag = NOTEQUAL;
        break;
      }
   }
 }


 printf("\n| ");

 /* print out currentSeed that will have futureSeed */
  for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COL; j++) {
         /* side grids*/
        if (j == COL - 1) {
           printf("|\n|");
        }
        currentSeed[i][j] = futureSeed[i][j];

        /* print grid */
        if (currentSeed[i][j] == DEAD) {
           printf(" ");
        }
        if (currentSeed[i][j] == ALIVE){
           printf("X");
        }

     } /* end of COl loop */

  }  /* end of ROWS loop */

     ticks++;

   /* print the bottom of the grid  */
    for (j = 0; j < COL; j++){
        if ( j < (COL - 2) ){
          printf("-");
        }
        if ( j == (COL - 1) ){
          printf("- %d", ticks);
        }
      }
     putc ('\n', stdout);
     system ("sleep 0.25");

   if (flag == 1) {
     ticks= maxTicks;
   }

   if (flag == NOTEQUAL && ticks == maxTicks ) {
    char ques2[200];

    printf ("Continue (y or n) ");
    fgets(ques2, 200, stdin);
    chop(ques2);

    while ( !(strcmp(ques2, "y") == 0 || strcmp(ques2, "n") == 0 ) ) {
     printf("Input is case sensitive (y or n) " );
     printf ("Continue? (y or n) ");
     fgets(ques2, 200, stdin);
     chop(ques2);
    }
     if (strcmp(ques2, "y") == 0 ) {
       maxTicks  = 2147483647;
     }
     if (strcmp(ques2, "n") == 0 ) {
       fclose(seedFile3);
       return(-1);
     }
   }


} /* end of while loop */

} while ( flag == NOTEQUAL);


}  /* end of if yes loop */



fclose(seedFile); 



  return (0);
} /* end of program */

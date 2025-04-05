/*
	Name: Lab#2
	Copyright: 2021-22
	Author: Prof. Joao Costa
	Date: 06/04/22 17:24
	Description: 
		Parallelizing an inner loop with dependences
	
			for (iter=0; iter<numiter; iter++) {
				for (i=0; i<size-1; i++) {
					V[i] = f( V[i], V[i+1] );
				}
			}
*/

#include<stdio.h>
#include<stdlib.h>
#include <omp.h>


#define TOTALSIZE 1000
#define NUMITER 200

/*
* DUMMY FUNCTION
*/
#define f(x,y)	((x+y)/2.0)


/* MAIN: PROCESS PARAMETERS */
int main(int argc, char *argv[]) {

  /* VARIABLES */
  int i, iter;

  /* DECLARE VECTOR AND AUX DATA STRUCTURES */
  double *Vtmp = (double *) malloc(TOTALSIZE * sizeof(double));
  double *V = (double *) malloc(TOTALSIZE * sizeof(double));

  /* 1. INITIALIZE VECTOR */
  for(i = 0; i < TOTALSIZE; i++) {
    V[i]= 0.0 + i;
  }
  

  #pragma omp parallel for
  for(i = 0; i < TOTALSIZE-1; i++) {
    Vtmp[i] = f(V[i], V[i+1]);
  }
  V[TOTALSIZE-1] = V[TOTALSIZE-1]; // ou mantenha inalterado

  #pragma omp parallel for
  for(i = 0; i < TOTALSIZE-1; i++) {
    V[i] = Vtmp[i];
  }




  /* 3. OUTPUT FINAL VALUES */
  printf("Output:\n"); 
  for(i = 0; i < TOTALSIZE; i++) {
    printf("%4d %f\n", i, V[i]);
  }

}

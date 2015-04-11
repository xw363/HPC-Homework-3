/******************************************************************************
* FILE: omp_solved4.c
* DESCRIPTION:
*   The original N is too large, and each thread cannot hold a double array
*   of size N*N on its stack if we do not make N smaller.
*   The maximum possible N could vary from system to system.
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/* N made smaller here */
#define N 512

int main (int argc, char *argv[]) 
{
int nthreads, tid, i, j;
double a[N][N];

/* Fork a team of threads with explicit variable scoping */
#pragma omp parallel shared(nthreads) private(i,j,tid,a)
  {

  /* Obtain/print thread info */
  tid = omp_get_thread_num();
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d starting...\n", tid);

  /* Each thread works on its own private copy of the array */
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      a[i][j] = tid + i + j;

  /* For confirmation */
  printf("Thread %d done. Last element= %f\n",tid,a[N-1][N-1]);

  }  /* All threads join master thread and disband */

}


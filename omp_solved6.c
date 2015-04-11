/******************************************************************************
* FILE: omp_solved6.c
* DESCRIPTION:
*   Fix the program by letting dotprod() return a value, and main()
*   receive it.
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN];

float dotprod ()
{
int i,tid;
float sum;

tid = omp_get_thread_num();
/* Fix: add parallel */
#pragma omp parallel for reduction(+:sum)
  for (i=0; i < VECLEN; i++)
    {
    sum = sum + (a[i]*b[i]);
    printf("  tid= %d i=%d\n",tid,i);
    }

/* Fix: return the final sum */
return sum;
}


int main (int argc, char *argv[]) {
int i;
float sum;

for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
sum = 0.0;

/* Fix: assign return value of dotprod() to sum */
#pragma omp parallel shared(sum)
  sum = dotprod();

printf("Sum = %f\n",sum);

}


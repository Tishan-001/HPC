/******************************************************************************
* FILE: omp_workshare2.c
* DESCRIPTION:
*   OpenMP Example - Sections Work-sharing - C Version
*   In this example, the OpenMP SECTION directive is used to assign
*   different array operations to each thread that executes a SECTION. 
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 50

int main (int argc, char *argv[]) 
{
int i, nthreads, tid;
float a[N], b[N], c[N], d[N];

/* Some initializations */
for (i=0; i<N; i++) {
  a[i] = i * 1.5;
  b[i] = i + 22.35;
  c[i] = d[i] = 0.0;
  }

#pragma omp parallel shared(a,b,c,d,nthreads) private(i,tid)
  {
  tid = omp_get_thread_num();
  if (tid == 0)
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d starting...\n",tid);

  #pragma omp sections nowait
    {
    #pragma omp section
      {
      printf("Thread %d doing section 1\n",tid);
      for (i=0; i<N; i++)
        {
        c[i] = a[i] + b[i]; // Section 1: addition
        printf("Thread %d: c[%d]= %f\n",tid,i,c[i]);
        }
      }

    #pragma omp section
      {
      printf("Thread %d doing section 2\n",tid);
      for (i=0; i<N; i++)
        {
        d[i] = a[i] * b[i]; // Section 2: multiplication
        printf("Thread %d: d[%d]= %f\n",tid,i,d[i]);
        }
      }

    }  /* end of sections */

    printf("Thread %d done.\n",tid); 

  }  /* end of parallel section */

}

/*

Suppose you run this with 2 threads:
* Thread 0 does Section 1:
    c[i] = a[i] + b[i];
* Thread 1 does Section 2:
    d[i] = a[i] * b[i];
Each section loops through all i = 0 to 49.

----------------------------------------
| Thread 0        | Thread 1           |
| ----------------| ------------------ |
| Section 1       | Section 2          |
| c[i] = a[i]+b[i]| d[i] = a[i]*b[i]   |
| i = 0..49       | i = 0..49          |
----------------------------------------

*/
/******************************************************************************
* FILE: omp_reduction.c
* DESCRIPTION:
*   OpenMP Example - Combined Parallel Loop Reduction - C/C++ Version
*   This example demonstrates a sum reduction within a combined parallel loop
*   construct.  Notice that default data element scoping is assumed - there
*   are no clauses specifying shared or private variables.  OpenMP will 
*   automatically make loop index variables private within team threads, and
*   global variables shared.
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int   i, n;
float a[100], b[100], sum; 

/* Some initializations */
n = 100;
for (i=0; i < n; i++)
  a[i] = b[i] = i * 1.0;
sum = 0.0;

#pragma omp parallel for reduction(+:sum)
  for (i=0; i < n; i++)
    sum = sum + (a[i] * b[i]);

printf("   Sum = %f\n",sum);

}

/*

* Let’s visualize it assuming 4 threads:

| Thread | i Range | Operation                 | Partial Sum |
| ------ | ------- | ------------------------- | ----------- |
| T0     | 0 – 24  | sum += i*i                | 4900        |
| T1     | 25 – 49 | sum += i*i                | 44875       |
| T2     | 50 – 74 | sum += i*i                | 132250      |
| T3     | 75 – 99 | sum += i*i                | 146325      |
|        |         | Final  sum = T0+T1+T2+T3  | 328350      |


| Concept                    | Explanation                                                                                |
| -------------------------- | ------------------------------------------------------------------------------------------ |
| #pragma omp parallel for   | Splits the loop across threads.                                                            |
| reduction(+:sum)           | Combines each thread’s local sum using +.                                                  |
| sum behavior               | Each thread gets a private copy of sum, which is combined into the final result.           |
| Loop variable i            | Automatically private in OpenMP parallel for.                                              |

*/
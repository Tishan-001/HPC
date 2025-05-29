/******************************************************************************
* FILE: omp_orphan.c
* DESCRIPTION:
*   OpenMP Example - Parallel region with an orphaned directive - C/C++ Version
*   This example demonstrates a dot product  being performed by an orphaned
*   loop reduction construct.  Scoping of the reduction variable is critical.
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN], sum;

float dotprod ()
{
int i,tid;

tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
  for (i=0; i < VECLEN; i++)
    {
    sum = sum + (a[i]*b[i]);
    printf("  tid= %d i=%d\n",tid,i);
    }
}


int main (int argc, char *argv[]) {
int i;

for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
sum = 0.0;

#pragma omp parallel
  dotprod();

printf("Sum = %f\n",sum);

}

/*

* Key point: The loop performing the parallel computation is in a separate function dotprod(), 
  not in main() — making it an orphaned directive.
* The #pragma omp for directive distributes the iterations of a for loop among multiple threads.

What is an Orphaned Directive?

An "orphaned" directive is an OpenMP directive (like #pragma omp for, #pragma omp sections, etc.) 
that appears inside a function, and outside of any explicit parallel region in that function itself.

| Directive              | Starts threads?  | Needs parallel region?                    |
| ---------------------- | ---------------  | ----------------------------------------  |
|  #pragma omp parallel  | ✅ Yes           | No                                        |
|  #pragma omp for       | ❌ No            | ✅ Yes (must be inside a parallel region) |


*/
# OpenMP Directives in C/C++

## 1. Directive Format
```c
#pragma omp directive-name [clause, ...] newline
```

## Components:

| Part         | Description |
|--------------|-------------|
| `#pragma omp` | Required prefix for all OpenMP directives in C/C++ |
| `directive-name` | Specifies the OpenMP operation (e.g., `parallel`, `for`, `sections`) |
| `[clause, ...]` | Optional modifiers (e.g., `private(x)`, `shared(y)`, `reduction(+:sum)`) |
| `newline`     | Mandatory before the structured block |

## Example:
```c
#pragma omp parallel default(shared) private(beta, pi)
{
    // Parallel region
}
```

## 2. General Rules

✔ Case-sensitive (e.g., `#pragma omp parallel`, not `#pragma OMP PARALLEL`).  
✔ Only one directive-name per `#pragma`.  
✔ Applies to only one succeeding statement, which must be a structured block (enclosed in `{}`).  
✔ Line continuation: Use `\` at the end of a line to split long directives.  

```c
#pragma omp parallel default(shared) \
    private(x, y) num_threads(4)  
{  
    // Parallel code  
}
```

## 3. Common Directives

| Directive  | Description |
|-----------|-------------|
| `parallel` | Creates a team of threads |
| `for`      | Splits loop iterations across threads |
| `sections` | Divides work into independent blocks |
| `single`   | Executes block with only one thread |
| `critical` | Ensures mutual exclusion (like a lock) |
| `barrier`  | Synchronizes all threads at a point |
| `atomic`   | Ensures atomic memory update |

## Example Usage

### Parallel Region
```c
#include <omp.h>
#include <stdio.h>

int main() {
    #pragma omp parallel
    {
        printf("Hello from thread %d\n", omp_get_thread_num());
    }
    return 0;
}
```
# OpenMP Key Clauses

## 4. Key Clauses

| Clause | Purpose |
|--------|---------|
| `private(var)` | Each thread gets its own copy of `var` |
| `shared(var)` | All threads access the same `var` |
| `default(shared/none)` | Sets default data-sharing behavior |
| `reduction(op:var)` | Combines results from all threads (e.g., `+`, `*`, `max`) |
| `num_threads(N)` | Specifies the number of threads |
| `schedule(static/dynamic/guided)` | Controls loop iteration distribution |

## Example with Clauses

```c
#include <omp.h>
#define N 1000

int main() {
    double a[N], sum = 0.0;
    // Initialize array a here...
    
    #pragma omp parallel for reduction(+:sum) schedule(dynamic, 10)
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }
    
    printf("Total sum: %f\n", sum);
    return 0;
}
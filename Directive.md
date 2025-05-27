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
```

# OpenMP Directive Scoping

## 1. Key Concepts

### (1) Static (Lexical) Extent
**Definition:** The code textually enclosed between the beginning and end of a structured block following a directive.  
**Characteristics:**  
- Limited to the same function/routine where the directive appears.  
- Does not span multiple files or function calls.  

**Example:**
```c
#include <stdio.h>
#include <omp.h>
#define N 100
#define M 50

// Function prototypes
void sub1();
void sub2();
void work();

int main() {
    int a[N], b[N], c[N];
    // Initialize arrays
    for (int i = 0; i < N; i++) {
        b[i] = i;
        c[i] = i * 2;
    }

    // Static (Lexical) Extent Example
    #pragma omp parallel
    {
        printf("Thread %d: Inside parallel region (static extent)\n", omp_get_thread_num());
        #pragma omp for
        for (int i = 0; i < N; i++) {
            a[i] = b[i] + c[i];
        }
    }
}
```
### (2) Orphaned Directive

**Definition:** A directive that appears outside another enclosing directive's static extent.  

**Characteristics:**  
- Can span multiple routines (functions/subroutines).  
- Still executes within the dynamic extent of a parent parallel region.  

**Example:**  
```c
    // Orphaned Directive Example
    #pragma omp parallel
    {
        sub1(); // Contains orphaned CRITICAL directive
    }
```
### (3) Dynamic Extent

**Definition:** Includes:  
- The static extent of a directive + all orphaned directives executed within it.  

**Example:**  
```c
    // Dynamic Extent Example
    #pragma omp parallel
    {
        sub1(); // Contains orphaned CRITICAL
        sub2(); // Contains orphaned SECTIONS
    }
```
## 2. Why Scoping Matters

### Binding Rules
Directives bind to the nearest enclosing structured block.

**Example:**
```c
    // Binding Rules Example
    #pragma omp parallel
    {
        #pragma omp for // Correctly binds to PARALLEL
        for (int i = 0; i < N; i++) {
            a[i] = b[i] * c[i];
        }
    }
```
### Nesting Rules
Some directives cannot be nested (e.g., DO inside DO without collapse).

**Example of illegal nesting:**
```c
    // Illegal Nesting Example
    #pragma omp parallel for
    {
        #pragma omp for // ERROR: Nested parallel for without collapse
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // Some computation
            }
        }
    }
```
### Correct Usage
Orphaned directives must be in the dynamic extent of a parallel region.

**Example:**
```c
    // Valid Orphaned Directive in Dynamic Extent
    #pragma omp parallel
    {
        work(); // Contains orphaned SECTIONS directive
    }
```

# OpenMP Directives: Parallel Region Construct

## What is a Parallel Region?
A parallel region is like a team project where:
- Normally, one person (the "master thread") does all the work
- In a parallel region, we split the work among multiple team members ("threads")

```c
#pragma omp parallel [options...]
{
    // Code inside this block runs in parallel
    // Multiple threads execute this simultaneously
}
```
## How It Works

When a thread hits `#pragma omp parallel`:

- It becomes the "master" (team leader)
- It recruits other threads to form a team
- All team members (including master) work on the code block together

At the end of the block:

- All threads wait for each other to finish (like a team meeting point)
- Only the master continues after this point

## Controlling Thread Count

OpenMP decides how many threads to use in this order:

1. `if` condition (if present)
2. `num_threads` clause
3. `omp_set_num_threads()` function call
4. `OMP_NUM_THREADS` environment variable
5. Default (usually equals your CPU cores)

## Important Rules

- **No jumping in/out**: Can't use `goto` to enter or exit a parallel block
- **Single block only**: Must be one continuous code block (can't split across functions)
- **Thread safety**: If one thread crashes, all threads stop and results may be unreliable

## Common Options/Clauses

| Clause             | Purpose                                              |
|--------------------|------------------------------------------------------|
| `private(list)`    | Each thread gets its own copy of these variables     |
| `shared(list)`     | All threads share these variables (be careful!)      |
| `num_threads(N)`   | Request exactly N threads                            |
| `if(condition)`    | Only use parallel if condition is true               |
| `reduction(op:list)` | Combine results from all threads (like summing)   |

**Example:**
```c
#include <omp.h>
#include <stdio.h>

int main() {
    int nthreads, tid;
    // Start parallel region - team forms here
    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num(); // Get my thread ID (0 is master)
        printf("Hello from thread %d\n", tid);
        // Only thread 0 (master) does this part
        if (tid == 0) {
            nthreads = omp_get_num_threads(); // Count team members
            printf("We have %d threads total\n", nthreads);
        }
    } // Team meets here, only master continues
    return 0;
}
```
### Key Functions

- **omp_get_thread_num()**:: "Who am I?" (returns thread ID)
- **omp_get_num_threads()**:: "How many of us are there?"
- **omp_set_num_threads(N)**:: "Next time, use N threads"

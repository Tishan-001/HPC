# High Performance Computing (HPC)

## 1. Introduction
High Performance Computing (HPC) refers to the use of supercomputers and parallel processing techniques for solving complex computational problems. HPC systems aggregate computing power to deliver much higher performance than typical desktop computers or servers.

**Key Goals:**
- Solve large-scale scientific, engineering, and business problems.
- Enable simulations, data analysis, and modeling that are otherwise infeasible.

## 2. HPC Architecture

### a. Components
- **Processors (CPUs/GPUs):** Multiple, often thousands or millions, for parallel computation.
- **Memory:** Large and fast, sometimes distributed across nodes.
- **Interconnect:** High-speed networks (e.g., InfiniBand) connecting nodes.
- **Storage:** High-capacity, high-throughput systems for massive datasets.

### b. Types of Architectures
- **Shared Memory:** All processors access a common memory space.
- **Distributed Memory:** Each processor has its own local memory; communication via network.
- **Hybrid:** Combination of both (common in modern HPC clusters).

## 3. Parallel Computing

### a. Concepts
- **Parallelism:** Dividing a task into subtasks processed simultaneously.
- **Scalability:** Ability to efficiently use increasing numbers of processors.
- **Amdahl’s Law:** Limits of parallel speedup due to serial portions of code.

### b. Programming Models
- **MPI (Message Passing Interface):** Standard for distributed memory systems.
- **OpenMP:** For shared memory parallelism.
- **CUDA/OpenCL:** For GPU programming.
- **Hybrid Models:** Combining MPI with OpenMP or CUDA.
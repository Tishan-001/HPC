# Pthreads Overview

## What is a Thread?

A **thread** is an independent stream of instructions that can be scheduled by the operating system. It represents a “procedure” that runs independently from its main program.

In a **multi-threaded** program, multiple procedures (threads) can run simultaneously and/or independently.

## Process vs Thread (UNIX Perspective)

### Process:
A **UNIX process** is created by the OS and requires a fair amount of “overhead”. Processes contain information about program resources and program execution state, including:
- Process & user ID
- Environment variables
- Working directory
- Program instructions
- CPU state (registers, etc.)
- Memory (stack & heap)
- File descriptors
- Signal handling
- Shared libraries
- IPC info (pipes, semaphores, etc.)

### Thread:
A **thread**:
- Exists **within** a process
- Has its own **control flow**
- Is **lightweight**, holding only essential resources:
  - Stack pointer
  - Registers
  - Scheduling properties (priority, policy)
  - Blocked/pending signals
  - Thread-specific data
- Shares the **process's resources** with other threads

![Unix Process](images/unix_process.png)

![Threads within a unix process](images/thread_unix_process.png)

## Key Characteristics

- Threads **share memory and resources** of their parent process.
- Threads are independently **schedulable** by the OS.
- Threads require **synchronization** when accessing shared data.

## Implications of Shared Resources

- **Changes** by one thread (e.g., closing a file) affect others.
- **Pointers** with the same value refer to the same memory.
- **Read/write operations** on shared memory must be synchronized to avoid race conditions.

## What are Pthreads?

**Pthreads** (POSIX threads) are a standardized set of C programming interfaces for creating and managing threads on UNIX systems.

## Why Pthreads?

- Historically, different hardware vendors implemented **proprietary threading APIs**, causing **portability issues**.
- A **standard interface** was needed for cross-platform thread development.

## POSIX Standard

- Defined by **IEEE POSIX 1003.1c (1995)**.
- Pthreads adhere to this standard.
- Most modern UNIX systems support **Pthreads** along with any proprietary thread APIs.

## Key Characteristics

- Implemented via:
  - `pthread.h` header file
  - A thread **library** (may be standalone or part of `libc`)
- Consists of:
  - C **data types**
  - C **function calls** for thread creation, synchronization, and management

## Why Pthreads?

## 1. Lightweight

Threads are **more lightweight** compared to processes. They require **less overhead** from the operating system to create and manage.

### Performance Comparison
![Threads within a unix process](images/performance_table.png)

> ✅ **Conclusion**: `pthread_create()` is significantly faster than `fork()`.

---

## 2. Efficient Communication & Data Exchange

- **Threads share memory** within a process, allowing **zero-copy data exchange** via pointers.
- **MPI** (used in HPC) requires memory copies even in shared memory mode.
- **Pthreads** eliminate this need, providing **higher efficiency**, especially on-node.
- Worst-case: communication reduced to **cache-to-CPU/memory-to-CPU bandwidth**, which is still faster than MPI shared memory.

---

## 3. Additional Benefits of Threading

- **Overlapping CPU and I/O**:
  - One thread can perform computation while another waits for I/O.

- **Priority/Real-time Scheduling**:
  - Higher priority threads can **preempt** lower priority ones.

- **Asynchronous Event Handling**:
  - Threads allow efficient **handling of unpredictable events**.

---

## 4. Real-world Examples

- **Web browsers**: Downloading, rendering, and handling input happen in parallel.
- **Modern operating systems**: Use threads extensively to manage concurrent tasks efficiently.


# Designing Threaded Programs

## Why Use Threads for Parallel Programming?

Modern computers have **multiple cores**, so we can run parts of a program at the same time using **threads**. This is called **parallel programming**.

To benefit from Pthreads, your program should have **independent tasks** that can run **concurrently** (at the same time).

---

## ✅ Good Use Cases for Threads

Threads are useful when your program:

- ⏳ Waits for long I/O (like reading files or waiting for user input)
- 🧠 Uses a lot of CPU in some parts
- 🔔 Needs to handle **unexpected events** (like incoming messages)
- 🚨 Has **high-priority work** that must be done immediately

---

## Common Threading Models

1. **Manager/Worker**  
   - A **manager** thread assigns work to **worker** threads.  
   - Two types:  
     - Static (fixed number of workers)  
     - Dynamic (workers created as needed)

2. **Pipeline**  
   - Work is split into steps, each handled by a different thread.  
   - Like a factory assembly line.

3. **Peer**  
   - All threads (including the creator) do the work together.

---

## Shared Memory Model

- All threads **share the same global memory**.
- But each thread also has its **own private data**.
- You (the programmer) must **protect shared memory** to avoid problems.

---

## Thread-Safeness

- Some functions or libraries are **not thread-safe** (they don’t work properly if used by many threads at once).
- If you're unsure whether a function is thread-safe:
  - ❌ **Do not use it from multiple threads at the same time**
  - ✅ Use a lock or **"serialize"** the calls (one thread at a time)

---

## Thread Limits

- Different systems have **different thread limits**:
  - Max number of threads
  - Default stack size per thread
- A program that works on one system may fail on another due to these differences.

> 🔍 Tip: Always test your threaded program on your actual target system.

---
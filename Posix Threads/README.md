# Pthreads Overview

## What is a Thread?

A **thread** is an independent stream of instructions that can be scheduled by the operating system. It represents a “procedure” that runs independently from its main program.

In a **multi-threaded** program, multiple procedures (threads) can run simultaneously and/or independently.

## Process vs Thread (UNIX Perspective)

### Process:
A **UNIX process** is created by the OS and includes:
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
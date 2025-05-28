# Mutex Variables Overview (Beginner-Friendly Notes)

## What is a Mutex?
- **Mutex** stands for **Mutual Exclusion**.
- It's a **lock** that protects **shared data** accessed by multiple threads.
- Only **one thread at a time** can own the mutex.
- Prevents **race conditions** and ensures **thread synchronization**.

## Why Use Mutex?
- To protect **critical sections** (shared data).
- Ensures that **only one thread updates** shared data at a time.
- Prevents inconsistent results due to simultaneous writes.

## Example: Race Condition Without Mutex

![Mutex table](images/mutex_table.png)

🔴 Both threads read the same value and write the same final result — **losing one update**!

✅ This can be fixed using a **mutex** to protect access to the balance.

## Typical Mutex Usage Steps

1. **Create and initialize** a mutex.
2. Threads **attempt to lock** the mutex.
3. One thread **succeeds** and becomes the owner.
4. That thread **performs actions** on shared data.
5. It then **unlocks** the mutex.
6. Another thread acquires the lock and **repeats** the process.
7. Finally, the mutex is **destroyed** when no longer needed.

## Blocking vs Non-blocking

- `pthread_mutex_lock`: blocks if mutex is already locked.
- `pthread_mutex_trylock`: does **not block**, just checks.

# Creating and Destroying Mutexes

Routines:

`pthread_mutex_init(mutex, attr)`

`pthread_mutex_destroy(mutex)`

`pthread_mutexattr_init(attr)`

`pthread_mutexattr_destroy(attr)`

## 📌 What is a Mutex?
A **mutex** (mutual exclusion) is a lock used to **protect shared resources** from concurrent access by multiple threads.

## 🔨 Creating a Mutex

### Two Ways to Initialize a Mutex

1. **Static Initialization** (at declaration):
```c
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
```
2. **Dynamic Initialization** (at runtime):
```c
pthread_mutex_t mymutex;
pthread_mutex_init(&mymutex, NULL); // NULL uses default attributes
```
🔓 Note: A newly created mutex is unlocked by default.

## ⚙️ Using Mutex Attributes

### Types of Mutex Attributes:

To customize mutex behavior, use `pthread_mutexattr_t` and related functions.
```c
pthread_mutexattr_t attr;
pthread_mutexattr_init(&attr);
// set attributes here (optional)
pthread_mutex_init(&mymutex, &attr);
```
## 🧹 Destroying Mutexes

When you are done with a mutex:
```c
pthread_mutex_destroy(&mymutex);
```
If you used custom attributes:
```c
pthread_mutexattr_destroy(&attr);
```
Destroying cleans up resources and is good practice.

# Locking and Unlocking Mutexes

Routines:

`pthread_mutex_lock(mutex)`

`pthread_mutex_trylock(mutex)`

`pthread_mutex_unlock(mutex)`

## Purpose:
Mutexes are used to protect **shared data** from being accessed by multiple threads at the same time. Only one thread can **own (lock)** a mutex at a time.

## Main Routines:

### 🔒 1. Locking a Mutex
```c
pthread_mutex_lock(&mutex);
```
- If the mutex is already locked, the calling thread waits (blocks) until it becomes available.
- Once acquired, the thread owns the mutex.

### 🏃 2. Try Locking a Mutex
```c
pthread_mutex_trylock(&mutex);
```
- Non-blocking version.
- If the mutex is already locked:
    - Returns immediately with an error (EBUSY).
- Useful to avoid deadlocks.

### 🔓 3. Unlocking a Mutex
```c
pthread_mutex_unlock(&mutex);
```
- Releases the mutex.
- Only the owning thread can unlock.
- Error returned if:
    - The mutex is already unlocked.
    - It is owned by another thread.

### ⚠️ Important Notes:

- Mutexes are like a “gentleman’s agreement” between threads: there’s no automatic enforcement.
- The programmer must ensure that:
    - Threads lock before accessing shared data.
    - Threads unlock when done.

### 🧪 Example Error Scenario:

| Thread 1 | Thread 2  | Thread 3   |
| -------- | --------- | ---------- |
| Lock     |           |            |
| A = 2    |           |            |
| Unlock   |           |            |
|          | Lock      |            |
|          | A = A + 1 |            |
|          | Unlock    |            |
|          |           | A = A \* B |

✅ If Thread 3 accesses A without locking, it can cause race conditions.

### ❓ Common Question:

Q: When more than one thread is waiting for a locked mutex, which one gets it first when released?

🅰️ Answer:

This is implementation-dependent. POSIX does not guarantee any specific order (like FIFO). It could be:
- First-come, first-served
- Priority-based
- Random

So don’t rely on a specific order. Always design for safety, not assumptions.
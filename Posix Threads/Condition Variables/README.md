# Condition Variables (Pthreads)

## 🔍 What is it?
Condition variables allow **threads to wait** for **certain conditions** (like a variable reaching a value) **without constantly checking (polling)**.

Think of it like:  
> “Don’t call me, I’ll wait until someone notifies me when the time is right.”

---

## 🤝 Used With:
Always used **together with a mutex** to protect shared data.

---

## 🧱 Why Use It?
Without condition variables, threads would need to **keep checking** a condition (polling) which:
- Wastes CPU
- Needs the mutex locked while checking
- Is not efficient

Condition variables help threads **sleep and wait** until notified by another thread.

## Example Use Case (Thread A waits, Thread B signals):

### 🧵 Thread A:
1. Lock the mutex  
2. Check the condition  
3. If condition not met, call:
   ```c
   pthread_cond_wait(&cond, &mutex);
   ```
    This:
    - Releases the mutex
    - Sleeps until signaled
    - Re-acquires the mutex when woken up
    - Unlock the mutex
    - Continue work

### 🧵 Thread B:
1. Lock the mutex
2. Change the value that A is waiting on
3. If condition is now true, call:
    ```c
    pthread_cond_signal(&cond);
    ```
    - Wakes up one waiting thread (A)

4. Unlock the mutex
5. Continue work

## 🔧 Key Functions:

| Function                           | Description                                        |
| ---------------------------------- | -------------------------------------------------- |
| `pthread_cond_wait(&cond, &mutex)` | Makes thread wait for condition and releases mutex |
| `pthread_cond_signal(&cond)`       | Wakes up one thread waiting on condition           |
| `pthread_cond_broadcast(&cond)`    | Wakes up **all** waiting threads                   |

# Creating and Destroying Condition Variables

## 🔧 What is a Condition Variable?
- A condition variable lets threads wait for something to happen and signal when it does.
- It works together with a mutex to safely handle shared data.

## ✅ How to Declare and Initialize

You must declare it as:
```c
pthread_cond_t mycond;
```

There are 2 ways to initialize:
1. Static Initialization
    ```c
    pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;
    ```
2. Dynamic Initialization
    ```c
    pthread_cond_t mycond;
    pthread_cond_init(&mycond, NULL); // NULL = use default settings
    ```
    - You can also use an attribute object if needed (very rare for beginners).

## 🛠️ Optional Attributes

- Attribute type: pthread_condattr_t
- Only 1 special attribute exists:
    `process-shared → allows use across multiple processes`
- Use these functions for attribute handling:
    ```c
    pthread_condattr_init(&attr);      // Create attribute object
    pthread_condattr_destroy(&attr);   // Destroy when done
    ```
## 🧹 Destroying Condition Variables

When you’re done using a condition variable:
```c
pthread_cond_destroy(&mycond);
```
This frees resources — always clean up if created dynamically.

# Waiting and Signaling on Condition Variables

## 🔁 Purpose

Condition variables let threads wait for a condition to be true, and wake up when another thread signals them.

### 🛑 pthread_cond_wait()
- Used to block (pause) a thread until it's signaled.
- Must be used while holding a mutex lock:
    ```c
    pthread_mutex_lock(&mutex);
    while (condition is false) {
        pthread_cond_wait(&cond, &mutex); // Automatically unlocks mutex while waiting
    }
    // Mutex automatically re-locked when thread wakes up
    pthread_mutex_unlock(&mutex);
    ```

## 🔁 Why use while (not if)?

Prevents bugs like:
- Waking up due to wrong signal
- Spurious wakeups (Pthreads allows these)
- Another thread changing the condition before this one gets the mutex

## 📢 pthread_cond_signal()
- Wakes up one waiting thread.
- Must be used after locking the mutex:
    ```c
    pthread_mutex_lock(&mutex);
    condition = true;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    ```
## 📡 pthread_cond_broadcast()

Use this to wake up all waiting threads (not just one):
```c
pthread_cond_broadcast(&cond);
```

### ⚠️ Common Mistakes to Avoid

| Action                     | Description                           |
| -------------------------- | ------------------------------------- |
| `pthread_cond_wait()`      | Wait for a condition (mutex required) |
| `pthread_cond_signal()`    | Wake up **one** waiting thread        |
| `pthread_cond_broadcast()` | Wake up **all** waiting threads       |

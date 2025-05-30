#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int item_available = 0; // Shared variable

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    sleep(2); // Simulate time to produce something

    pthread_mutex_lock(&mutex);
    item_available = 1; // Item is ready!
    printf("Producer: Item is ready. Signaling consumer...\n");

    pthread_cond_signal(&cond); // Signal the consumer
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);
    while (item_available == 0) { // Use WHILE to re-check condition
        printf("Consumer: No item yet. Waiting...\n");
        pthread_cond_wait(&cond, &mutex); // Wait and unlock mutex
    }

    printf("Consumer: Got the item! Processing...\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, consumer, NULL);
    pthread_create(&t2, NULL, producer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}

/*

How It Works:

1. Consumer locks the mutex and checks if an item is available.
2. Since no item yet, it waits on the condition variable (this also unlocks the mutex temporarily).
3. Producer produces an item, locks the mutex, sets item_available = 1, and signals the condition.
4. Consumer is woken up, mutex is re-locked, and it checks the condition again.
5. It finds the item, processes it, and unlocks the mutex.

| Function                  | Meaning                                  |
| ------------------------- | -----------------------------------------|
| pthread_join(t1, NULL);   | Wait main thread for thread t1 to finish |
| pthread_join(t2, NULL);   | Wait main thread for thread t2 to finish |

*/
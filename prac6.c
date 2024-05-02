#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;

void increment() {
  // Lock the mutex before accessing the shared counter
  pthread_mutex_lock(&mutex);

  counter++;

  // Unlock the mutex after accessing the shared counter
  pthread_mutex_unlock(&mutex);
}

void* worker(void* arg) {
  // Perform increment 1000 times
  for (int i = 0; i < 1000; i++) {
    increment();
  }

  pthread_exit(NULL);
}

int main(int argc, char* argv) {
  int num_threads = 2; // Modify as needed

  // Initialize the mutex lock
  if (pthread_mutex_init(&mutex, NULL) != 0) {
    perror("Mutex initialization failed");
    exit(1);
  }

  // Create threads
  pthread_t threads[num_threads];
  for (int i = 0; i < num_threads; i++) {
    if (pthread_create(&threads[i], NULL, worker, NULL) != 0) {
      perror("Thread creation failed");
      exit(1);
    }
  }

  // Wait for all threads to finish
  for (int i = 0; i < num_threads; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("Thread join failed");
      exit(1);
    }
  }

  // Destroy the mutex lock
  pthread_mutex_destroy(&mutex);

  printf("Final counter value: %d\n", counter);

  return 0;
}


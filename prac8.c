#include <stdio.h>
#include <omp.h>
#include <unistd.h>

void task1() {
  printf("Task 1: Performing calculations...\n");
  // Simulate some calculations by sleeping for a short duration
  #pragma omp barrier
  sleep(1); // Adjust sleep time as needed
  printf("Task 1 finished.\n");
}

void task2() {
  printf("Task 2: Reading data from a file...\n");
  // Simulate reading data by sleeping for a short duration
  #pragma omp barrier
  sleep(2); // Adjust sleep time as needed
  printf("Task 2 finished.\n");
}

int main() {
  int num_threads;

  // Get the number of threads available
  #pragma omp parallel num_threads(2) // Request 2 threads
  {
    num_threads = omp_get_num_threads();

    #pragma omp sections nowait // Execute sections concurrently without waiting
    {
      #pragma omp section
      {
        task1();
      }
      #pragma omp section
      {
        task2();
      }
    }
  }

  printf("Number of threads used: %d\n", num_threads);

  return 0;
}


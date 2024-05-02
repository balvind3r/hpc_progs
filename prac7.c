#include <stdio.h>
#include <omp.h>

int main() {
  int num_threads;

  // Get the number of threads available
  #pragma omp parallel num_threads(4)  // Request 4 threads (modify as needed)
  {
    num_threads = omp_get_num_threads();
    printf("Hello World from thread %d of %d\n", omp_get_thread_num(), num_threads);
  }

  return 0;
}


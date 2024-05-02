#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *runner(void *param) {
  // Argument passed to the thread (thread number)
  long int num = (long int)param;

  long int fib1 = 0, fib2 = 1, next;

  // Print Fibonacci series up to 'num'th term (0-based indexing)
  if (num > 1) {
    printf("Fibonacci Series: ");
    printf("%ld, %ld, ", fib1, fib2);
    for (int i = 2; i < num; i++) {
      next = fib1 + fib2;
      printf("%ld, ", next);
      fib1 = fib2;
      fib2 = next;
    }
  } else if (num == 1) {
    printf("Fibonacci Series: 0\n");
  } else {
    printf("Fibonacci Series: \n"); // Empty series for num <= 0
  }

  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  long int num;
  pthread_t tid;

  // Get the number of terms from the user (modify for default value)
  if (argc != 2) {
    printf("Usage: %s <number_of_terms>\n", argv[0]);
    return 1;
  }

  num = atol(argv[1]);

  // Create a new thread
  if (pthread_create(&tid, NULL, runner, (void *)num) != 0) {
    perror("pthread_create failed");
    return 1;
  }

  // Wait for the thread to finish
  if (pthread_join(tid, NULL) != 0) {
    perror("pthread_join failed");
    return 1;
  }

  printf("\n"); // Newline after thread execution

  return 0;
}


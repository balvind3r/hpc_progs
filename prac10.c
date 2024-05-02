#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 5

int main() {
    int i, tid;
    int array[ARRAY_SIZE];

    // Initialize the array
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    // Default loop scheduling
    printf("Default loop scheduling:\n");
    #pragma omp parallel private(i, tid)
    {
        tid = omp_get_thread_num();
        #pragma omp for
        for (i = 0; i < ARRAY_SIZE; i++) {
            printf("Thread %d: array[%d] = %d\n", tid, i, array[i]);
        }
    }

    // Static loop scheduling with chunk size 10
    printf("\nStatic loop scheduling with chunk size 10:\n");
    #pragma omp parallel private(i, tid)
    {
        tid = omp_get_thread_num();
        #pragma omp for schedule(static, 10)
        for (i = 0; i < ARRAY_SIZE; i++) {
            printf("Thread %d: array[%d] = %d\n", tid, i, array[i]);
        }
    }

    // Dynamic loop scheduling with chunk size 10
    printf("\nDynamic loop scheduling with chunk size 10:\n");
    #pragma omp parallel private(i, tid)
    {
        tid = omp_get_thread_num();
        #pragma omp for schedule(dynamic, 10)
        for (i = 0; i < ARRAY_SIZE; i++) {
            printf("Thread %d: array[%d] = %d\n", tid, i, array[i]);
        }
    }

    return 0;
}


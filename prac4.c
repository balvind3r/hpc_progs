#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 10

void quicksort(int *array, int left, int right);
int partition(int *array, int left, int right);
void swap(int *a, int *b);

int main(int argc, char *argv[]) {
    int rank, size;
    int array[ARRAY_SIZE];
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter %d elements: ", ARRAY_SIZE);
        for (i = 0; i < ARRAY_SIZE; i++) {
            scanf("%d", &array[i]);
        }
    }

    // Broadcast the array to all processes
    MPI_Bcast(array, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform quicksort
    quicksort(array, 0, ARRAY_SIZE - 1);

    // Gather sorted array from all processes
    int *sortedArray = NULL;
    if (rank == 0) {
        sortedArray = (int *)malloc(ARRAY_SIZE * sizeof(int));
    }
    MPI_Gather(array, ARRAY_SIZE, MPI_INT, sortedArray, ARRAY_SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    // Print sorted array in rank 0
    if (rank == 0) {
        printf("Sorted array: ");
        for (i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", sortedArray[i]);
        }
        printf("\n");
        free(sortedArray);
    }

    MPI_Finalize();
    return 0;
}

void quicksort(int *array, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(array, left, right);
        quicksort(array, left, pivotIndex - 1);
        quicksort(array, pivotIndex + 1, right);
    }
}

int partition(int *array, int left, int right) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[right]);
    return i + 1;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


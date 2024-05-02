#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

int main(){
    int matrix1[SIZE][SIZE] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    int matrix2[SIZE][SIZE] = {
        {9,8,7},
        {6,5,4},
        {3,2,1}
    };

    int result[SIZE][SIZE];
    int i, j, k;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for(i = 0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            result[i][j] = 0;
            for(k = 0; k < SIZE; k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;

    printf("Matrix 1:\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }
    printf("Matrix 2:\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }
    printf("Result Matrix:\n");
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    printf("\nMultiplication completed in %f seconds\n", cpu_time_used);

    return 0;
}
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 4

void gauss_elimination(float A[N][N], float B[N]) {
    int i, j, k;
    float factor;

    #pragma omp parallel for private(i, j, k, factor) shared(A, B)
    for (k = 0; k < N-1; k++) {
        for (i = k+1; i < N; i++) {
            factor = A[i][k] / A[k][k];
            for (j = k; j < N; j++) {
                A[i][j] = A[i][j] - factor * A[k][j];
            }
            B[i] = B[i] - factor * B[k];
        }
    }
}

int main() {
    float A[N][N] = {{2, -1, 1, 3},
                     {4, 5, -2, 2},
                     {1, 2, 3, -1},
                     {5, 4, 3, 2}};
    float B[N] = {8, 4, 10, 2};

    // Measure time
    clock_t start = clock();

    gauss_elimination(A, B);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Resultant matrix after Gaussian Elimination:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }

    printf("\nResultant vector B:\n");
    for (int i = 0; i < N; i++) {
        printf("%f ", B[i]);
    }
    printf("\n");

    printf("\nExecution time: %f seconds\n", time_spent);

    return 0;
}

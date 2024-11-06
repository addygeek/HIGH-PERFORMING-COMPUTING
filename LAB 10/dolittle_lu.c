#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 4

void dolittle_lu(float A[N][N], float L[N][N], float U[N][N]) {
    int i, j, k;
    
    #pragma omp parallel for private(i, j, k)
    for (i = 0; i < N; i++) {
        // Upper Triangular Matrix U
        for (k = i; k < N; k++) {
            float sum = 0;
            for (j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        // Lower Triangular Matrix L
        for (k = i; k < N; k++) {
            if (i == k) {
                L[i][i] = 1; // Diagonal as 1
            } else {
                float sum = 0;
                for (j = 0; j < i; j++) {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

int main() {
    float A[N][N] = {{2, -1, 1, 3},
                     {4, 5, -2, 2},
                     {1, 2, 3, -1},
                     {5, 4, 3, 2}};
    float L[N][N], U[N][N];
    
    // Measure time
    clock_t start = clock();

    dolittle_lu(A, L, U);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Matrix L (Lower Triangular):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", L[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix U (Upper Triangular):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%f ", U[i][j]);
        }
        printf("\n");
    }

    printf("\nExecution time: %f seconds\n", time_spent);

    return 0;
}

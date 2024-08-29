#include <omp.h>
#include <stdio.h>

#define NUM_ITERATIONS 10

void critical_demo() {
    printf("\nSynchronization (critical section) demonstration:\n");

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            #pragma omp critical
            {
                printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Time taken for critical section demo: %f seconds\n", end_time - start_time);
}

int main() {
    omp_set_num_threads(4);
    critical_demo();
    return 0;
}


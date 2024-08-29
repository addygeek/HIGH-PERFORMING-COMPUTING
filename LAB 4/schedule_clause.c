#include <omp.h>
#include <stdio.h>

#define NUM_ITERATIONS 10

void schedule_demo() {
    printf("Schedule clause demonstration:\n");

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static, 2)
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
        }
    }

    double end_time = omp_get_wtime();
    printf("Time taken for schedule demo: %f seconds\n", end_time - start_time);
}

int main() {
    omp_set_num_threads(4);
    schedule_demo();
    return 0;
}


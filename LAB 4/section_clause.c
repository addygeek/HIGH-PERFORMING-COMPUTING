#include <omp.h>
#include <stdio.h>

void sections_demo() {
    printf("\nSections clause demonstration:\n");

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Section 1 started by thread %d\n", omp_get_thread_num());
                for (int i = 0; i < 1000000; ++i);
                printf("Section 1 completed by thread %d\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Section 2 started by thread %d\n", omp_get_thread_num());
                for (int i = 0; i < 1000000; ++i);
                printf("Section 2 completed by thread %d\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Section 3 started by thread %d\n", omp_get_thread_num());
                for (int i = 0; i < 1000000; ++i);
                printf("Section 3 completed by thread %d\n", omp_get_thread_num());
            }
        }
    }

    double end_time = omp_get_wtime();
    printf("Time taken for sections demo: %f seconds\n", end_time - start_time);
}

int main() {
    omp_set_num_threads(3);
    sections_demo();
    return 0;
}


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ITERATIONS 10
#define NUM_SECTIONS 3

// Function to demonstrate different scheduling strategies
void schedule_demo() {
    printf("Schedule clause demonstration:\n");

    // Record start time
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static, 2) // Static scheduling with chunk size of 2
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
        }
    }

    // Record end time and calculate duration
    double end_time = omp_get_wtime();
    printf("Time taken for schedule demo: %f seconds\n", end_time - start_time);
}

// Function to demonstrate sections and synchronization
void sections_demo() {
    printf("\nSections and synchronization demonstration:\n");

    // Record start time
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Section 1 started by thread %d\n", omp_get_thread_num());
                // Critical section to ensure thread safety
                #pragma omp critical
                {
                    printf("Critical section in section 1, thread %d\n", omp_get_thread_num());
                }
                printf("Section 1 completed by thread %d\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Section 2 started by thread %d\n", omp_get_thread_num());
                // Critical section to ensure thread safety
                #pragma omp critical
                {
                    printf("Critical section in section 2, thread %d\n", omp_get_thread_num());
                }
                printf("Section 2 completed by thread %d\n", omp_get_thread_num());
            }

            #pragma omp section
            {
                printf("Section 3 started by thread %d\n", omp_get_thread_num());
                // Critical section to ensure thread safety
                #pragma omp critical
                {
                    printf("Critical section in section 3, thread %d\n", omp_get_thread_num());
                }
                printf("Section 3 completed by thread %d\n", omp_get_thread_num());
            }
        } // End of sections
    } // End of parallel region

    // Record end time and calculate duration
    double end_time = omp_get_wtime();
    printf("Time taken for sections demo: %f seconds\n", end_time - start_time);
}

int main() {
    // Initialize OpenMP environment
    omp_set_num_threads(4); // Set the number of threads to 4

    // Call functions to demonstrate OpenMP features
    schedule_demo();
    sections_demo();

    return 0;
}


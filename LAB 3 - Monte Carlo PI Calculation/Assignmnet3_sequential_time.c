#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define NP 100000

int main() {
    int count_inside_all_points = 0;
    double x, y;
    double start_time, end_time;

    // Start measuring time
    start_time = omp_get_wtime();
    
    // Sequential computation
    for (int i = 0; i < NP; i++) {
        // Generate random point (x, y)
        x = 2.0 * rand() / RAND_MAX - 1.0;
        y = 2.0 * rand() / RAND_MAX - 1.0;
        
        // Circle Equation to check if the point lies inside or not
        if (x*x + y*y <= 1.0) {
            count_inside_all_points++;
        }
    }
    
    // End measuring time
    end_time = omp_get_wtime();
    
    // Calculate the estimated value of π
    double pi_estimate = 4.0 * count_inside_all_points / NP;
    
    // Print the result
    printf("Estimated value of π (pi): %2.7f\n", pi_estimate);
    
    // Print the elapsed time
    printf("Time taken (sequential): %f seconds\n", end_time - start_time);
    
    return 0;
}
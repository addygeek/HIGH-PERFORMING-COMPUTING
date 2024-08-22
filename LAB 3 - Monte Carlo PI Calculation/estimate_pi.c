#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define NP 100000  // Number of random points

int main() {
    int count_inside = 0;  // Counter for points inside the circle
    double x, y;  // Coordinates of random points
    
    // Open file for writing the points
    FILE *file = fopen("points.dat", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing\n");
        return 1;
    }
    
    // Initialize OpenMP parallel region
    #pragma omp parallel private(x, y) reduction(+:count_inside)
    {
        // Initialize random seed based on thread number
        unsigned int seed = omp_get_thread_num();  // Different seed for each thread
        
        // Parallel for loop to generate random points and check if inside the circle
        #pragma omp for
        for (int i = 0; i < NP; i++) {
            // Generate random point (x, y) within the square [-1, 1] x [-1, 1]
            x = 2.0 * rand_r(&seed) / RAND_MAX - 1.0;
            y = 2.0 * rand_r(&seed) / RAND_MAX - 1.0;
            
            // Check if the point is inside the circle of radius 1
            if (x * x + y * y <= 1.0) {
                count_inside++;  // Increment count if point is inside the circle
                fprintf(file, "%f %f\n", x, y);  // Write point to file
            } else {
                fprintf(file, "%f %f\n", x, y);  // Write point to file
            }
        }
    }
    
    // Close the file
    fclose(file);
    
    // Calculate the estimated value of π
    double pi_estimate = 4.0 * count_inside / NP;
    
    // Print the result
    printf("Estimated value of π: %.2f\n", pi_estimate);
    
    // Generate the plot using GNUplot
    FILE *gnuplot = popen("gnuplot -persistent", "w");
    if (gnuplot == NULL) {
        fprintf(stderr, "Error opening GNUplot\n");
        return 1;
    }
    
    // Plot the points
    fprintf(gnuplot, "set title 'Monte Carlo Simulation of π'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");
    fprintf(gnuplot, "set xrange [-1:1]\n");
    fprintf(gnuplot, "set yrange [-1:1]\n");
    fprintf(gnuplot, "set size square\n");
    fprintf(gnuplot, "plot 'points.dat' with points pt 1 lc rgb 'blue' title 'Points'\n");
    
    // Close GNUplot
    pclose(gnuplot);
    
    return 0;
}

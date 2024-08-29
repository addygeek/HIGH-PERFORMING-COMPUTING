#include <iostream>
#include <omp.h>
#include <vector>
#include <numeric>  // For std::accumulate

#define N 100  // Number of elements in each vector

int main() {
    std::vector<double> a(N);
    std::vector<double> b(N);

    // Initialize vectors a and b
    std::iota(a.begin(), a.end(), 0); // Fill vector a with values 0, 1, 2, ..., N-1
    std::iota(b.begin(), b.end(), 0); // Fill vector b with values 0, 1, 2, ..., N-1

    double dot_product = 0.0;

    // Parallelize the dot product calculation using OpenMP
    #pragma omp parallel for reduction(+:dot_product)
    for (int i = 0; i < N; ++i) {
        dot_product += a[i] * b[i];
    }

    std::cout << "The dot product is " << dot_product << std::endl;

    return 0;
}

#include <iostream>
#include <thread>
#include <vector>
#include <numeric>  // For std::accumulate
#include <barrier>  // C++20 barrier

#define N 100  // Number of elements in each vector
#define P 4    // Number of threads

std::vector<double> a(N); // Vector a[N]
std::vector<double> b(N); // Vector b[N]
std::vector<double> partial_sums(P, 0.0); // Partial sums for dot product
std::vector<double> cross_product_results(3, 0.0); // Results for cross product

// Barrier for synchronization
std::barrier<> bar(P);

void parallel_dot_product(int thread_id) {
    int start = (N / P) * thread_id;
    int end = (N / P) * (thread_id + 1);
    double sum = 0.0;

    for (int i = start; i < end; ++i) {
        sum += a[i] * b[i];
    }
    
    partial_sums[thread_id] = sum;
    bar.arrive_and_wait(); // Synchronize with other threads
}

void parallel_cross_product(int thread_id) {
    if (N == 3) {  // Cross product is only defined for 3D vectors
        if (thread_id == 0) cross_product_results[0] = a[1] * b[2] - a[2] * b[1];
        if (thread_id == 1) cross_product_results[1] = a[2] * b[0] - a[0] * b[2];
        if (thread_id == 2) cross_product_results[2] = a[0] * b[1] - a[1] * b[0];
    }
    bar.arrive_and_wait(); // Synchronize with other threads
}

int main() {
    // Initialize vectors a and b (Example: Fill with values 0 to N-1)
    std::iota(a.begin(), a.end(), 0); // Fill vector a with values 0, 1, 2, ..., N-1
    std::iota(b.begin(), b.end(), 0); // Fill vector b with values 0, 1, 2, ..., N-1

    std::vector<std::thread> threads;

    // Create threads for parallel dot product
    for (int i = 0; i < P; ++i) {
        threads.emplace_back(parallel_dot_product, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // Compute the final dot product
    double dot_product = std::accumulate(partial_sums.begin(), partial_sums.end(), 0.0);
    std::cout << "The dot product is " << dot_product << std::endl;

    // Create threads for parallel cross product (only if N == 3)
    if (N == 3) {
        threads.clear();
        for (int i = 0; i < 3; ++i) {
            threads.emplace_back(parallel_cross_product, i);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        // Output the cross product result
        std::cout << "The cross product is [" 
                  << cross_product_results[0] << ", " 
                  << cross_product_results[1] << ", " 
                  << cross_product_results[2] << "]" << std::endl;
    } else {
        std::cout << "Cross product computation skipped as N != 3" << std::endl;
    }

    return 0;
}

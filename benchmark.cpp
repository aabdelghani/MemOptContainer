#include <iostream>
#include <vector>
#include <chrono>
extern "C" {
#include "custom_array.h"  // Include your custom array header
}

/**
 * Benchmark the performance of std::vector.
 * 
 * @param numElements Number of elements to benchmark
 */
void benchmarkStdVector(size_t numElements) {
    std::vector<int> vec;
    auto start = std::chrono::high_resolution_clock::now();

    // Insertion
    for (size_t i = 0; i < numElements; ++i) {
        vec.push_back(i);
    }

    // Access
    for (size_t i = 0; i < numElements; ++i) {
        int value = vec[i];
    }

    // Deletion
    for (size_t i = 0; i < numElements; ++i) {
        vec.pop_back();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "std::vector: " << duration.count() << " seconds\n";
}

/**
 * Benchmark the performance of CustomArray.
 * 
 * @param numElements Number of elements to benchmark
 */
void benchmarkCustomArray(size_t numElements) {
    CustomArray array;
    initArray(&array, numElements);

    auto start = std::chrono::high_resolution_clock::now();

    // Insertion
    for (size_t i = 0; i < numElements; ++i) {
        insertElement(&array, i);
    }

    // Access
    for (size_t i = 0; i < numElements; ++i) {
        int value = getElement(&array, i);
    }

    // Deletion
    for (size_t i = 0; i < numElements; ++i) {
        deleteElement(&array, 0);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "CustomArray: " << duration.count() << " seconds\n";

    freeArray(&array);
    destroyMemoryPool();
}

/**
 * Main function to run the benchmarks.
 */
int main() {
    const size_t numElements = 1000;

    std::cout << "Benchmarking std::vector...\n";
    benchmarkStdVector(numElements);

    std::cout << "Benchmarking CustomArray...\n";
    initMemoryPool(sizeof(int) * numElements, numElements);  // Initialize memory pool
    benchmarkCustomArray(numElements);

    return 0;
}


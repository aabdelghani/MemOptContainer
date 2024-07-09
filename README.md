
Custom Array Project
====================

Overview
--------
This project implements a custom dynamic array in C with advanced memory handling. 
It includes a garbage collection mechanism to reclaim memory from deleted elements 
and uses a memory pool to manage small memory allocations efficiently. 
Additionally, it provides thread-safe versions of the operations and a lock-free version for high-performance scenarios.

Files
-----
- custom_array.h: Header file containing the declarations of the custom array and memory pool functions.
- custom_array.c: Source file implementing the custom array functionalities.
- main.c: Source file containing the main function to demonstrate the usage of the custom array.
- CMakeLists.txt: CMake build configuration file.

Requirements
------------
- CMake 3.10 or higher
- C compiler (GCC recommended)
- pthread library

Instructions
------------
1. Create a build directory:
   ```
   mkdir build
   cd build
   ```

2. Run CMake to generate the build system files:
   ```
   cmake ..
   ```

3. Build the project:
   ```
   cmake --build .
   ```

4. Run the executable:
   ```
   ./main
   ```

Description
-----------
The custom array implementation provides the following functionalities:

1. Initialization:
   - Initialize the array with a specified initial capacity.

2. Insertion:
   - Add elements to the array, expanding capacity as necessary.

3. Deletion:
   - Remove elements from the array and compact the memory.

4. Access:
   - Access elements by index.

5. Resize:
   - Dynamically resize the array to optimize memory usage.

6. Garbage Collection:
   - Reclaim memory from deleted elements.

7. Memory Pool:
   - Manage small memory allocations efficiently using a memory pool.

8. Concurrency:
   - Implement thread-safe versions of insertion, deletion, and access operations.
   - Use synchronization primitives (e.g., mutexes) to ensure thread safety.
   - Implement a lock-free version of the container for high-performance scenarios.

Define
------
In the code, a `#define` is used for the memory pool size:

```c
#define MEMORY_POOL_SIZE 1000
```

This can be adjusted based on your needs.

Function Declarations
---------------------
custom_array.h:

```c
#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H

#include <stdlib.h>
#include <pthread.h>

#define MEMORY_POOL_SIZE 1000  // Adjust this size based on your needs

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
    size_t deleted_count;  // Track the number of deleted elements
    size_t *deleted_indices;  // Track the indices of deleted elements
    pthread_mutex_t lock;  // Mutex for thread safety
} CustomArray;

// Function declarations for custom array
void initArray(CustomArray *array, size_t initial_capacity);
void insertElement(CustomArray *array, int element);
void deleteElement(CustomArray *array, size_t index);
int getElement(CustomArray *array, size_t index);
void resizeArray(CustomArray *array, size_t new_capacity);
void freeArray(CustomArray *array);
void garbageCollect(CustomArray *array);

// Function declarations for memory pool
void initMemoryPool(size_t element_size, size_t element_count);
void *allocateFromPool();
void freeToPool(void *element);
void destroyMemoryPool();

// Function declarations for lock-free custom array (for high-performance scenarios)
void insertElementLockFree(CustomArray *array, int element);
void deleteElementLockFree(CustomArray *array, size_t index);
int getElementLockFree(CustomArray *array, size_t index);

#endif // CUSTOM_ARRAY_H
```

Usage Example
-------------
main.c:

```c
#include "custom_array.h"
#include <stdio.h>
#include <pthread.h>

void printArray(CustomArray *array) {
    for (size_t i = 0; i < array->size; i++) {
        printf("%d ", getElement(array, i));
    }
    printf("\n");
}

void *threadFunction(void *arg) {
    CustomArray *array = (CustomArray *)arg;
    for (int i = 0; i < 1000; i++) {
        insertElement(array, i);
    }
    return NULL;
}

int main() {
    // Initialize memory pool with MEMORY_POOL_SIZE elements of size `int`
    initMemoryPool(sizeof(int) * MEMORY_POOL_SIZE, MEMORY_POOL_SIZE);

    CustomArray array;
    
    // Initialization
    initArray(&array, 4);
    printf("Array initialized with capacity 4.\n");
    
    // Create threads for concurrent insertion
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, threadFunction, &array);
    pthread_create(&thread2, NULL, threadFunction, &array);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Elements inserted concurrently: ");
    printArray(&array);
    
    // Access
    printf("Access element at index 2: %d\n", getElement(&array, 2));
    
    // Deletion
    deleteElement(&array, 1);
    printf("Element at index 1 deleted: ");
    printArray(&array);

    // Garbage collection
    garbageCollect(&array);
    printf("After garbage collection: ");
    printArray(&array);

    // Final cleanup
    freeArray(&array);
    destroyMemoryPool();
    printf("Array memory freed.\n");
    
    return 0;
}
```

Notes
-----
- Ensure that the memory pool is initialized before using the custom array.
- The garbage collection function should be called periodically to reclaim memory from deleted elements.

-------
For any questions or issues, please contact Ahmed Abdelghany at [ahmedabdelghany15@gmail.com].

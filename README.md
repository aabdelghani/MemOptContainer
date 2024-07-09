
Custom Array Project
====================

Overview
--------
This project implements a custom dynamic array in C with advanced memory handling. 
It includes a garbage collection mechanism to reclaim memory from deleted elements 
and uses a memory pool to manage small memory allocations efficiently.

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

Function Declarations
---------------------
custom_array.h:

```c
#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H

#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
    size_t deleted_count;  // Track the number of deleted elements
    size_t *deleted_indices;  // Track the indices of deleted elements
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

#endif // CUSTOM_ARRAY_H
```

Usage Example
-------------
main.c:

```c
#include "custom_array.h"
#include <stdio.h>

void printArray(CustomArray *array) {
    for (size_t i = 0; i < array->size; i++) {
        printf("%d ", getElement(array, i));
    }
    printf("\n");
}

int main() {
    // Initialize memory pool with 100 elements of size `int`
    initMemoryPool(sizeof(int) * 100, 100);

    CustomArray array;
    
    // Initialization
    initArray(&array, 4);
    printf("Array initialized with capacity 4.\n");
    
    // Insertion
    insertElement(&array, 10);
    insertElement(&array, 20);
    insertElement(&array, 30);
    insertElement(&array, 40);
    printf("Elements inserted: ");
    printArray(&array);
    
    // Resize
    printf("Resizing array to capacity 10.\n");
    resizeArray(&array, 10);
    printf("New capacity: %zu\n", array.capacity);
    
    // Insertion after resize
    insertElement(&array, 50);
    printf("Element 50 inserted after resizing: ");
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

Contact
-------
For any questions or issues, please contact [Ahmed Abdelghany] at [ahmedabdelghany15@gmail.com].

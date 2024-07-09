#include "custom_array.h"
#include <stdio.h>
#include <pthread.h>
#define MEMORY_POOL_SIZE 4

void printArray(CustomArray *array) {
    for (size_t i = 0; i < array->size; i++) {
        printf("%d \t", getElement(array, i));
    }
    printf("\n");
}

void *threadFunction(void *arg) {
    CustomArray *array = (CustomArray *)arg;
    
    for (int i = 0; i < MEMORY_POOL_SIZE; i++) {
        insertElement(array, i);
    }
    return NULL;
}

int main() {
    // Initialize memory pool with # elements of size `int`
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


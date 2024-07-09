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


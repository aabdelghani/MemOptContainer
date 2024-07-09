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


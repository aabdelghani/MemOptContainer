#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <pthread.h>

#define MEMORY_POOL_SIZE 4  // Adjust this size based on your needs

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

#ifdef __cplusplus
}
#endif

#endif // CUSTOM_ARRAY_H


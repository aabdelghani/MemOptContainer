#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <pthread.h>

#define MEMORY_POOL_SIZE 4  // Adjust this size based on your needs

/**
 * CustomArray structure representing a dynamic array.
 */
typedef struct {
    int *data;                  // Pointer to the array data
    size_t size;                // Current number of elements in the array
    size_t capacity;            // Current capacity of the array
    size_t deleted_count;       // Track the number of deleted elements
    size_t *deleted_indices;    // Track the indices of deleted elements
    pthread_mutex_t lock;       // Mutex for thread safety
} CustomArray;

/**
 * Initialize the custom array with a specified initial capacity.
 * 
 * @param array Pointer to the CustomArray to initialize
 * @param initial_capacity Initial capacity of the array
 */
void initArray(CustomArray *array, size_t initial_capacity);

/**
 * Insert an element into the custom array.
 * 
 * @param array Pointer to the CustomArray
 * @param element Element to insert into the array
 */
void insertElement(CustomArray *array, int element);

/**
 * Delete an element from the custom array at the specified index.
 * 
 * @param array Pointer to the CustomArray
 * @param index Index of the element to delete
 */
void deleteElement(CustomArray *array, size_t index);

/**
 * Get an element from the custom array at the specified index.
 * 
 * @param array Pointer to the CustomArray
 * @param index Index of the element to retrieve
 * @return The element at the specified index, or -1 if out of bounds
 */
int getElement(CustomArray *array, size_t index);

/**
 * Resize the custom array to a new capacity.
 * 
 * @param array Pointer to the CustomArray
 * @param new_capacity New capacity for the array
 */
void resizeArray(CustomArray *array, size_t new_capacity);

/**
 * Free the memory allocated for the custom array.
 * 
 * @param array Pointer to the CustomArray
 */
void freeArray(CustomArray *array);

/**
 * Perform garbage collection to reclaim memory from deleted elements.
 * 
 * @param array Pointer to the CustomArray
 */
void garbageCollect(CustomArray *array);

/**
 * Initialize the memory pool with a specified element size and count.
 * 
 * @param element_size Size of each element in the pool
 * @param element_count Number of elements in the pool
 */
void initMemoryPool(size_t element_size, size_t element_count);

/**
 * Allocate memory from the memory pool.
 * 
 * @return Pointer to the allocated memory, or NULL if allocation fails
 */
void *allocateFromPool();

/**
 * Free memory back to the memory pool.
 * 
 * @param element Pointer to the memory to free
 */
void freeToPool(void *element);

/**
 * Destroy the memory pool and free all allocated memory.
 */
void destroyMemoryPool();

/**
 * Insert an element into the custom array in a lock-free manner.
 * 
 * @param array Pointer to the CustomArray
 * @param element Element to insert into the array
 */
void insertElementLockFree(CustomArray *array, int element);

/**
 * Delete an element from the custom array at the specified index in a lock-free manner.
 * 
 * @param array Pointer to the CustomArray
 * @param index Index of the element to delete
 */
void deleteElementLockFree(CustomArray *array, size_t index);

/**
 * Get an element from the custom array at the specified index in a lock-free manner.
 * 
 * @param array Pointer to the CustomArray
 * @param index Index of the element to retrieve
 * @return The element at the specified index, or -1 if out of bounds
 */
int getElementLockFree(CustomArray *array, size_t index);

#ifdef __cplusplus
}
#endif

#endif // CUSTOM_ARRAY_H


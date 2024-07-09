#include "custom_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>

// Memory pool structure and functions
typedef struct MemoryPool {
    void *pool;
    size_t element_size;
    size_t element_count;
    void **free_list;
    size_t free_count;
} MemoryPool;

static MemoryPool pool;

void initMemoryPool(size_t element_size, size_t element_count) {
    pool.pool = malloc(element_size * element_count);
    pool.element_size = element_size;
    pool.element_count = element_count;
    pool.free_list = (void **)malloc(element_count * sizeof(void *));
    pool.free_count = element_count;

    for (size_t i = 0; i < element_count; i++) {
        pool.free_list[i] = (char *)pool.pool + i * element_size;
    }
}

void *allocateFromPool() {
    if (pool.free_count == 0) {
        return NULL;
    }
    return pool.free_list[--pool.free_count];
}

void freeToPool(void *element) {
    if (pool.free_count < pool.element_count) {
        pool.free_list[pool.free_count++] = element;
    }
}

void destroyMemoryPool() {
    free(pool.pool);
    free(pool.free_list);
}

// Initialize the array with a specified initial capacity
void initArray(CustomArray *array, size_t initial_capacity) {
    array->data = (int *)allocateFromPool();
    if (!array->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    array->size = 0;
    array->capacity = initial_capacity;
    array->deleted_count = 0;
    array->deleted_indices = (size_t *)allocateFromPool();
    if (!array->deleted_indices) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    pthread_mutex_init(&array->lock, NULL);
}

// Add elements to the array, expanding capacity as necessary
void insertElement(CustomArray *array, int element) {
    pthread_mutex_lock(&array->lock);
    if (array->size == array->capacity) {
        size_t new_capacity = array->capacity * 2;
        resizeArray(array, new_capacity);
    }
    if (array->deleted_count > 0) {
        size_t index = array->deleted_indices[--array->deleted_count];
        array->data[index] = element;
    } else {
        array->data[array->size++] = element;
    }
    pthread_mutex_unlock(&array->lock);
}

// Remove elements from the array and compact the memory
void deleteElement(CustomArray *array, size_t index) {
    pthread_mutex_lock(&array->lock);
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        pthread_mutex_unlock(&array->lock);
        return;
    }
    for (size_t i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
    pthread_mutex_unlock(&array->lock);
}

// Access elements by index
int getElement(CustomArray *array, size_t index) {
    pthread_mutex_lock(&array->lock);
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        pthread_mutex_unlock(&array->lock);
        return -1;
    }
    int value = array->data[index];
    pthread_mutex_unlock(&array->lock);
    return value;
}

// Dynamically resize the array to optimize memory usage
void resizeArray(CustomArray *array, size_t new_capacity) {
    int *new_data = (int *)allocateFromPool();
    if (!new_data) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < array->size; i++) {
        new_data[i] = array->data[i];
    }
    freeToPool(array->data);
    array->data = new_data;
    array->capacity = new_capacity;
}

// Free the array memory
void freeArray(CustomArray *array) {
    pthread_mutex_lock(&array->lock);
    freeToPool(array->data);
    freeToPool(array->deleted_indices);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
    array->deleted_count = 0;
    pthread_mutex_unlock(&array->lock);
    pthread_mutex_destroy(&array->lock);
}

// Garbage Collection: Reclaim memory from deleted elements
void garbageCollect(CustomArray *array) {
    pthread_mutex_lock(&array->lock);
    size_t new_size = 0;
    for (size_t i = 0; i < array->size; i++) {
        if (array->data[i] != -1) {
            array->data[new_size++] = array->data[i];
        }
    }
    array->size = new_size;
    array->deleted_count = 0;
    pthread_mutex_unlock(&array->lock);
}

// Lock-free versions of the functions (for high-performance scenarios)

void insertElementLockFree(CustomArray *array, int element) {
    if (array->size == array->capacity) {
        size_t new_capacity = array->capacity * 2;
        resizeArray(array, new_capacity);
    }
    if (array->deleted_count > 0) {
        size_t index = array->deleted_indices[--array->deleted_count];
        array->data[index] = element;
    } else {
        array->data[array->size++] = element;
    }
}

void deleteElementLockFree(CustomArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    for (size_t i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
}

int getElementLockFree(CustomArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }
    return array->data[index];
}


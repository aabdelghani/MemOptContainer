#include "custom_array.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize the array with a specified initial capacity
void initArray(CustomArray *array, size_t initial_capacity) {
    array->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!array->data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    array->size = 0;
    array->capacity = initial_capacity;
}

// Add elements to the array, expanding capacity as necessary
void insertElement(CustomArray *array, int element) {
    if (array->size == array->capacity) {
        size_t new_capacity = array->capacity * 2;
        resizeArray(array, new_capacity);
    }
    array->data[array->size++] = element;
}

// Remove elements from the array and compact the memory
void deleteElement(CustomArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    for (size_t i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
}

// Access elements by index
int getElement(CustomArray *array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }
    return array->data[index];
}

// Dynamically resize the array to optimize memory usage
void resizeArray(CustomArray *array, size_t new_capacity) {
    int *new_data = (int *)realloc(array->data, new_capacity * sizeof(int));
    if (!new_data) {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    array->data = new_data;
    array->capacity = new_capacity;
}

// Free the array memory
void freeArray(CustomArray *array) {
    free(array->data);
    array->size = 0;
    array->capacity = 0;
}


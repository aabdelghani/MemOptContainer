#ifndef CUSTOM_ARRAY_H
#define CUSTOM_ARRAY_H

#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} CustomArray;

// Function declarations
void initArray(CustomArray *array, size_t initial_capacity);
void insertElement(CustomArray *array, int element);
void deleteElement(CustomArray *array, size_t index);
int getElement(CustomArray *array, size_t index);
void resizeArray(CustomArray *array, size_t new_capacity);
void freeArray(CustomArray *array);

#endif // CUSTOM_ARRAY_H


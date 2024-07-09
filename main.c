#include "custom_array.h"
#include <stdio.h>

int main() {
    CustomArray array;
    initArray(&array, 4);

    insertElement(&array, 10);
    insertElement(&array, 20);
    insertElement(&array, 30);
    insertElement(&array, 40);

    printf("Initial elements:\n");
    for (size_t i = 0; i < array.size; i++) {
        printf("%d ", getElement(&array, i));
    }
    printf("\n");

    deleteElement(&array, 1);
    printf("After deleting element at index 1:\n");
    for (size_t i = 0; i < array.size; i++) {
        printf("%d ", getElement(&array, i));
    }
    printf("\n");

    freeArray(&array);
    return 0;
}


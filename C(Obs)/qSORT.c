#ifndef size_t
#include<stddef.h>
#endif

size_t partition(void* arr, size_t left, size_t right, size_t size, int (*comp)(const void*, const void*)) ;
void quicksort(void* arr, size_t left, size_t right, size_t size, int (*comp)(const void*, const void*));

size_t partition(void* arr, size_t left, size_t right, size_t size, int (*comp)(const void*, const void*)) {
    const void* pivot = (char*)arr + right * size;
    size_t i = left - 1;

    for (size_t j = left; j < right; j++) {
        if (comp((char*)arr + j * size, pivot) <= 0) {
            i++;
            char* temp = (char*)malloc(size);
            memcpy(temp, (char*)arr + i * size, size);
            memcpy((char*)arr + i * size, (char*)arr + j * size, size);
            memcpy((char*)arr + j * size, temp, size);
            free(temp);
        }
    }

    char* temp = (char*)malloc(size);
    memcpy(temp, (char*)arr + (i + 1) * size, size);
    memcpy((char*)arr + (i + 1) * size, pivot, size);
    memcpy(pivot, temp, size);
    free(temp);

    return i + 1;
}


void quicksort(void* arr, size_t left, size_t right, size_t size, int (*comp)(const void*, const void*)) {
    if (left < right) {
        size_t pivotIndex = partition(arr, left, right, size, comp);
        quicksort(arr, left, pivotIndex - 1, size, comp);
        quicksort(arr, pivotIndex + 1, right, size, comp);
    }
}

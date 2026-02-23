#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamic_array.h"

static int da_reserve(DynamicArray *arr, size_t min_capacity) {
    if (!arr) return 1;

    if (arr->capacity >= min_capacity) return 0;

    size_t new_capacity = (arr->capacity == 0) ? 4 : arr->capacity;
    while (new_capacity < min_capacity) {
        new_capacity *= 2;
    } 
    
    int *new_data = (int *)realloc(arr->data, new_capacity * sizeof(int));
    if (!new_data) return 2;

    arr->data = new_data;
    arr->capacity = new_capacity;

    return 0;
}

int da_init(DynamicArray *arr, size_t initial_capacity) {
    if (!arr) return 1;

    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;

    // allow 0 as initial capacity to start empty and allocate on push 
    if (initial_capacity == 0) return 0;

    arr->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!arr->data) return 2;

    arr->capacity = initial_capacity;

    return 0;
}

int da_push_back(DynamicArray *arr, int value) {
    if (!arr) return 1;

    if (da_reserve(arr, arr->size + 1) != 0) return 2;

    arr->data[arr->size++] = value;
    return 0;
}

int da_get(const DynamicArray *arr, size_t index, int *out) {
    if (!arr || !out) return 1;
    if (index >= arr->size) return 2;

    *out = arr->data[index];
    return 0;
}

int da_set(DynamicArray *arr, size_t index, int value) {
    if (!arr) return 1;
    if (index >= arr->size) return 2;

    arr->data[index] = value;
    return 0;
}

size_t da_size(const DynamicArray *arr) {
    return arr ? arr->size : 0;
}

size_t da_capacity(const DynamicArray *arr) {
    return arr ? arr->capacity : 0;
}

int da_remove_at(DynamicArray *arr, size_t index) {
    if (!arr) return 1;
    if (index >= arr->size) return 2;

    if (index + 1 < arr->size) {
        memmove(&arr->data[index],
                &arr->data[index+1],
                (arr->size - index - 1) * sizeof(int));
    }
    arr->size--;
    return 0;
}

int da_pop_back(DynamicArray *arr, int*out) {
    if (!arr) return 1;
    if (arr->size == 0) return 2;
    
    arr->size--;
    if (out) *out = arr->data[arr->size];
    return 0;
}

void da_free(DynamicArray *arr) {
    if (!arr) return;

    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->capacity = 0;
}
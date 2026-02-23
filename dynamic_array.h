#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H 

#include <stddef.h>

typedef struct {
    int *data;              // pointer to heap allocated memory
    size_t size;            // number of elements currently stored 
    size_t capacity;        // number of elements that can fit before resizing
} DynamicArray; 

// initialise the array to a valid empty state 
// return 0 on success, non-zero on allocation failure
int da_init(DynamicArray *arr, size_t initial_capacity);

// append one element, grow capacity if needed
// returns 0 on success, non-zero on allocation failure
int da_push_back(DynamicArray *arr, int value);

// read element at index
int da_get(const DynamicArray *arr, size_t index, int *out);

// write element at index
// return 0 on success, non-zero if index is out of range
int da_set(DynamicArray *arr, size_t index, int value);

size_t da_size(const DynamicArray *arr);

size_t da_capacity(const DynamicArray *arr);

// free heap storage and reset to empty state
void da_free(DynamicArray *arr);

int da_remove_at(DynamicArray *arr, size_t index);

int da_pop_back(DynamicArray *arr, int *out);

#endif
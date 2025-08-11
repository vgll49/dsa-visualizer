#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sorting_algorithms.h"

// Bubble Sort (o(n2), best case o(n))
dns_arr_t* bubble_sort(dns_arr_t* array) {
    bool is_swapping = true;
    int end = array->size;

    while(is_swapping) {
        is_swapping = false;
        for(int i = 1; i < end; i++) {
            if(array->data[i - 1] > array->data[i]) {
                int tmp = array->data[i -1];
                array->data[i-1] = array->data[i];
                array->data[i] = tmp;
                is_swapping = true;
            }
        }
        end--;
    }
    return array;
}

// Merge Sort (o(n*log(n)))
// 2 funcs

dns_arr_t* merge(dns_arr_t* first, dns_arr_t* second) {
    dns_arr_t* final = malloc(sizeof(dns_arr_t));

    if(final == NULL) {
        return NULL;
    }

    final->size = first->size + second->size;
    final->data = malloc(final->size * sizeof(int));

    if(final->data == NULL) {
        free(final);
        return NULL;
    }

    int i = 0;
    int j = 0;
    int index = 0;
    while(i < first->size && j < second->size) {
        if(first->data[i] < second->data[j]) {
            final->data[index++] = first->data[i++];
        } else {
            final->data[index++] = second->data[j++];
        }
    }

    while (i < first->size) {
        final->data[index++] = first->data[i++];
    }
    while (j < second->size) {
        final->data[index++] = second->data[j++];
    }

    

    free(first->data);
    free(first);
    free(second->data);
    free(second);

    return final;
}

dns_arr_t* merge_sort(dns_arr_t* array) {
    if (array->size < 2) {
        return array;
    }

    // split array in 2

    // memory allocation for the 2 split arrays
    int left_size = array->size / 2 + (array->size % 2);
    int right_size = array->size / 2;

    dns_arr_t* left_array = malloc(sizeof(dns_arr_t));
    if(left_array == NULL) {
        return NULL;
    }

    left_array->size = left_size;
    left_array->data = malloc(left_size * sizeof(int));
    if(left_array->data == NULL) {
        free(left_array);
        return NULL;
    }

    dns_arr_t* right_array = malloc(sizeof(dns_arr_t));
    if(right_array == NULL) {
        free(right_array);
        return NULL;
    }
    right_array->size = right_size;
    right_array->data = malloc(right_size * sizeof(int));

    if(right_array->data == NULL) {
        return NULL;
    }

    //inserting numbers into the arrays
    for(int i = 0; i < left_size; i++) {
        left_array->data[i] = array->data[i];
    }

    for(int i = 0; i < right_size; i++) {
        right_array->data[i] = array->data[i + left_size];
    }

    //now call merge sort on both
    dns_arr_t* sorted_left;
    dns_arr_t* sorted_right;

    sorted_left = merge_sort(left_array);
    sorted_right = merge_sort(right_array);

    if (sorted_left == NULL || sorted_right == NULL) {
        if (sorted_left) { free(sorted_left->data); free(sorted_left); }
        if (sorted_right) { free(sorted_right->data); free(sorted_right); }
        return NULL;
    }

    free(array->data);
    free(array);

    return merge(sorted_left, sorted_right);

}


// Insertion Sort (O(n2) -> for presorted small datasets)
dns_arr_t* insertion_sort(dns_arr_t* array) {

    for(int i = 1; i < array->size; i++) {
        int j = i;
        while(j > 0 && array->data[j-1] > array->data[j]) {
            int tmp = array->data[j-1];
            array->data[j-1] = array->data[j];
            array->data[j] = tmp;
            j--;
        }   
    }

    return array;
}


// Quick Sort 
int partition(dns_arr_t* array, int low, int high) {
    int pivot = array->data[high];
    int i = low -1;

    for(int j = low; j < high; j++) {
        if(array->data[j] < pivot) {
            i++;
            int tmp = array->data[j];
            array->data[j] = array->data[i];
            array->data[i] = tmp;
        }
    }
    int tmp = array->data[i+1];
    array->data[i+1] = pivot;
    array->data[high] = tmp;

    int pivot_index = i+1;
    printf("pivot is %d\n", pivot_index);
    return pivot_index;
}


void* quick_sort(dns_arr_t* array, int low, int high) {
    if(low < high) {
        int middle = partition(array, low, high);
        quick_sort(array, low, middle-1);
        quick_sort(array, middle+1, high);
    }

}


// Selection Sort






// Heap Sort, Binary Search
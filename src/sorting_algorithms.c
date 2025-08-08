#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sorting_algorithms.h"
#include "array.h"

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

// Merge Sort
// 2 funcs
dns_arr_t* merge_sort(dns_arr_t* array) {
    if (array->size < 2) {
        return array;
    }

    // split array in 2
    // call merge on both
}

dns_arr_t* merge(dns_arr_t* first, dns_arr_t* second) {
    dns_arr_t* final = malloc(sizeof(dns_arr_t));

    if(final == NULL) {
        return;
    }

    
}
// Quick Sort 





// Insertion Sort 


// Selection Sort
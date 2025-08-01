#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "array.h"

dns_arr_t *create_dns_array(int size) {
    srand(time(NULL));  
    dns_arr_t *arr = malloc(sizeof(dns_arr_t));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    arr->size = size;
    arr->data = calloc(1, size * (sizeof(int)));

    for(int i = 0; i < size; i++) {
        arr->data[i] = rand() % 100;
    }

    return arr;
}
 
int dns_arr_set(dns_arr_t *arr, int element,  int index) {

    if(index >= arr->size) {
        printf("Index out of bounds\n");
        return 1;
    }

    arr->data[index] = element;

    return arr->data[index];
}

int dns_arr_append(dns_arr_t *arr) {
    srand(time(NULL));  
    int new_size = arr->size+1;

    int *tmp = realloc(arr->data, new_size * sizeof(int));
    if(!tmp) {
        free(arr->data);
        return 1;
    }

    tmp[new_size-1] = rand() % 100;
    arr->data = tmp;
    arr->size++;

    return arr->size;
}

int dns_arr_del_at_index(dns_arr_t *arr, int index) {
    if(index >= arr->size) {
        printf("Index out of bounds\n");
        return 1;
    }

    for (int i = index; i < arr->size -1; i++) {
        arr->data[i] = arr->data[i+1];
    }

    int new_size = arr->size-1;
    int *tmp = realloc(arr->data, new_size * sizeof(int));
    
    if(!tmp) {
        free(arr->data);
        return 1;
    }

    arr->data = tmp;
    arr->size--;

    return arr->size;
}


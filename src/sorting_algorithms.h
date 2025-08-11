#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H
#include "array.h"

dns_arr_t* bubble_sort(dns_arr_t* array);
dns_arr_t* merge_sort(dns_arr_t* array);
dns_arr_t* insertion_sort(dns_arr_t* array);
void* quick_sort(dns_arr_t* array, int low, int high);
#endif
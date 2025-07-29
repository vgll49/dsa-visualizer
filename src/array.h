#ifndef ARRAY_H
#define ARRAY_H

typedef struct DNSArray {
    int size;
    int *arr;
} dns_arr_t;

dns_arr_t *create_dns_array(int len);
int dns_arr_set(dns_arr_t *arr, int element,  int index);
int dns_arr_del_at_index(dns_arr_t *arr, int index);
int dns_arr_append(dns_arr_t *arr, int element);

#endif 
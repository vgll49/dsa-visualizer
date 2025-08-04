#ifndef QUEUE_H
#define QUEUE_H

typedef struct DNSQueue {
    int count;
    int capacity;
    int *data;
} dns_int_queue_t;


dns_int_queue_t *queue_create(int capacity);
int queue_push(dns_int_queue_t *queue);
void queue_print(dns_int_queue_t *queue);
int queue_pop(dns_int_queue_t *queue);
void queue_free(dns_int_queue_t *queue);
int queue_peek(dns_int_queue_t *queue);

#endif 
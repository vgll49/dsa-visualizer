#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"


// CREATE
dns_int_queue_t *queue_create(int capacity) {
    dns_int_queue_t *obj = malloc(sizeof(dns_int_queue_t));

    if (obj == NULL) {
        printf("queue memory allocation failed\n");
        return NULL;
    }

    obj->capacity = capacity;
    obj->count = 0;
    obj->data = malloc(obj->capacity * sizeof(int));
    
    if (obj->data == NULL) {
        printf("queue memory allocation failed\n");
        free(obj);
        return NULL;
    }

    return obj;
}

// PUSH
int queue_push(dns_int_queue_t *queue) {
    srand(time(NULL));  

    if(queue->capacity == queue->count) {
        queue->capacity *= 2;
        int *tmp = realloc(queue->data, queue->capacity * sizeof(int));
        if (tmp == NULL) {
            queue->capacity /= 2;
            return 1;
        }
        queue->data = tmp;
    }

    queue->data[queue->count] = rand() % 100;
    queue->count++;
}

// PRINT
void queue_print(dns_int_queue_t *queue) {
    if(queue == NULL) {
        printf("queue is null");
    }

    for (int i = 0; i < queue->count; i ++) {
        printf("value is: %d at index: %d\n", queue->data[i], i);
    }

    printf("queue size: %d and queue capacity: %d\n", queue->count, queue->capacity);
}

// POP
// This is 0(n) because its not a linked list
int queue_pop(dns_int_queue_t *queue) {
    if(queue->count == 0) {
        return 0;
    }
    int pop = queue->data[0];

    for(int i = 0; i < queue->count-1; i++) {
        queue->data[i] =  queue->data[i+1];
    }

    queue->count--;

    return pop;
}

// PEEK
int queue_peek(dns_int_queue_t *queue) {
    if(queue->count == 0) {
        return 0;
    }

    return queue->data[queue->count-1];
}

// FREE
void queue_free(dns_int_queue_t *queue) {
    if(queue == NULL) {
        return;
    }

    if(queue->data != NULL) {
        free(queue->data);
    }

    free(queue);
}
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "linked_list.h"

// CREATE
t_linked_list *linked_list_create() {
    t_linked_list *list = malloc(sizeof(t_linked_list));

    if(list == NULL) {
        return NULL;
    }

    list->head = malloc(sizeof(t_node));
    
    if(list->head == NULL) {
        return NULL;
    }

    list->tail = malloc(sizeof(t_node));

    if(list->head == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

// APPEND
void *linked_list_add_to_tail (t_linked_list *list) {
    srand(time(NULL));

    t_node *node = malloc(sizeof(t_node));

    node->val = rand() % 100; 
    node->next = NULL;

    if(list->head == NULL) {
        list->head = node;
        list->tail = node;
        return list;
    }

    list->tail->next = node;
    list->tail = node;

    return list;
}

// POP (O(1))
t_node *linked_list_pop (t_linked_list *list) {
    if(list->head == NULL) {
        return NULL;
    }
    t_node *old_node = list->head;
    list->head = list->head->next;

    if(list->head == NULL) {
        list->tail == NULL;
    }
    
    free(old_node);
}

// PRINT
void linked_list_print(t_linked_list *list) {
    t_node *iter = list->head;
    int i = 0;
    
    while(iter!= NULL) {
        printf("val is %d at index %d\n", iter->val, i);
        iter = iter->next;
        i++;
    }
}


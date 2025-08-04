#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

// CREATE
dns_stack_t* stack_create(int capacity) {
    dns_stack_t* stack = malloc(sizeof(dns_stack_t));

    if (stack == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    stack->count = 0;
    stack->capacity = capacity;
    stack->stack_elements = malloc(stack->capacity * sizeof(t_stack_element));

    if (stack->stack_elements == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    return stack;
}

// PRINT
void stack_print(dns_stack_t *stack) {
    for(int i = 0; i < stack->count; i++) {
        switch (stack->stack_elements[i].data_type) {
            case TYPE_INT:
            printf("INT value %d at Index %d\n",*(int*)stack->stack_elements[i].data, i);
            break;
            case TYPE_FLOAT:
            printf("Float value %.2f at Index %d\n",*(float*)stack->stack_elements[i].data, i);
            break;
            case TYPE_CHAR:
            printf("Char value %c at Index %d\n",*(char*)stack->stack_elements[i].data, i);
            break;
            case TYPE_STRING:
            printf("String value %s at Index %d\n",(char *)stack->stack_elements[i].data, i);
            break;
            default:
            break;
        }
    }
    printf("current stack size is: %d\n", stack->count);
}

// PUSH
void stack_push(dns_stack_t *stack, t_stack_element *obj) {

    if(stack->count == stack->capacity) {
        stack->capacity *= 2;
        void *newadress = realloc(stack->stack_elements,  stack->capacity * sizeof(t_stack_element));

        if(newadress == NULL) {
            stack->capacity /= 2;
            return;
        }
        stack->stack_elements = newadress;
    }

    stack->stack_elements[stack->count] = *obj;
    stack->count++;
}


void stack_push_multiple_types(dns_stack_t *stack) {
    srand(time(NULL));  

    int* int_obj = malloc(sizeof(int));
    *int_obj = rand() % 100;
    t_stack_element int_elem = {
        .data = int_obj,
        .data_type = TYPE_INT
    };
    stack_push(stack, &int_elem);

    
    float *pi = malloc(sizeof(float));
    *pi = rand() % 100;
    t_stack_element float_elem = {
        .data = pi,
        .data_type = TYPE_FLOAT,
    };
    stack_push(stack, &float_elem);

    char* st = "Hello World";
    int len = strlen(st) +1;
    char *string_obj_adress = malloc(len * sizeof(char));
    strcpy(string_obj_adress, st);
    t_stack_element str_elem = {
        .data = string_obj_adress,
        .data_type = TYPE_STRING,
    };
    stack_push(stack, &str_elem);


    char* ch = malloc(sizeof(char)); 
    *ch = 'A' + (random() % 26);
    t_stack_element char_elem = {
        .data = ch,
        .data_type = TYPE_CHAR,
    };
    stack_push(stack, &char_elem);
}   

// POP
void* stack_pop(dns_stack_t* stack) {
    if(stack->count < 1) {
        printf("STACK IS EMPTY");
        return NULL;
    }
    
    stack->count--;
    return stack->stack_elements[stack->count].data;
}

// Free
void stack_free(dns_stack_t *stack) {
    if(stack == NULL) {
        return;
    }

    if(stack->stack_elements != NULL) {
        free(stack->stack_elements);
    }
    free(stack);
}

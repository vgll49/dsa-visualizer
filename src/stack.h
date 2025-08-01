#ifndef STACK_H
#define STACK_H

typedef enum Data_Type{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING,
} t_data_type;

typedef struct Stack_Element {
    void *data;
    t_data_type data_type;
} t_stack_element;

typedef struct Stack {
    int capacity;
    int count;
    t_stack_element* stack_elements;
 
} dns_stack_t;

dns_stack_t* stack_create(int len);
void stack_print(dns_stack_t *stack);
void stack_push(dns_stack_t *stack, t_stack_element *obj);
void* stack_pop(dns_stack_t* stack);
void stack_free(dns_stack_t *stack);
void stack_push_multiple_types(dns_stack_t *stack);

#endif
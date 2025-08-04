#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node t_node;

typedef struct Node {
    int val;
    t_node *next;

} t_node;

typedef struct Linked_List {
    t_node *head;
    t_node *tail;
} t_linked_list;

t_linked_list *linked_list_create();
void *linked_list_add_to_tail (t_linked_list *list);
void linked_list_print(t_linked_list *list);
t_node *linked_list_pop (t_linked_list *list);

#endif

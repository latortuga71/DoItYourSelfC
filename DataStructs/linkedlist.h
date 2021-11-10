#include <stdlib.h>
#include <stdio.h>

struct node {
    int data;
    struct node* next;
};


typedef struct {
 struct node* start;
 struct node* current;
 struct node* end;
 int length;
} linked_list;


struct node* new_node();
linked_list* __linked_list_init();
linked_list* new_linked_list(int nodes);
void print_list();
int list_length(linked_list*);
void push_node(linked_list*,int);

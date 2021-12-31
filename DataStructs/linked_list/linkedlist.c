#include "linkedlist.h"


struct node* new_node(){
    return (struct node*)malloc(sizeof(struct node));
}

linked_list* __linked_list_init(){
    return(linked_list*)malloc(sizeof(linked_list));
}

linked_list* new_linked_list(int value){
    linked_list* list = __linked_list_init();
    struct node* head = new_node();
    list->current = head;
    list->start = head;
    list->end = head;
    list->current->data = value;
    list->current->next = NULL;
    list->length = 1;
    return list;
}

void delete_linked_list(linked_list* list){
    while(list->length != 0){
        pop_node(list);
    }
    free(list->start);
    free(list);
}


void reverse_linked_list(linked_list* list){
    // https://www.geeksforgeeks.org/reverse-a-linked-list/ <- :O
    // it is confusing, you really gotta draw it out then stare.
    struct node* previous = NULL;
    struct node* next = NULL;
    list->current = list->start; 
    // current should already point to start
    while (list->current != NULL){
        next = list->current->next;
        list->current->next = previous;
        previous = list->current;
        list->current = next;
    }
    // set end to current
    list->end = list->current;
    // set start to prev
    list->start = previous;
    // set current to start
    list->current = list->start;
}

void push_node(linked_list* list, int value){
        struct node* n = new_node();
        n->data = value;
        n->next = NULL;
        list->end->next = n;
        list->end = n;
        list->length += 1;
}

int pop_node(linked_list* list){
    while(list->current->next != list->end){
        list->current = list->current->next;
    }
    struct node* removed = list->current->next;
    list->current->next = NULL;
    list->end = list->current;
    list->current = list->start;
    free(removed);
    --list->length; 
    return 0;
}

int list_length(linked_list* list){
    return list->length;
}

void print_list(linked_list* list){
    while (list->current != NULL){
        printf("%d\n",list->current->data);
        list->current = list->current->next;
    }
    list->current = list->start; 
}

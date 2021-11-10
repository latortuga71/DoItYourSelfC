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
    /*
    linked_list* list = __linked_list_init();
    struct node* head = new_node();
    list->current = head;
    list->start = head;
    list->current->data = 0;
    list->current->next = NULL;
    for (int x = 1; x < nodes; x++){
        printf("Adding node\n");
        struct node* n = new_node();
        n->data = x;
        n->next = NULL;
        list->current->next = n;
        list->current = n;
    }
    list->end = list->current;
    list->start = head;
    list->current = head;
    list->length = nodes;
    return list;
    */
}

void push_node(linked_list* list, int value){
        struct node* n = new_node();
        n->data = value;
        n->next = NULL;
        list->end->next = n;
        list->end = n;
        list->length += 1;
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

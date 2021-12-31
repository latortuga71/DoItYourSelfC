#include "list.h"

list* new_list(size_t item_size){
    list* l = malloc(sizeof(list));
    l->size = 0;
    l->item_size = item_size;
    return l;
}


void* append(list* l, void* item){
    l->size++;
    l->items = realloc(l->items,(l->size + 1) * l->item_size);
    l->items[l->size - 1] = item;
    return item;
}

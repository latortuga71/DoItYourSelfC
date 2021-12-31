#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int size;
    size_t item_size;
    void** items;
} list;

list* new_list(size_t item_size);

void* append(list* list,void* item);

#include "stack.h"

Stack* new_stack(){
    Stack* s = malloc(sizeof(Stack));
    s->length = 0;
    s->values = calloc(s->length,sizeof(int*));
    return s;
}

void delete_stack(Stack* s){
    free(s->values);
    free(s);
}

int pop_stack(Stack* s){
    if (s->length <= 0){
        printf("ERROR: Cannot pop empty stack");
        return 0;
    }
    int popped = s->values[s->length];
    s->length -= 1;
    s->values = realloc(s->values,sizeof(int*) * s->length);
    return popped;
}

size_t stack_length(Stack* s){
    return s->length;
}

void print_stack(Stack* s){
    printf("[");
    for (int x = 0; x < s->length; x++){
        printf(" %d ",s->values[x]);
    }
    printf("]\n");
}

size_t push_stack(Stack* s, int value){
    s->length += 1;
    s->values = realloc(s->values,sizeof(int*) * s->length);
    s->values[s->length - 1] = value;
    return s->length;
}

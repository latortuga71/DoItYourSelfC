#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Stack {
    size_t length;
    int* values;
} Stack;


Stack* new_stack();
size_t stack_length(Stack* s);
int peek_stack(Stack* s);
bool is_stack_empty(Stack* s);
void delete_stack();
int pop_stack(Stack*);
size_t push_stack(Stack*, int);
void print_stack(Stack*);



#include "stack.h"



int main(){
    Stack* s = new_stack();
    push_stack(s,1);
    push_stack(s,15);
    push_stack(s,56);
    pop_stack(s);
    pop_stack(s);
    pop_stack(s);
    print_stack(s);
    delete_stack(s);
}

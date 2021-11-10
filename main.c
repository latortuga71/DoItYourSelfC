#include "DataStructs/string.h"
#include "DataStructs/linkedlist.h"


int main(){
    linked_list* list = new_linked_list(3);
    push_node(list,11);
    push_node(list,12);
    print_list(list);
    reverse_linked_list(list);
    print_list(list);
    delete_linked_list(list);
}

#include "DataStructs/string.h"
#include "DataStructs/linkedlist.h"


int main(){
    linked_list* list = new_linked_list(3);
    push_node(list,11);
    print_list(list);
    printf("%d\n",list_length(list));
}

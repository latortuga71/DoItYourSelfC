#include "DataStructs/string.h"



int main(){
    string_t* hello = string_init("hello");
    string_print(hello);
    string_reverse(hello);
    string_print(hello);
    delete_string(hello);
}

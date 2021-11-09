#include "DataStructs/string.h"



int main(){
    string_t* hello = string_init("hello from hell");
    string_print(hello);
    delete_string(hello);
    /*
    string_t* hello_sliced = string_slice(hello,1,7);
    if (hello_sliced == NULL){
        string_print(hello);
        delete_string(hello);
        return 1;
    }
    string_print(hello);
    string_print(hello_sliced);
    delete_string(hello);
    delete_string(hello_sliced);
    */
}

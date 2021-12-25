#include "DataStructs/string.h"
#include "DataStructs/linkedlist.h"
#include "Algorithms/sorting.h"
#include "Algorithms/searching.h"
#include "DataStructs/list.h"


void print_array(int* array,int length){
    for (int x = 0; x < length; x++){
        printf("%d, ",array[x]);
    }
    printf("\n");
}

int main(){
    int list_of_ints[6] = {31,41,59,26,41,58};
    print_array(list_of_ints,6);
    selection_sort(list_of_ints,6);
    print_array(list_of_ints,6);
}

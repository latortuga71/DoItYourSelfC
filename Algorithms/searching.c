#include "searching.h"

int linear_search(int* array,int length,int value){
    for (int x = 0; x < length; x++){
        if (array[x] == value)
            return 1;
    }
    return 0;
}

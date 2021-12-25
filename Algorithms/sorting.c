#include "sorting.h"

void selection_sort(int* array,int length){
    int idx_min,x,y;
    for (x = 0; x < length - 1;x++){
        idx_min = x;
        for (y = x+1; y < length; y++){
            if (array[y] < array[idx_min]){
                idx_min = y;
            }
        }
        if (idx_min != x){
            int tmp = array[idx_min];
            array[idx_min] = array[x];
            array[x] = tmp;
        }
    }
}



int linear_search(int* array,int n, int v){
    for (int x = 0; x < n; x++)
        if (array[x] == v)
            return x;
    return -1;
}


void insertion_sort_inc(int* array,int length){
    int x,y,key;
    for (int x = 1; x < length; x++){
        key = array[x]; // right param
        y = x - 1;
        while (y >= 0 && array[y] > key){
            array[y + 1] = array[y];
            y = y - 1;
            printf("while iteration\n");
        }
        array[y + 1] = key;
        printf("Key %d X %d Y %d\n",key,x,y);
    }
}


void insertion_sort_dec(int* array,int length){
    int x,y,key;
    for (int x = 1; x < length; x++){
        key = array[x];
        y = x - 1;
        while (y >= 0 && array[y] < key){
            array[y+1] = array[y];
            y = y - 1;
        }
        array[y+1] = key;
    }
}

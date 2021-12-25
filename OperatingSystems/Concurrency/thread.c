#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int var1;
    int var2;
} object_t;


void* work(void* args){
    object_t* argz = (object_t*)args;
    printf("Running in a thread! %d %d\n",argz->var1,argz->var2);
    object_t* new = malloc(sizeof(object_t));
    new->var1 = 10;
    new->var2 = 20;
    return (void*)new;
}

int main(int argc,char *argv[]){
    object_t yeah;
    object_t* yeah2;
    yeah.var1 = 1;
    yeah.var2 = 2;
    pthread_t thread1;
    // create thread takes a void* to args 
    pthread_create(&thread1,NULL,work,(void*)&yeah);
    // to return args from thread cast to void**
    pthread_join(thread1,(void**)&yeah2);
    printf("%d %d\n",yeah2->var1,yeah2->var2);
    
    return 0;

}

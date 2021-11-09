#include "string.h"

string_t* __new_string(){
    return(string_t*)malloc(sizeof(size_t));
}

string_t* string_init(const char * data){
    string_t* string_object = __new_string();
    int length = strlen(data);
    string_object->length = length + 1;
    string_object->value = malloc(sizeof(char)* length);
    if (string_object -> value == NULL) {
        printf("Failed allocate memory for string!\n");
        return NULL;
    }
    strncpy(string_object->value,data,string_object->length);
    return string_object;
}

int string_append(string_t* string, const char *data){
    int original_string_length = string->length; 
    int length = strlen(data);
    while (string->length < length){
        int realloc_length = string->length * 2;
        printf("Reallocating memory to string append %d\n",realloc_length);
        char* tmp = realloc(string->value,sizeof(char) * realloc_length); 
        if (tmp == NULL){
            printf("Failed to realloc for string append!\n");
            return 0;
        }
        string->value = tmp;
        string->length = realloc_length;
    }
    strncat(string->value,data,length);
    return string->length;
}

void string_insert(string_t* string,const char* data){
    // to do 
}
void string_replace(string_t* string,const char* old, const char* new){
    // this is a tough one
}

int string_findf(string_t* string,const char *data){
    int data_length = strlen(data);
    int length = strlen(string->value);
    for (int x = 0; x < length; x++){
        if (strncmp(&string->value[x],data,data_length) == 0) {
            return x;
        }
    }
    return 0;
}

int string_findl(string_t* string,const char *data){
    int data_length = strlen(data);
    int length = strlen(string->value);
    for (; length > 0; length--){
        if (strncmp(&string->value[length],data,data_length) == 0) {
            return length;
        }
    }
    return 0;
}

int string_in(string_t* string,const char* data){
    int data_length = strlen(data);
    int length = strlen(string->value);
    for (int x = 0; x < length; x++){
        if (strncmp(&string->value[x],data,data_length) == 0) {
            return 1;
        }
    }
    return 0;
}

void string_reverse(string_t* string){
    char *start = string->value;
    char *end = string->value;
    while (*end){
        ++end;
    }
    --end;
    for (; start < end; ++start, --end){
        char h = *start;
        char t = *end;
        *start = t;
        *end = h;
    }
}

string_t* string_slice(string_t* string,int start,int end){
    int len = strlen(string->value);
    int bufferSz = end - start + 1;
    char *tempBuffer = malloc(sizeof(char) * bufferSz);
    string_t* result;
    if (start < end && start < len - 1 && end <= len){
        for (int x = 0; start < end; start++){
            char h = string->value[start];
            tempBuffer[x] = h;
            x++;
        }
    } else {
        printf("index out of bounds!\n");
        return NULL;
    }
    result = string_init(tempBuffer);
    free(tempBuffer);
    return result;
}

char* string_at(string_t* string,int index){
    if (index > string->length){
        return NULL; 
    } else {
        return &string->value[index];
    }
}

void string_print(string_t* string){
    printf("%s\n",string->value);
}

int string_size(string_t* string){
    return strlen(string->value) - 1;
}

string_t* string_copy(string_t* string){
    return string_init(string->value);
}

void delete_string(string_t* string){
    free(string->value);
    free(string);
}

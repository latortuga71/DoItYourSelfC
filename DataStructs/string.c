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

void string_reverse(string_t* string){
    int length = strlen(string->value);
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

char* string_at(string_t* string,int index){
    if (index > string->length){
        return NULL; 
    } else {
        return &string->value[index];
    }
}

char string_front(string_t* string){
    return string->value[0];
} 

char string_back(string_t* string){
    return string->value[strlen(string->value) - 1];
}

void string_print(string_t* string){
    printf("%s\n",string->value);
}

int string_size(string_t* string){
    return strlen(string->value) - 1;
}

void delete_string(string_t* string){
    free(string->value);
    free(string);
}

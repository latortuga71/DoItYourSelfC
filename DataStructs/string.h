#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char* value;
    int length;
} string_t;

// private
string_t* __new_string();
// public
// constructor
string_t* string_init(const char*);

// maniuplation
int string_append(string_t*,const char*);
int string_size(string_t*);
void string_reverse(string_t*);
void string_replace(string_t*,const char*,const char*);
string_t* string_copy(string_t*);
string_t* string_slice(string_t*,int,int);
// index methods
char* string_at(string_t*,int idx);
// return address of char at index, needs to be derefernced wit *
int string_in(string_t*,const char*);
int string_findf(string_t*,const char*);
int string_findl(string_t*,const char*);
// print methods
void string_print(string_t*);
// destructor
void delete_string(string_t*);
/// to do
// replace return a new string object replace all occurences
// insert insert a string into a specific index

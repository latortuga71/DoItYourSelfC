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

// index methods
char* string_at(string_t*,int idx);
// return address of char at index, needs to be derefernced wit *
char string_front(string_t*);
char string_back(string_t*);
// return string at front or back no need to dereference
//
//
//
// print methods
void string_print(string_t*);
// destructor
void delete_string(string_t*);
/// to do
// assign copy over the string with a new string and resize if needed
// push back assign char to end of string
// pop back delete char from end of string
// replace return a new string object
// find first return first occurence index
// find last return last occurence index
// reverse reverse string in place

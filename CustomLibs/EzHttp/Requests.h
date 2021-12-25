#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_HEADERS 100
#define MAX_URLPARAM 25
#define MAX_POSTPARAM 25

typedef struct Header{
    char* key;
    char* value;
} Header;

typedef struct BodyParameter{
    char* key;
    char* value;
} BodyParameter;

typedef struct UrlParameter{
    char* key;
    char* value;
} UrlParameter;

typedef struct Request {
    char* type;
    char* path;
    size_t request_size;
    char* request_payload; // GET / HTTP/1.1\r\nHeader:Value\r\n\r\n\r\nUsername=test&password=test\r\n
    Header** headers;
    BodyParameter** post_parameters;
    UrlParameter** url_parameters;
} Request;



Request* newRequest(const char* type,const char* path);
UrlParameter* newUrlParameter(const char* key, const char* value);
BodyParameter* newBodyParameter(const char* key, const char* value);

void sendHttpRequest(Request*,const char*,int);
void buildRequest(Request*);
void buildUrlParameters(Request*);
void addUrlParameter(Request*,UrlParameter*);
void printUrlParameters(Request*);

// TO DOS 
void addHeader(Request*,Header*);
void addBodyParameter(Request*,BodyParameter*);

void buildBodyParameters(Request*);
void buildHeaders(Request*);
void printHeaders(Request*);
void printBodyParameters(Request*);

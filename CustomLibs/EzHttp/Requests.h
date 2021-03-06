#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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
    char* request_payload; 
    Header** headers;
    BodyParameter** post_parameters;
    UrlParameter** url_parameters;
} Request;



Request* newRequest(const char* type,const char* path);
UrlParameter* newUrlParameter(const char* key, const char* value);
BodyParameter* newBodyParameter(const char* key, const char* value);
Header* newHeader(const char* key,const char* value);

void deleteRequest(Request*);
void deleteUrlParameter(UrlParameter*);
void deleteHeader(Header*);
void deleteBodyParameter(BodyParameter*);
void deleteRequestHeaders(Request* );
void deleteRequestUrlParams(Request*);

void exitError(const char*);
void warningError(const char* );
void debugError(const char* );


bool sendHttpRequest(Request*,const char*,const char* port);
bool sendHttpsRequest(Request*,const char*,const char* port);
SSL_CTX* InitSSLCtx();

void buildRequest(Request*,const char*);
bool buildUrlParameters(Request*);
char* buildBodyParameters(Request*);

void printUrlParameters(Request*);
void printHeaders(Request*);
void printBodyParameters(Request*);

bool addHeader(Request*,Header*);
bool addBodyParameter(Request*,BodyParameter*);
bool addUrlParameter(Request*,UrlParameter*);

char* buildHeaders(Request*);



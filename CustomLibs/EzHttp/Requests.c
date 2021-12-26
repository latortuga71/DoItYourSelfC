#include "Requests.h"

/*
 * TO DO
 * Add error handling for malloc and calloc
 * Free all allocated memory to avoid memory leaks
*/  

void exitError(const char* msg){
    printf("ERROR: %s\n",msg);
    exit(1);
}

void debugError(const char* msg){
    printf("DEBUG: %s\n",msg);
}

void warningError(const char *msg){
    printf("WARNING: %s\n",msg);
}

Header* newHeader(const char* key,const char* value){
    Header* h = malloc(sizeof(Header));
    h->key = malloc(sizeof(char) * strlen(key));
    h->value = malloc(sizeof(char) * strlen(value));
    strncpy(h->key,key,strlen(key));
    strncpy(h->value,value,strlen(value));
    return h;
}

void deleteHeader(Header* h){
    free(h->key);
    free(h->value);
    free(h);
}

UrlParameter* newUrlParameter(const char* key,const char* value){
    UrlParameter* u = malloc(sizeof(UrlParameter));
    u->key = malloc(sizeof(char)* strlen(key));
    u->value = malloc(sizeof(char)* strlen(value));
    strncpy(u->key,key,strlen(key));
    strncpy(u->value,value,strlen(value));
    return u;
}

void deleteUrlParameter(UrlParameter* u){
    free(u->key);
    free(u->value);
    free(u);
}

Request* newRequest(const char* type,const char* path){
    Request* r = malloc(sizeof(Request));
    r->headers = calloc(MAX_HEADERS,sizeof(Header*));
    r->url_parameters = calloc(MAX_URLPARAM,sizeof(UrlParameter*)); // init to zero with calloc so loop to null works?
    r->type = malloc(sizeof(char)* strlen(type));
    r->path = malloc(sizeof(char)* strlen(path));
    strncpy(r->type,type,strlen(type));
    strncpy(r->path,path,strlen(path));
    return r;
}

void deleteRequest(Request* r){
    free(r->headers);
    free(r->url_parameters);
    free(r->path);
    free(r->request_payload);
    free(r->type);
    free(r);
}

void printHeaders(Request* r){
    for (int x = 0; x < MAX_URLPARAM; x++){
        if (r->headers[x] == NULL){
            break;
        } else {
            printf("%s: %s\n",r->headers[x]->key,r->headers[x]->value);
        }
    }
}
void printUrlParameters(Request* r){
    for (int x = 0; x < MAX_URLPARAM; x++){
        if (r->url_parameters[x] == NULL){
            break;
        } else {
            printf("%s=%s\n",r->url_parameters[x]->key,r->url_parameters[x]->value);
        }
    }
}

bool addHeader(Request* r, Header* h){
    int x = 0;
    int in_bounds = 0;
    for (; x < MAX_HEADERS; x++) {
        if (r->headers[x] == NULL){
            in_bounds = 1;
            break;
        }
    }
    if (in_bounds){
        r->headers[x] = h;
        return true;
    } else{
        warningError("Failed to append header, max header limit of 100 reached");
        return false;
    }
}

bool addUrlParameter(Request* r,UrlParameter* u){
    int in_bounds = 0;
    int x = 0;
    for (; x < MAX_URLPARAM; x++){
        if (r->url_parameters[x] == NULL){
            in_bounds = 1;
            break;
        }
    }
    if (in_bounds) {
        r->url_parameters[x] = u;
        return true;
    } else {
        warningError("Failed to append url parameter, maximum parameter limit of 25 reached");
        return false;
    }
}
char* buildHeaders(Request* r){
    int x = 0;
    int value_len,key_len,total_len;
    int headers_buffer_size = 0;
    char* tmp_buffer = NULL;
    char* headers_buffer = calloc(0,sizeof(char));
    for (; x < MAX_HEADERS; x++) {
        if (r->headers[x] == NULL){
            break;
        }
        key_len = strlen(r->headers[x]->key);
        value_len = strlen(r->headers[x]->value);
        total_len = key_len + value_len + 4; // colon and space and newline and carriage return
        tmp_buffer = malloc(sizeof(char) * total_len);
        if (tmp_buffer == NULL){
            warningError("Failed to malloc temp buffer");
            return NULL;
        }
        sprintf(tmp_buffer,"%s: %s\n",r->headers[x]->key,r->headers[x]->value);
        headers_buffer_size = headers_buffer_size + total_len;
        headers_buffer = realloc(headers_buffer, sizeof(char) * total_len + headers_buffer_size);
        strncat(headers_buffer,tmp_buffer,total_len);
        free(tmp_buffer);
    }
    return headers_buffer;
}

bool buildUrlParameters(Request* r){
    int x = 0;
    int value_len,key_len,total_len;
    int url_buffer_size = 1;
    char* tmp_buffer;
    char* url_buffer = malloc(sizeof(char)*1); 
    strncpy(url_buffer,"?",1);
    for (; x < MAX_URLPARAM; x++){
        if (r->url_parameters[x] == NULL){
            break;
        }
        key_len = strlen(r->url_parameters[x]->key);
        value_len = strlen(r->url_parameters[x]->value);
        total_len = key_len + value_len + 2; // = and eol
        tmp_buffer = malloc(sizeof(char) * total_len);
        if (tmp_buffer == NULL){
            warningError("Failed to malloc temp buffer");
            return false;
        }
        sprintf(tmp_buffer,"%s=%s&",r->url_parameters[x]->key,r->url_parameters[x]->value);
        url_buffer_size = url_buffer_size + total_len;
        url_buffer = realloc(url_buffer, sizeof(char) * total_len + url_buffer_size);
        strncat(url_buffer,tmp_buffer,total_len);
        free(tmp_buffer);
    }
    r->path = realloc(r->path,sizeof(char) * url_buffer_size + strlen(r->path));
    strncat(r->path,url_buffer,url_buffer_size-1); // subtract 1 to remove trailing ampersand
    free(url_buffer);
    return true;
}

void buildRequest(Request* r, const char* hostname){
    // build base of request payload GET / HTTP/1.1
    // build URL PARAMS AND PATH
    buildUrlParameters(r); // adds url parmaeters to path variable
    // auto add Host header
    Header* host_header = newHeader("Host",hostname);
    Header* user_agent = newHeader("User-Agent","EzHttp/0.0.1");
    addHeader(r,host_header);
    addHeader(r,user_agent);
    char* headers_payload = buildHeaders(r); // gets headers block into pointer to heap
    if (headers_payload == NULL){
        exitError("Failed to gather headers exiting...");
    }
    // done with host header and url
    size_t type_size = strlen(r->type)+ 1; // account for extra space after type
    size_t path_size = strlen(r->path) + 12; // accounting for ' HTTP/1.1\r\n'
    size_t headers_size = strlen(headers_payload); 
    size_t total_base = type_size + path_size + headers_size + 1;
    r->request_size = total_base;
    r->request_payload = malloc(sizeof(char) * total_base);
    sprintf(r->request_payload,"%s %s HTTP/1.1\n%s\r\n",r->type,r->path,headers_payload);
    printf("%s",r->request_payload);
    // clean up
    deleteHeader(host_header);
    deleteHeader(user_agent);
    free(headers_payload);
    // to do post params and provide content length header
}

bool sendHttpRequest(Request* r, const char* hostname,int port){
    char* response = malloc(sizeof(char) * 1);
    size_t resp_sz;
    size_t resp_buffer_len = 512;
    char resp_buffer[resp_buffer_len];
    int status,socketfd;
    struct addrinfo hints;
    struct addrinfo* res;
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    // gets ip address for hostname
    if ((status = getaddrinfo(hostname,"http", &hints,&res)) != 0){
        warningError("Failed to call getaddrinfo");
        return false;
    }
    // free res later
    socketfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if (socketfd == -1){
        warningError("Failed to open socket");
        return false;
    }
    if (connect(socketfd,res->ai_addr,res->ai_addrlen) != 0 ){
        warningError("Failed to connect");
        return false;
    }
    freeaddrinfo(res);
    // send
    int bytes_recv = 1; // so we actualy get into the while loop
    int bytes_sent = send(socketfd,r->request_payload,r->request_size,0);
    // recv
    while (recv(socketfd,resp_buffer,resp_buffer_len,0) > 0 ){
        if (bytes_recv > 0){
            response = realloc(response,sizeof(char) * resp_buffer_len + resp_sz);
            strncat(response,resp_buffer,resp_buffer_len);
            resp_sz += resp_buffer_len;
        }
    }
    printf("%s",response);
    free(response);
    close(socketfd);
    return true;
}

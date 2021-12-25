#include "Requests.h"

/*
 * TO DO
 * Add error handling for malloc and calloc
 * Free all allocated memory to avoid memory leaks
*/  

UrlParameter* newUrlParameter(const char* key,const char* value){
    UrlParameter* u = malloc(sizeof(UrlParameter));
    u->key = malloc(sizeof(char)* strlen(key));
    u->value = malloc(sizeof(char)* strlen(value));
    strncpy(u->key,key,strlen(key));
    strncpy(u->value,value,strlen(value));
    return u;
}


Request* newRequest(const char* type,const char* path){
    Request* r = malloc(sizeof(Request));
    r->url_parameters = calloc(MAX_URLPARAM,sizeof(UrlParameter*)); // init to zero with calloc so loop to null works?
    r->type = malloc(sizeof(char)* strlen(type));
    r->path = malloc(sizeof(char)* strlen(path));
    strncpy(r->type,type,strlen(type));
    strncpy(r->path,path,strlen(path));
    return r;
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

void addUrlParameter(Request* r,UrlParameter* u){
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
    } else {
        printf("Failed to append url parameter, maximum parameter limit of 25 reached\n");
    }
}

void buildUrlParameters(Request* r){
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
        printf("Total length for this url parameter %d\n",total_len);
        //tmp_buffer = malloc(sizeof(char) * total_len);
        tmp_buffer = malloc(sizeof(char) * total_len);
        if (tmp_buffer == NULL){
            printf("Failed to malloc temp buffer\n");
            return;
        }
        printf("Created temp buffer\n");
        sprintf(tmp_buffer,"%s=%s&",r->url_parameters[x]->key,r->url_parameters[x]->value);
        printf("Length of sprintf buffer %d\n",strlen(tmp_buffer));
        printf("Attempting to append to master buffer\n");
        printf("url buffer size %d\n",strlen(url_buffer));
        printf("Reallocating buffer\n");
        url_buffer = realloc(url_buffer, sizeof(char) * total_len + url_buffer_size);
        url_buffer_size = total_len + url_buffer_size;
        printf("new size of url buffer %d\n",url_buffer_size);  
        // now append with stncat the temp buffer to current urlbuffer
        strncat(url_buffer,tmp_buffer,total_len);
        printf("%s\n",url_buffer);
        free(tmp_buffer);
    }
    // here is where we take the big ass buffer and concat it to the path string
    r->path = realloc(r->path,sizeof(char) * url_buffer_size + strlen(r->path));
    strncat(r->path,url_buffer,url_buffer_size-1); // subtract 1 to remove trailing ampersand
    return;
}

void buildRequest(Request* r){
    // build base of request payload GET / HTTP/1.1
    // build URL PARAMS AND PATH
    buildUrlParameters(r); // adds url parmaeters to path variable
    size_t type_size = strlen(r->type)+ 1; // account for extra space after type
    size_t path_size = strlen(r->path) + 12; // accounting for ' HTTP/1.1\r\n'
    size_t total_base = type_size + path_size + 1;
    r->request_size = total_base;
    r->request_payload = malloc(sizeof(char) * total_base);
    sprintf(r->request_payload,"%s %s HTTP/1.1\r\n\r\n",r->type,r->path);
    printf("%s\n",r->request_payload);
    // build headers would increase the size of the request_size and append to request_payload
    // to do // 
    // build post params would increase the size of the request_zie and append to request_payload 
    // to do
}

void sendHttpRequest(Request* r, const char* hostname,int port){
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
        fprintf(stdout,"errr getaddrinfo error");
        exit(1);
    }
    // free res later
    socketfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if (socketfd == -1){
        printf("Error Creating Socket");
        exit(1);
    }
    if (connect(socketfd,res->ai_addr,res->ai_addrlen) != 0 ){
        printf("Failed to connect!\n");
        exit(1);
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
    close(socketfd);
    
}

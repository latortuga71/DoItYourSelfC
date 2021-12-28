#include "Requests.h"

/*
 * TO DO
 * Add error handling for malloc and calloc
 * Add helper functions for build request and have switch statement run based on what type of request is.
 * so we dont try to allocation post pararameters when its a get request etc.
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

BodyParameter* newBodyParameter(const char* key, const char* value){
    BodyParameter* b = malloc(sizeof(BodyParameter));
    b->key = malloc(sizeof(char) * strlen(key));
    b->value = malloc(sizeof(char) * strlen(value));
    strncpy(b->key,key,strlen(key));
    strncpy(b->value,value,strlen(value));
    return b;
}

void deleteBodyParameter(BodyParameter* b){
    free(b->key);
    free(b->value);
    free(b);
}


Request* newRequest(const char* type,const char* path){
    Request* r = malloc(sizeof(Request));
    r->headers = calloc(MAX_HEADERS,sizeof(Header*));
    r->url_parameters = calloc(MAX_URLPARAM,sizeof(UrlParameter*)); // init to zero with calloc so loop to null works?
    r->post_parameters = calloc(MAX_POSTPARAM,sizeof(BodyParameter*));
    r->type = malloc(sizeof(char)* strlen(type));
    r->path = malloc(sizeof(char)* strlen(path));
    strncpy(r->type,type,strlen(type));
    strncpy(r->path,path,strlen(path));
    return r;
}

void deleteRequest(Request* r){
    free(r->post_parameters);
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

void printBodyParameters(Request* r){
    for (int x = 0; x < MAX_POSTPARAM; x++){
        if (r->post_parameters[x] == NULL){
            break;
        } else {
            printf("%s=%s\n",r->post_parameters[x]->key,r->post_parameters[x]->value);
        }
    }
}

bool addBodyParameter(Request* r, BodyParameter* b){
    int x = 0;
    int in_bounds = 0;
    for (; x < MAX_POSTPARAM; x++){
        if (r->post_parameters[x] == NULL){
            in_bounds = 1;
            break;
        }
    }
    if (in_bounds){
        r->post_parameters[x] = b;
    } else {
        warningError("Failed to append post parameter, max limit of 25 parameters reached");
        return false;
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

char* buildBodyParameters(Request* r){
    int x = 0;
    int value_len,key_len,total_len;
    int body_buffer_size = 0;
    char* tmp_buffer;
    char* body_buffer = calloc(0,sizeof(char));
    for (; x < MAX_POSTPARAM; x++){
        if (r->post_parameters[x] == NULL){
            break;
        }
        key_len = strlen(r->post_parameters[x]->key);
        value_len = strlen(r->post_parameters[x]->value);
        total_len = key_len + value_len + 2; // = and eol
        tmp_buffer = malloc(sizeof(char) * total_len);
        if (tmp_buffer == NULL){
            warningError("Failed to malloc temp buffer");
            return NULL;
        }
        body_buffer_size += total_len + 1;
        sprintf(tmp_buffer,"%s=%s&",r->post_parameters[x]->key,r->post_parameters[x]->value);
        body_buffer = realloc(body_buffer, sizeof(char) * body_buffer_size + total_len);
        strncat(body_buffer,tmp_buffer,total_len);
        free(tmp_buffer);
    }
    return body_buffer;
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
    // Build Url Params //
    if (!buildUrlParameters(r))
        exitError("Failed to add url parameters Exiting..");
    // Add Default Headers //
    Header* host_header = newHeader("Host",hostname);
    Header* user_agent = newHeader("User-Agent","EzHttp/0.0.1");
    if (!addHeader(r,host_header))
        warningError("Failed to add Header");
    if (!addHeader(r,user_agent))
        warningError("Failed to add Header");
    // Build Post Parameters //
    char* body_parameters = buildBodyParameters(r);
    if (body_parameters == NULL)
        exitError("Failed to gather body parameters exiting...");
    int body_content_length = strlen(body_parameters);
    char body_content_length_str[100];
    sprintf(body_content_length_str,"%d",body_content_length);
    //Header* content_length = newHeader("Content-Length",body_content_length_str);
    Header* accept_header = newHeader("accept","*/*");
    Header* content_type = newHeader("Content-Type","application/x-www-form-urlencoded");
    if (!addHeader(r,content_type))
        warningError("Failed to add content type header");
    if (!addHeader(r,accept_header))
        warningError("Failed to add accept header");
    //if (!addHeader(r,content_length))
    //    warningError("Failed to add content length header");
    /// Build Headers ///
    char* headers_payload = buildHeaders(r); // gets headers block into pointer to heap
    if (headers_payload == NULL)
        exitError("Failed to gather headers exiting...");
    // Build Request with all parts
    size_t type_size = strlen(r->type)+ 1; // account for extra space after type
    size_t path_size = strlen(r->path) + 12; // accounting for ' HTTP/1.1\r\n'
    size_t headers_size = strlen(headers_payload); 
    size_t body_size = strlen(body_parameters);
    size_t total_base = type_size + path_size + headers_size + body_size + 15;
    r->request_size = total_base;
    r->request_payload = malloc(sizeof(char) * total_base);
    sprintf(r->request_payload,"%s %s HTTP/1.1\n%s\n%s",r->type,r->path,headers_payload);//body_parameters);
    printf("%s",r->request_payload);
    printf("#############\n\n\n\n");
    //  Clean up Allocations ///
    deleteHeader(host_header);
    deleteHeader(user_agent);
    //deleteHeader(content_length);
    deleteHeader(content_type);
    free(headers_payload);
    free(body_parameters);
}

SSL_CTX* InitSSLCtx(){
    SSL_METHOD *method;
    SSL_CTX *ctx;
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    //method = TLSv1_2_client_method();  /* Create new client-method instance 
    method = SSLv23_client_method();
    ctx = SSL_CTX_new(method);   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

bool sendHttpsRequest(Request* r, const char* hostname,const char* port){
    // SSL SETUP
    SSL_CTX* ctx;
    SSL* ssl;
    SSL_library_init();
    ctx = InitSSLCtx();
    ssl = SSL_new(ctx);

    char* response = calloc(0,sizeof(char));
    size_t resp_sz;
    size_t resp_buffer_len = 1024;
    char resp_buffer[resp_buffer_len];
    int status,socketfd;
    struct addrinfo hints;
    struct addrinfo* res;
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    // gets ip address for hostname
    if ((status = getaddrinfo(hostname,port, &hints,&res)) != 0){
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
    // SSL SET SOCKET FD
    SSL_set_fd(ssl,socketfd);
    if (SSL_connect(ssl) == -1){
        warningError("Failed to connect via ssl.");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return false;
    }
    // send
    int bytes_recv;
    //int bytes_sent = send(socketfd,r->request_payload,r->request_size,0);
    int bytes_sent = SSL_write(ssl,r->request_payload,r->request_size);
    if (bytes_sent <= 0) {
        warningError("Failed to write bytes over ssl");
        SSL_free(ssl);
        SSL_CTX_free(ctx);
        return false;
    }
    while ((bytes_recv = SSL_read(ssl,resp_buffer,resp_buffer_len)) > 0){
        resp_sz += bytes_recv;
        response = realloc(response,sizeof(char) * resp_sz);
        strncat(response,resp_buffer,bytes_recv);
    }
    printf("%s",response);
    free(response);
    SSL_free(ssl);
    close(socketfd);
    SSL_CTX_free(ctx);
    return true;
}

bool sendHttpRequest(Request* r, const char* hostname,const char* port){
    char* response = calloc(0,sizeof(char));
    size_t resp_sz;
    size_t resp_buffer_len = 1024;
    char resp_buffer[resp_buffer_len];
    int status,socketfd;
    struct addrinfo hints;
    struct addrinfo* res;
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    // gets ip address for hostname
    if ((status = getaddrinfo(hostname, port, &hints,&res)) != 0){
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
    int bytes_recv; // so we actualy get into the while loop
    int bytes_sent = send(socketfd,r->request_payload,r->request_size,0);
    // recv
    while ((bytes_recv = recv(socketfd,resp_buffer,resp_buffer_len,0)) > 0){
        resp_sz += bytes_recv;
        response = realloc(response,sizeof(char) * resp_sz);
        strncat(response,resp_buffer,bytes_recv);
    }
    printf("%s",response);
    free(response);
    close(socketfd);
    return true;
}

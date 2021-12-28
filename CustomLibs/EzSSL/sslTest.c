#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"


void FatalError(const char* msg){
    printf("%s\n",msg);
    exit(1);
}

void InitOpenSSL(){
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();
}


int main(int argc, char** argv){
    int res;
    InitOpenSSL();
    //using bio to set up a connection instead of socket
    BIO* bio;
    // ssl stuff
    SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
    SSL* ssl;
    if (!SSL_CTX_load_verify_locations(ctx,NULL,"/etc/pki/tls/cert.pem")){
        printf("SSL CTX Load Verify Error\n");
        exit(1);
    }
    bio = BIO_new_ssl_connect(ctx);
    BIO_get_ssl(bio,&ssl);
    SSL_set_mode(ssl,SSL_MODE_AUTO_RETRY);
    BIO_set_conn_hostname(bio,"tls-v1-2.badssl.com:1012");
    if (BIO_do_connect(bio) <= 0)
        FatalError("Failed to start connection");
    BIO_do_handshake(bio);
    if (SSL_get_verify_result(ssl) != X509_V_OK){
        printf("Failed to validate certificate! We can still connect though\n");
    }
    printf("Setting up get request");
    // send a get request
    char request_buffer[100];
    size_t response_buffer_len = 512; 
    char response_buffer[response_buffer_len];
    char* response = calloc(0,sizeof(char));
    size_t response_Sz = 0;
    sprintf(request_buffer,"GET / HTTP/1.1\r\n\r\n");
    size_t request_buffer_len = strlen(request_buffer);
    // write to socket
    if (BIO_write(bio,request_buffer,request_buffer_len) <= 0){
        if (! BIO_should_retry(bio)){
            printf("Failed to write to socket! Exiting");
            exit(1);
        }
        printf("Successfully wrote to socket upon retry");
    }
    printf("Sent GET Request!\n");
    // read from socket
    int bytesRead = BIO_read(bio,response_buffer,response_buffer_len);
    printf("Read\n");
    if (bytesRead == 0){
        printf("Connection Closed!");
        printf("Response -> %s\n",response_buffer);
        free(response);
        return 0;
    }
    if (bytesRead < 0){
        printf("Failed to read from socket!");
        if (!BIO_should_retry(bio)){
            FatalError("Failed to handle read! exiting...");
        }
        printf("Retry worked!");
    }
    printf("Before while loop");
    while (bytesRead > 0){
        response_Sz += response_buffer_len;
        response = realloc(response,sizeof(char) * response_Sz);
        strncat(response,response_buffer,response_buffer_len);
        bytesRead = BIO_read(bio,response_buffer,response_buffer_len);
    }
    printf("%s",response);
    free(response);
    BIO_free_all(bio);
    SSL_CTX_free(ctx);





    /*
    // bio stuff
    bio = BIO_new_connect("localhost:8000");
    if (bio == NULL)
        FatalError("Failed to connect using bio");
    if (BIO_do_connect(bio) <= 0)
        FatalError("Failed to handle new connection");
    // send a get request
    char request_buffer[100];
    size_t response_buffer_len = 512; 
    char response_buffer[response_buffer_len];
    char* response = calloc(0,sizeof(char));
    size_t response_Sz = 0;
    sprintf(request_buffer,"GET / HTTP/1.1\r\n\r\n");
    size_t request_buffer_len = strlen(request_buffer);
    // write to socket
    if (BIO_write(bio,request_buffer,request_buffer_len) <= 0){
        if (! BIO_should_retry(bio)){
            printf("Failed to write to socket! Exiting");
            exit(1);
        }
        printf("Successfully wrote to socket upon retry");
    }
    printf("Sent GET Request!\n");
    // read from socket
    int bytesRead = BIO_read(bio,response_buffer,response_buffer_len);
    if (bytesRead == 0){
        printf("Connection Closed!");
        printf("Response -> %s\n",response_buffer);
        free(response);
        return 0;
    }
    if (bytesRead < 0){
        printf("Failed to read from socket!");
        if (!BIO_should_retry(bio)){
            FatalError("Failed to handle read! exiting...");
        }
        printf("Retry worked!");
    }
    while (bytesRead > 0){
        printf("%d\n",bytesRead);
        response_Sz += response_buffer_len;
        response = realloc(response,sizeof(char) * response_Sz + 1);
        strncat(response,response_buffer,response_buffer_len);
        bytesRead = BIO_read(bio,response_buffer,response_buffer_len);
    }
    printf("%s",response);
    free(response);
    BIO_free_all(bio);
    */
    return 0;
}

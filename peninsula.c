#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "ErrorT.h"
#include "transportlayer/tcp.h"
#include "Requestparsing/parsing.h"
#include "Connection/clientIP.h"
#include "Connection/rawhttp.h"
#include "Requestparsing/request.h"
#include "conf/parseconfig.h"

int main(void) {
    /*1- TCP CONNECTION PROTOCOL
        sets up, via OS socket, the fluid connection between the client and the server
        pretty important :) 
    */
    char *config_file = "./conf/httpd.conf";
    int *count = malloc(sizeof(int));
    config_hashmap *config_map = parseconfig(config_file, count); 
    int listen_sock = openTCPSocket(8080, 5);

    
    for (;;) {
        /* 2- CONNECTION SETUP PROTOCOL
            determine the client ip, reads the raw HTTP data, and should theoretically do the TLS handshake(hasn't been implemented yet)*/    
        int client_sock = clientIP(listen_sock);
        char *buffer = rawhttp(client_sock);


        /* 3- REQUEST PARSING PROTOCOL
            Parses the request line, parses the headers, and stores 
        */
        request_hashmap *request_map = parser(buffer);
       
        const char *response = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Connection: close\r\n"
            "Server: Peninsula\r\n"
            "\r\n"
            "Hello, world!\n";

        send(client_sock, response, strlen(response), 0);
        close(client_sock);
        
    }
   return 0;
}

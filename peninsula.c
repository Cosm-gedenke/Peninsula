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
#include "host/matchost.h"
#include "conf/defconfig.h"
#include "path/matchpath.h"

int main(void) {
    /*1- TCP CONNECTION PROTOCOL
        sets up, via OS socket, the fluid connection between the client and the server
        pretty important :) 
    */
    config_record *main_config = calloc(1, sizeof(config_record));
    defconfig(main_config);
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
        /* 4- MATCH THE VIRTUAL HOST
            grabs the Host header and verifies it exists, fallback onto main configuration if it doesn't exist
        */
        printf("bazinga"); fflush(stdout);
        config_record *config = matchost(config_map, request_map, main_config);


        /* 5- URI and file mapping
            applies document root, might implement more eventually through modules
            resolves to the filesystem
        */
        printf("bazinga"); fflush(stdout);
        char *web_path = matchpath(config->chosenhost,request_map); 
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

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
#include "response/response.h"
#include "response/readcontent.h"

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
    char *reqtype = calloc(20,sizeof(char));
    response_map *global_response = calloc(1, sizeof(response_map));
    
    for (;;) {
        /* 2- CONNECTION SETUP PROTOCOL
            determine the client ip, reads the raw HTTP data, and should theoretically do the TLS handshake(hasn't been implemented yet)*/    
        int client_sock = clientIP(listen_sock);
        char *buffer = rawhttp(client_sock);


        /* 3- REQUEST PARSING PROTOCOL
            Parses the request line, parses the headers, and stores 
        */
        request_hashmap *request_map = parser(buffer, &reqtype);
         /* 4- MATCH THE VIRTUAL HOST
            grabs the Host header and verifies it exists, fallback onto main configuration if it doesn't exist
        */
        config_record *config = matchost(config_map, request_map, main_config);


        /* 5- URI AND FILE MAPPING
            applies document root, might implement more eventually through modules
            resolves to the filesystem
        */
        char *web_path = matchpath(config->chosenhost,request_map, reqtype);

        /* 6- AUTHENTICATION AND AUTHORIZATION
            FIXME not yet implemented
            not entirely sure where and when this comes into play
        */

        /* 7- CONTENT GENERATION
            generates the content preparing it for servicing in the response
            the initial steps of building the response struct
        */
        global_response = readcontent(web_path,reqtype);
        
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

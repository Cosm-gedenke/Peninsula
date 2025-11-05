#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../ErrorT.h"

/*
opens a socket to the respective client address
*/
int clientIP(int listen_sock) {
    struct sockaddr_in clientaddr;
    socklen_t  addrlen = sizeof(clientaddr);
    int client_sock = accept(listen_sock,(struct sockaddr *)&clientaddr, &addrlen);
    
    if(client_sock < 0) {
        ErrorT("accept client failed");
    }
    return client_sock;

}

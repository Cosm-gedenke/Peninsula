#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "../ErrorT.h"


void constructAddress(struct sockaddr_in *echoserveraddress, unsigned short port) {
    memset(echoserveraddress, 0, sizeof(echoserveraddress)); // Zero out the structure 1*
    echoserveraddress->sin_family = AF_INET;                  // internet address family 2*
    echoserveraddress->sin_addr.s_addr = htonl(INADDR_ANY);   // any incoming interface 3*
    echoserveraddress->sin_port = htons(port);                //local port
}

int openTCPSocket(unsigned short port, int maxpends) {

    int sock;
    struct sockaddr_in echoservaddress;
    //Standard stuff, uses built in socket function to open a tcp connection
    if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        ErrorT("failed to open socket");
    }
    constructAddress(&echoservaddress, port);

    //binds socket to local address *4
    if(bind(sock, (struct sockaddr * ) &echoservaddress, sizeof(echoservaddress)) < 0) {
        ErrorT("failed to bind");
    }
    
    if (listen(sock, maxpends)< 0) {
        ErrorT("failed to listen");
    }
     
    return sock;
    
}


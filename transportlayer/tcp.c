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

    //makes it so we can use the same socket while it is in TIME_WAIT, it is important however to note that this should be made a module as it should not be used in an actual production 
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //binds socket to local address *4
    if(bind(sock, (struct sockaddr * ) &echoservaddress, sizeof(echoservaddress)) < 0) {
        ErrorT("failed to bind");
    }
    
    if (listen(sock, maxpends)< 0) {
        ErrorT("failed to listen");
    }
     
    return sock;
    
}


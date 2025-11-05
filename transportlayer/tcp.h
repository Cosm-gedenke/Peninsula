
#ifndef TCP_H
#define TCP_H

void constructAddress(struct sockaddr_in *echoserveraddress, unsigned short port);

int openTCPSocket(unsigned short port, int maxpends);

#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../ErrorT.h"
#include <stdlib.h>
/*
     Receives information given by the client socket
*/
char *rawhttp(int client_sock) {
    char *buffer = malloc(2048);
    if (!buffer) return NULL;

    ssize_t bytes = recv(client_sock, buffer, 2047, 0);
    if (bytes < 1) {
        close(client_sock);
        free(buffer);
        return NULL;
    }
    buffer[bytes] = '\0';
    return buffer;
}

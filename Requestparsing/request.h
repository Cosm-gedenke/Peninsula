#ifndef REQUEST_H
#define REQUEST_H

typedef struct {
    char *reqline;
    char *host;
    char *user;
    char *accept;
    char *acceptl;
    char *accepte;
    char *connection;
    char *contentlength;
    char *cookie;
    char *referer;
    char *customheaders;
     
} request_record;

void freerequest(request_record* req);
#endif

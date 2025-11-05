#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "request.h"
#include "../ErrorT.h"


/*
trims the header value so that we only grab the information we actually want from the http request line
*/
char *trimheadervalue(char *headerline, const char *headername) {
    size_t namelen = strlen(headername);
    char *valuestart = headerline + namelen + 1;    
    return strdup(valuestart);
}

void freerequest(request_record *request) {
    free(request->reqline);
    free(request->host);
    free(request->user);
    free(request->accept);
    free(request->acceptl);
    free(request->accepte);
    free(request->connection);
    free(request->contentlength);
    free(request->cookie);
    free(request->referer);
    free(request->customheaders);
    free(request);
}

/*
     does the job and parses the raw http data onto the request_record struct
*/
request_record *parser(char *buffer) {
    if (!buffer) ErrorT("given buffer is invalid");
    char* token;
    char* rest = buffer;
    int i = 0;
    int size = 10;
    request_record *request;

    request = calloc(1, sizeof(request_record));
    if (!request) ErrorT("can't alloc memory");
    while ((token = strtok_r(rest, "\r\n", &rest))) {
        if (i == 0) {
            request->reqline = strdup(token);
            if(!request->reqline) ErrorT("can't alloc memory");
            i++;
            continue;
        }
        if (strncmp(token, "Host:", 5) == 0) {
            request->host = trimheadervalue(token, "Host:");
            if(!request->host) ErrorT("can't alloc host");
            continue;
        }
        else if(strncmp(token, "User-Agent:", 11) == 0) {
            request->user = trimheadervalue(token, "User-Agent:");
            if(!request->user) ErrorT("can't alloc user"); 
            continue;
        }
        else if(strncmp(token, "Accept-Language:", 16) == 0) {
            request->acceptl = trimheadervalue(token, "Accept-Language:");
            if(!request->acceptl) ErrorT("can't alloc acceptl"); 
            continue;
        }
        else if(strncmp(token, "Accept-Encoding:", 16) == 0)
        {
            request->accepte = trimheadervalue(token, "Accept-Encoding:");
            if(!request->accepte) ErrorT("can't alloc accepte"); 
            continue;
        }
        else if(strncmp(token, "Accept:", 7) == 0) {
            request->accept = trimheadervalue(token, "Accept:");
            if(!request->accept) ErrorT("can't alloc accept"); 
            continue;
        }
        else if(strncmp(token, "Connection:", 11) == 0) {
            request->connection = trimheadervalue(token, "Connection:");
            if(!request->connection) ErrorT("can't alloc connection"); 
            continue;
        }
        else if(strncmp(token, "Cookie:", 7) == 0) {
            request->cookie = trimheadervalue(token, "Cookie:");
            if(!request->cookie) ErrorT("can't alloc cookie"); 
            continue;
        }
        else if (strncmp(token, "Referer:", 8) == 0) {
            request->referer = trimheadervalue(token, "Referer:");
            if(!request->referer) ErrorT("can't alloc referer");
            continue;
        }
        //else custom headers in a hashmap, fix this tommorrow
    }
    return request;
}


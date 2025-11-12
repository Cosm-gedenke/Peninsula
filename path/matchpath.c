#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Requestparsing/request.h"
#include "../ErrorT.h"
#include <limits.h>

char* matchpath(char* chosenhost, request_hashmap *map) {
    printf("bazinga"); fflush(stdout);
    //FIXME not a flexible approach
    char *filepath = malloc(25+strlen(chosenhost));
    if (!filepath)
        ErrorT("can't allocate filepath");
    sprintf(filepath, "/srv/vhosts/%s/public_html", chosenhost);
    //FIXME implement functionality for more header types
    request_record *req = requests_lookup(map,"HTTP");
    char *path = strtok(req->header, " ");
    path = strtok(NULL, " ");
    char *matchedpath = malloc(25+strlen(chosenhost)+strlen(path));
    if (!matchedpath)
        ErrorT("can't allocate matchedpath");
    
    sprintf(matchedpath, "%s%s", filepath, path);
    char *actualpath = malloc(PATH_MAX);
    char * res = realpath(matchedpath, actualpath);
    if(res)
        return res; 
    else {
        ErrorT("can't match the file");
        return NULL;
    }
}

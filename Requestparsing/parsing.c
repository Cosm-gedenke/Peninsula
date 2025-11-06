#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "request.h"
#include "../ErrorT.h"
#include "../hash/hash.h"



/*
     does the job and parses the raw http data onto the request_record struct
*/
request_hashmap *parser(char *buffer) {
    if (!buffer)
        ErrorT("given buffer is invalid");
    char* token;
    char* rest = buffer;
    int i = 0;
    int size = 10;
    request_hashmap *map = calloc(1, sizeof(request_hashmap));
        while ((token = strtok_r(rest, "\r\n", &rest))) {
        request_record *request = calloc(1, sizeof(request_record));
        if (!request)
            ErrorT("can't alloc memory");
        
        request->header = malloc(strlen(token));
        request->header = strdup(token);
        requests_insert(map, request);
    }
    free(token);
    return map;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "request.h"
#include "../hash/hash.h"
void requests_insert(request_hashmap *map, request_record *request) {
    unsigned int index = hash(request->header);
    request->next = map->requests[index];
    map->requests[index] = request;
}



request_record * requests_lookup(request_hashmap *map, const char *header) {
    unsigned int index = hash(header);
    request_record *curr = map->requests[index];
    while (curr) {
        if (strstr(curr->header,header) != NULL)
            return curr;
        curr = curr->next;
    }
    return NULL;
} 
void freerequesthash(request_hashmap *map) {
    for(int i=0; i<256; i++) {
        while(map->requests[i] != NULL) {
            request_record *next = map->requests[i]->next;
            freerequest(map->requests[i]);
            map->requests[i] = next;
        }
    }
}






void freerequest(request_record *req) {
    free(req->header);
    free(req);
}

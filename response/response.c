#include <stdio.h>
#include <stdlib.h>
#include "response.h"


void response_insert(response_map *map, response *rep) {
    unsigned int index = hash(rep->header);
    rep->next = map->headers[index];
    map->headers[index] = rep;
}

char* configs_lookup(response_map *map,char *header) {
    unsigned int index = hash(header);
    response *curr = map->headers[index];
    while (curr) {
        if (strstr(rep->header,header) != NULL)
            return curr;
        curr = curr->next;
    }
    return NULL;
} 

void freeresponse(response *rep) {
    free(rep->header);
    free(rep);
}

void freeresponsehash(response_map *map) {
    for(int i=0; i<256; i++) {
        while(map->configs[i] != NULL) {
            config_record *next = map->headers[i]->next;
            freeresponse(map->headers[i]);
            map->headers[i] = next;
        }
    }
}

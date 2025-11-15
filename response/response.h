#ifndef RESPONSE_H
#define RESPONSE_H


typedef struct response {
  char *header;
  response *next;
}response;

typedef struct {
    char *headers[256];
}response_map;

void response_insert(response_map *map, char *header);
char *response_lookup(response_map *map, const char *header);
void freeresponse_hash(response_map *map);

#endif

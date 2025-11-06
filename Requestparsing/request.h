#ifndef REQUEST_H
#define REQUEST_H

typedef struct request_record {
    char *header;
    struct request_record *next;
} request_record;

typedef struct {
    request_record *requests[256];
}request_hashmap;

void requests_insert(request_hashmap *map, request_record *request);
request_record *requests_lookup(request_hashmap *map, const char *header);

void freerequest(request_record* req);
#endif

#ifndef PARSECONFIG_H
#define PARSECONFIG_H


/*
    config record struct, implemented using a hashmap for efficient lookup

*/
typedef struct config_record {
    char *IP;
    char *host;
    char *ipv6host;
    struct config_record *next;
}config_record;



// Bundled up the hashmap configuration
typedef struct {
    config_record *configs[256];
}config_hashmap;

void configs_insert(config_hashmap *map, config_record *config);
config_record *configs_lookup(config_hashmap *map, const char *host);
void freeconfig_hash(config_hashmap *map);


config_hashmap* parseconfig(const char* file_path, int* out_count);

void freeconfig(config_record* req);
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../ErrorT.h"
#include "parseconfig.h"
unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = hash * 33 + c;
    return hash % 256;
}

void configs_insert(config_hashmap *map, config_record *config) {
    unsigned int index = hash(config->host);
    config->next = map->configs[index];
    map->configs[index] = config;
}

config_record* configs_lookup(config_hashmap *map, const char *host) {
    unsigned int index = hash(host);
    config_record *curr = map->configs[index];
    while (curr) {
        if (strstr(curr->host,host) != NULL)
            return curr;
        curr = curr->next;
    }
    return NULL;
} 

void freeconfig(config_record *config) {
    free(config->host);
    free(config->IP);
    free(config->ipv6host);
    free(config);
}

void freeconfighash(config_hashmap *map) {
    for(int i=0; i<256; i++) {
        while(map->configs[i] != NULL) {
            config_record *next = map->configs[i]->next;
            freeconfig(map->configs[i]);
            map->configs[i] = next;
        }
    }
}

config_hashmap *parseconfig(const char *file_path, int *out_count) {
    int buf_size = 1024;
    int count = 0;
    config_hashmap *map = calloc(1, sizeof(config_hashmap));  
    
    if (!map)
        ErrorT("can't alloc config map");
    
    FILE *file = fopen(file_path, "r");
    
    if (!file)
        ErrorT("can't open file");

    char* line = malloc(buf_size);
    config_record *config = NULL;

    if (!line)
        ErrorT("can't alloc line");    
    while(fgets(line, buf_size, file)) {
        if(isspace(line[0]) || line[0] == '#' || line[0] == '\n')
            continue;
        if(line[0] == ':' && config) {
            char *token1 = strtok(line, " \t\n");
            char *newline = token1 + 12;
            config->ipv6host = malloc(strlen(newline) + 1);
            config->ipv6host[strlen(newline)] = '\0';
            strcpy(config->ipv6host, newline);
            continue;
        }
        else
            config = calloc(1, sizeof(config_record));
        if (!config)
            ErrorT("can't alloc config");        
        // grabbing the IP to the respective configuration
        char *token = strtok(line, "\t\n");
        if (!token)
            continue;
        config->IP = malloc(12);
        if(!config->IP)
            ErrorT("can't alloc IP");

        strncpy(config->IP, token, 12);        
        config->IP[11] = '\0';
        
        //grabbing all domain names given to that IP in a line
        char *newline = token +12;

        if (!token) {
            fclose(file);
            ErrorT("file not properly configured");
        }
        config->host = malloc(strlen(newline)+1);
        if(!config->host)
            ErrorT("can't alloc host");
        strcpy(config->host, newline);
        configs_insert(map, config);
        count++;
    }
    fclose(file);
    free(line);
    *out_count = count;
    return map;
}

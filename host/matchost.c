#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../conf/parseconfig.h"
#include "../Requestparsing/request.h"
#include "../ErrorT.h"
#include "../host/matchost.h"
// Looks through the request_hashmap for the Host header and finds the configuration in the config_hasmap, if no matching host is found then we default to the main configuration.
// main configuration should be defined in startup, thus for the sake of defensive programming, our code will blow up if it isn't defined
config_record* matchost(config_hashmap *config_map, request_hashmap *request_map, config_record *main_configuration) {

    printf("sgima\n");fflush(stdout);
    request_record *req = requests_lookup(request_map, "Host:");
    if(!req)
        ErrorT("major error, didn't find host");
    char * host = req->header + strlen("Host: ");
    printf("bazinga\n");fflush(stdout);
    config_record *conf = configs_lookup(config_map, host);
    if(!(main_configuration))
        ErrorT("major error, main configuration not defined");
    
    if(conf) {
        conf->chosenhost = host;
        return conf;
    } 
        
    else
        return main_configuration;

    return NULL;
    
}

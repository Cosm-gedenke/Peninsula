#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parseconfig.h"

void defconfig(config_record * main_configuration) {
    //we assume we are doing DocumentRoot
    main_configuration->chosenhost = malloc(strlen("/var/www/html\0"));
    main_configuration->IP = malloc(strlen("127.0.0.1\0"));
    
    strcpy(main_configuration->chosenhost, "/var/www/html\0");
    strcpy(main_configuration->IP, "127.0.0.1\0");
}

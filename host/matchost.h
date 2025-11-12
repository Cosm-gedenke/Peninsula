#ifndef MATCHOST_H
#define MATCHOST_H

#include "../Requestparsing/request.h"
#include "../conf/parseconfig.h"

config_record *matchost(config_hashmap *config_map, request_hashmap *request_map, config_record *main_configuration);

#endif

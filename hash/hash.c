#include <stdio.h>
#include <stdlib.h>

unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = hash * 33 + c;
    return hash % 256;
}


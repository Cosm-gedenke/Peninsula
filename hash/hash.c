#include <stdio.h>
#include <stdlib.h>

unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    int i=5;
    while ((c = *str++) && (i>0)) {
        hash = hash * 33 + c;
        i--;
    }
    return hash % 256;
}


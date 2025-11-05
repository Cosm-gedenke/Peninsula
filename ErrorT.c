#include <stdio.h>
#include <stdlib.h>
#include "ErrorT.h"

void ErrorT(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

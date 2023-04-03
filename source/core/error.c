#include "error.h"

#include <stdlib.h>
#include <stdio.h>

void ThrowError( const char *error ) {
    printf( "%s\n", error );
    exit(-1);
}
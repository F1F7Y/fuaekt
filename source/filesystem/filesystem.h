#ifndef _FILESYSTEM
#define _FILESYSTEM

#include <stdio.h>

FILE *SafeOpenFile( const char *filename, const char *mode );

#endif // _FILESYSTEM
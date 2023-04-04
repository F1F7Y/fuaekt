#ifndef _FILESYSTEM
#define _FILESYSTEM

#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>

FILE *SafeOpenFile( const char *filename, const char *mode );

void Directory_IteratorStart( const char *path );
bool Directory_Iterate();
struct dirent *Directory_GetIteratorValue();


#endif // _FILESYSTEM
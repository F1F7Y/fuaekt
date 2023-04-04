#include "filesystem.h"

#include "core/error.h"

FILE *SafeOpenFile( const char *filename, const char *mode ) {
    FILE *pFile = fopen( filename, mode );

    if( !pFile )
        ThrowError( "Failed to open file!" );
    
    return pFile;
}

DIR *dir;

void Directory_IteratorStart( const char *path ) {
    dir = opendir( path );
}

struct dirent *ent;

bool Directory_Iterate() {
    if( dir == NULL )
        return false;
    
    ent = readdir( dir );

    if( ent == NULL ) {
        closedir( dir );
        return false;
    }
}

struct dirent *Directory_GetIteratorValue() {
    return ent;
}
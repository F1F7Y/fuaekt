#include "filesystem.h"

#include "core/error.h"

FILE *SafeOpenFile( const char *filename, const char *mode ) {
    FILE *pFile = fopen( filename, mode );

    if( !pFile )
        ThrowError( "Failed to open file!" );
    
    return pFile;
}
#include "map.h"

#include <string.h>

#include "filesystem/filesystem.h"


bool Map_DoesExist( const char *map ) {
    for( Directory_IteratorStart("maps/"); Directory_Iterate(); ) {
        struct dirent *ent = Directory_GetIteratorValue();
        if( strcmp( ent->d_name, map ) == 0 )
            return true;
    }

    return false;
}
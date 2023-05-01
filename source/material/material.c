#include "material.h"

#include <stdlib.h>
#include <stdio.h>
#include "core/logging.h"
#include "core/error.h"
#include "filesystem/filesystem.h"

Material_t errorMaterial;

NamedMaterial_t *loadedMaterials[128];

void Material_Init() {
    for( int i = 0; i < 128; i++ )
        loadedMaterials[i] = NULL;
}

void Material_ShutDown() {
    for( int i = 0; i < 128; i++ )
        if( loadedMaterials[i] )
            free(loadedMaterials[i]);
}

void Material_CreateErrorMaterial() {
    Log_Info( "Creating error material\n" );

    uint8_t buffer[256 * 256 * 4];
    for( int y = 0; y < 256; y++ ) {
        for( int x = 0; x < 256; x++ ) {
            uint8_t color[2][3] = { { 0x32, 0xBC, 0xC9 }, { 0xC9, 0x32, 0xBC } };

            int i = y < 128 && x <= 128 || y >= 128 && x > 128;

            buffer[(y * 256 + x) * 4 + 0] = color[0][i];
            buffer[(y * 256 + x) * 4 + 1] = color[1][i];
            buffer[(y * 256 + x) * 4 + 2] = color[2][i];
            buffer[(y * 256 + x) * 4 + 3] = 0xFF;
        }
    }

    errorMaterial.width = 256;
    errorMaterial.height = 256;

    glGenTextures( 1, &errorMaterial.texture );
    glBindTexture( GL_TEXTURE_2D, errorMaterial.texture );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);


    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, errorMaterial.width, errorMaterial.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer );
}

GLuint Material_GetErrorMaterial() {
    return errorMaterial.texture;
}

void Material_LoadMaterials() {
    for( Directory_IteratorStart("materials/"); Directory_Iterate(); ) {
        struct dirent *ent = Directory_GetIteratorValue();

        // Skip "." and ".."
        if( *ent->d_name == '.' )
            continue;
        
        int i = 0;
        for(; i < 128; i++)
        {
            if( !loadedMaterials[i] )
                break;
        }

        if( i == 128 )
            ThrowError( "Maximum number of materials is 128!" );
        
        Log_Info( "Loading material: %s to index %i\n", ent->d_name, i );

        char buffer[256] = {0};
        strcat(buffer, "materials/");
        strcat(buffer, ent->d_name);

        FILE *pFile = SafeOpenFile(buffer, "rb");
        DDSHeader_t header;
        fread( &header, sizeof(DDSHeader_t), 1, pFile);

        uint8_t imgBuffer[header.height * header.width * 4];
        fread(imgBuffer, sizeof(imgBuffer), 1, pFile);

        fclose(pFile);
        
        NamedMaterial_t *material = malloc(sizeof(NamedMaterial_t));
        strncpy(material->name, buffer, 256 );
        material->material.width = header.width;
        material->material.height = header.height;

        glGenTextures( 1, &material->material.texture );
        glBindTexture( GL_TEXTURE_2D, material->material.texture );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);


        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, material->material.width, material->material.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgBuffer );
        
        loadedMaterials[i] = material;
    }
}

GLuint Material_GetGLRef( const char *material ) {

    Log_Info( "Couldn't find %s, using error material instead!", material );
    return Material_GetErrorMaterial();
}
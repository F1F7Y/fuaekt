#include "material.h"

#include "core/logging.h"

Material_t errorMaterial;

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
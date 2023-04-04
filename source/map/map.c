#include "map.h"

#include <string.h>
#include <time.h>

#include "core/error.h"
#include "core/logging.h"
#include "filesystem/filesystem.h"
#include "material/shader.h"
#include "math.h"


bool Map_DoesExist( const char *map ) {
    for( Directory_IteratorStart("maps/"); Directory_Iterate(); ) {
        struct dirent *ent = Directory_GetIteratorValue();
        if( strcmp( ent->d_name, map ) == 0 )
            return true;
    }

    return false;
}

MapInfo_t g_pMapInfo;

typedef struct {
    Vector3f origin;
    Vector3f normal;
    Vector2f uv;
} GLVertex_t;

void Map_LoadMap( const char *map ) {
    Log_Info( "Loading map: \"%s\"\n", map );
    time_t tm = time(0);

    FILE *pMap = SafeOpenFile( map, "rb" );

    Header_t header;
    fread( &header, sizeof(header), 1, pMap);

    if( strncmp( "FMAP", header.ident, 4 ) != 0 )
        ThrowError( "Map has invalid ident!" );
    
    if( header.version != 1 )
        ThrowError( "Map has invalid version!" );

    Vector3f vertices[header.lumps[VERTICES].length/sizeof(Vector3f)];
    fseek( pMap, header.lumps[VERTICES].offset, SEEK_SET );
    fread( vertices, sizeof(Vector3f), header.lumps[VERTICES].length/sizeof(Vector3f), pMap );

    Vector3f normals[header.lumps[VERTEX_NORMALS].length/sizeof(Vector3f)];
    fseek( pMap, header.lumps[VERTEX_NORMALS].offset, SEEK_SET );
    fread( normals, sizeof(Vector3f), header.lumps[VERTEX_NORMALS].length/sizeof(Vector3f), pMap );

    RenderVertex_t renderVertices[header.lumps[RENDER_VERTICES].length/sizeof(RenderVertex_t)];
    fseek( pMap, header.lumps[RENDER_VERTICES].offset, SEEK_SET );
    fread( renderVertices, sizeof(RenderVertex_t), header.lumps[RENDER_VERTICES].length/sizeof(RenderVertex_t), pMap );
    
    // Build vertex array
    int numVertices = header.lumps[RENDER_VERTICES].length/sizeof(RenderVertex_t);
    GLVertex_t glVertices[numVertices];
    for( int i = 0; i < numVertices; i++ ) {
        glVertices[i].origin = vertices[renderVertices[i].vertexIdx];
        glVertices[i].normal = normals[renderVertices[i].normalIdx];
    }

    glGenBuffers( 1, &g_pMapInfo.vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, g_pMapInfo.vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLVertex_t ) * numVertices, &glVertices, GL_STATIC_DRAW );

    // 
    int16_t triangleIndices[header.lumps[RENDER_VERTICES].length/sizeof(int16_t)];
    fseek( pMap, header.lumps[RENDER_VERTICES].offset, SEEK_SET );
    fread( triangleIndices, sizeof(int16_t), header.lumps[RENDER_VERTICES].length/sizeof(int16_t), pMap );

    int numTriangles = header.lumps[RENDER_VERTICES].length/sizeof(int16_t);
    glGenBuffers( 1, &g_pMapInfo.indexBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_pMapInfo.indexBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(int16_t) * numTriangles, &triangleIndices, GL_STATIC_DRAW );

    glUseProgram( g_iShader );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( GLVertex_t ), (void*)offsetof( GLVertex_t, origin ) );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( GLVertex_t ), (void*)offsetof( GLVertex_t, normal ) );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( GLVertex_t ), (void*)offsetof( GLVertex_t, uv ) );
    glEnableVertexAttribArray( 2 );

    fclose( pMap );

    Log_Info( "Loading took: %i seconds\n", time(0) - tm );
}
#include "map.h"

#include <string.h>
#include <time.h>

#include "core/error.h"
#include "core/logging.h"
#include "entities/player.h"
#include "filesystem/filesystem.h"
#include "material/shader.h"
#include "utils/math.h"


bool Map_DoesExist( const char *map ) {
    for( Directory_IteratorStart("maps/"); Directory_Iterate(); ) {
        struct dirent *ent = Directory_GetIteratorValue();
        if( strcmp( ent->d_name, map ) == 0 )
            return true;
    }

    return false;
}

MapInfo_t g_mapInfo;

typedef struct {
    Vector3f origin;
    Vector3f normal;
    Vector2f uv;
} GLVertex_t;

void Map_LoadMap( const char *map ) {
    Log_Info( "Loading map: \"%s\"\n", map );
    time_t tm = time(0);

    if( g_mapInfo.meshes != 0 )
        Map_UnLoad();

    FILE *pMap = SafeOpenFile( map, "rb" );

    Header_t header;
    fread( &header, sizeof(header), 1, pMap);

    if( strncmp( "FMAP", header.ident, 4 ) != 0 )
        ThrowError( "Map has invalid ident!" );
    
    if( header.version != 1 )
        ThrowError( "Map has unsupported version!" );

    Vector3f vertices[header.lumps[VERTICES].length/sizeof(Vector3f)];
    fseek( pMap, header.lumps[VERTICES].offset, SEEK_SET );
    fread( vertices, sizeof(Vector3f), header.lumps[VERTICES].length/sizeof(Vector3f), pMap );

    Vector3f normals[header.lumps[VERTEX_NORMALS].length/sizeof(Vector3f)];
    fseek( pMap, header.lumps[VERTEX_NORMALS].offset, SEEK_SET );
    fread( normals, sizeof(Vector3f), header.lumps[VERTEX_NORMALS].length/sizeof(Vector3f), pMap );

    int numVertices = header.lumps[RENDER_VERTICES].length/sizeof(RenderVertex_t);
    RenderVertex_t renderVertices[numVertices];
    fseek( pMap, header.lumps[RENDER_VERTICES].offset, SEEK_SET );
    fread( renderVertices, sizeof(RenderVertex_t), numVertices, pMap );
    
    // Build vertex array
    GLVertex_t glVertices[numVertices];
    for( int i = 0; i < numVertices; i++ ) {
        glVertices[i].origin = vertices[renderVertices[i].vertexIdx];
        glVertices[i].normal = normals[renderVertices[i].normalIdx];
        glVertices[i].uv = renderVertices[i].uv;
    }

    int vertexBuffer;
    glGenBuffers( 1, &vertexBuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vertexBuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof( GLVertex_t ) * numVertices, glVertices, GL_STATIC_DRAW );

    // 
    int numTriangles = header.lumps[TRIANGLE_INDICES].length/sizeof(int16_t);
    int16_t triangleIndices[numTriangles];
    fseek( pMap, header.lumps[TRIANGLE_INDICES].offset, SEEK_SET );
    fread( triangleIndices, sizeof(int16_t), numTriangles, pMap );

    int indexBuffer;
    glGenBuffers( 1, &indexBuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, indexBuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(int16_t) * numTriangles, triangleIndices, GL_STATIC_DRAW );

    glUseProgram( g_iShader );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( GLVertex_t ), (void*)offsetof( GLVertex_t, origin ) );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( GLVertex_t ), (void*)offsetof( GLVertex_t, normal ) );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( GLVertex_t ), (void*)offsetof( GLVertex_t, uv ) );
    glEnableVertexAttribArray( 2 );

    int numMeshes = header.lumps[MESHES].length/sizeof(Mesh_t);
    Mesh_t meshes[numMeshes];
    fseek( pMap, header.lumps[MESHES].offset, SEEK_SET );
    fread( meshes, sizeof(Mesh_t), numMeshes, pMap );

    g_mapInfo.numMeshes = numMeshes;
    g_mapInfo.meshes = malloc( sizeof(Mesh_t) * numMeshes);
    memcpy( g_mapInfo.meshes, meshes, sizeof(Mesh_t) * numMeshes );

    fclose( pMap );

    Log_Info( "Map has: %i meshes\n", g_mapInfo.numMeshes );

    Log_Info( "Loading took: %i seconds\n", time(0) - tm );

    Vector3f zero; zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
    Player_Create( zero, zero, 50.0f );
}

void Map_UnLoad() {
    Log_Info( "Map Unload\n" );
    Player_Delete();
    free( g_mapInfo.meshes );
}
#ifndef _MAP
#define _MAP

#include <stdbool.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "structs.h"

typedef struct {
    int numMeshes;
    Mesh_t *meshes;
    int numBrushes;
    Brush_t *brushes;
    GLuint vertexBuffer;
    GLuint indexBuffer;
} MapInfo_t;

extern MapInfo_t g_mapInfo;

bool Map_DoesExist( const char *map );
void Map_LoadMap( const char *map );
void Map_UnLoad();

#endif // _MAP
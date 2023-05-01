#ifndef _MAP_STRUCTS
#define _MAP_STRUCTS

#include "utils/math.h"

#define UNUSED_0         0
#define PLANES           1
#define VERTICES         2
#define VERTEX_NORMALS   3
#define TEXTURE_NAMES    4
#define TEXTURE_DATAS    5
#define RENDER_VERTICES  6
#define TRIANGLE_INDICES 7
#define MESHES           8
#define PLANE_INDICES    9
#define BRUSHES          10
#define UNUSED_11        11
#define UNUSED_12        12
#define UNUSED_13        13
#define UNUSED_14        14
#define LIGHTS           15


typedef struct {
    int offset;
    int length;
} Lump_t;

typedef struct {
    char ident[4];
    int version;
    int mapRevision;
    int padding;

    Lump_t lumps[16];
} Header_t;

typedef struct {
    float a, b, c, d;
} Plane_t;

typedef struct {
    float x, y, z;
} Vertex_t;

typedef struct {
    float x, y, z;
} VertexNormal_t;

typedef struct {
    char path[256];
} TextureData_t;

typedef struct {
    int16_t vertexIdx;
    int16_t normalIdx;
    Vector2f uv;
} RenderVertex_t;

typedef struct {
    int16_t idx;
} TriangleIndex_t;

typedef struct {
    Vector3f mins;
    Vector3f maxs;
    uint16_t firstTri;
    uint16_t numTris;
    int32_t textureIdx;
} Mesh_t;

typedef struct {
    int16_t index;
} BrushPlaneIndex_t;

typedef struct {
    Vector3f mins;
    Vector3f maxs;
    int16_t firstPlaneIdx;
    int16_t numPlaneIdxs;
} Brush_t;

typedef struct {
    float origin[3];
    float colour[3];
    // int flags;
    // int direction;
} Light_t;

#endif // _MAP_STRUCTS
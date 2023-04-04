struct Lump_t {
    s32 offset;
    s32 length;
};

struct Header_t {
    char ident[4];
    s32 version;
    s32 revision;
    s32 pad;
    
    Lump_t lumps[16];
};

struct Plane3f { float a, b, c, d; };
struct Vector3f { float x, y, z; };

struct TextureData_t {
    s16 index;
};

struct RenderVertex_t {
    s16 vertexIdx;
    s16 normalIdx;
    float uv[2];
};

struct Mesh_t {
    float mins[3];
    float maxs[3];
    s16 firstTri;
    s16 numTris;
    s16 textureIdx;
};

struct Brush_t {
    float mins[3];
    float maxs[3];
    s16 firstPlaneIdx;
    s16 numPlaneIdxs;
};

struct Light_t {
    float origin[3];
    float colour[3];
    // int flags;
    // int direction;
};

////////////////////////////////

Header_t header @ 0;

// Unused
Plane3f planes[header.lumps[1].length/sizeof(Plane3f)] @ header.lumps[1].offset;
Vector3f vertices[header.lumps[2].length/sizeof(Vector3f)] @ header.lumps[2].offset;
Vector3f normals[header.lumps[3].length/sizeof(Vector3f)] @ header.lumps[3].offset;
char textures[header.lumps[4].length/sizeof(char)] @ header.lumps[4].offset;
s16 textureDatas[header.lumps[5].length/sizeof(s16)] @ header.lumps[5].offset;
RenderVertex_t renderVertices[header.lumps[6].length/sizeof(RenderVertex_t)] @ header.lumps[6].offset;
s16 triangleIndices[header.lumps[7].length/sizeof(s16)] @ header.lumps[7].offset;
Mesh_t meshes[header.lumps[8].length/sizeof(Mesh_t)] @ header.lumps[8].offset;
s16 planeIndices[header.lumps[9].length/sizeof(s16)] @ header.lumps[9].offset;
Brush_t brushes[header.lumps[10].length/sizeof(Brush_t)] @ header.lumps[10].offset;
// Unused
// Unsued
// Unused
// Unused
Light_t lights[header.lumps[15].length/sizeof(Light_t)] @ header.lumps[15].offset;














#ifndef _MATERIAL
#define _MATERIAL

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

typedef struct {
    GLuint texture;
    int width;
    int height;
} Material_t;

typedef struct {
    char name[256];
    Material_t material;
} NamedMaterial_t;

// DDS header
typedef struct {
    uint32_t size;
    uint32_t flags;
    char fourCC[4];
    uint32_t RGBBitCount;
    uint32_t RBitMask;
    uint32_t GBitMask;
    uint32_t BBitMask;
    uint32_t ABitMask;
} DDSPixelFormat_t;

typedef struct {
    char magic[4];
    uint32_t size;
    uint32_t flags;
    uint32_t height;
    uint32_t width;
    uint32_t pitchOrLinearSize;
    uint32_t depth;
    uint32_t mipMapCount;
    uint32_t reserved1[11];
    DDSPixelFormat_t ddspf;
    uint32_t caps;
    uint32_t caps2;
    uint32_t caps3;
    uint32_t caps4;
    uint32_t reserved2;
} DDSHeader_t;

void Material_Init();
void Material_ShutDown();

void Material_CreateErrorMaterial();
GLuint Material_GetErrorMaterial();
void Material_LoadMaterials();
GLuint Material_GetGLRef( const char *material );

#endif // _MATERIAL
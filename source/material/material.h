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

void Material_CreateErrorMaterial();
GLuint Material_GetErrorMaterial();
void Material_LoadMaterials();

#endif // _MATERIAL
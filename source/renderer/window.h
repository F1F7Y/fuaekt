#ifndef _WINDOW
#define _WINDOW

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

extern GLFWwindow *g_pWindow;

void Window_Create();
void Window_Close();

#endif // _WINDOW
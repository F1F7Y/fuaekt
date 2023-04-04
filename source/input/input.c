#include "input.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "renderer/window.h"

static void Input_KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods ) {
    Log_Info( "Key callback called!\n" );
}

void Input_Initilaze() {
    Log_Info( "Input handler initilazed!\n" );
    glfwSetKeyCallback( g_pWindow, Input_KeyCallback );
}
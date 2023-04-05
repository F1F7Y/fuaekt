#include "window.h"

#include "core/error.h"

GLFWwindow *g_pWindow = NULL;


void Window_Create() {
    g_pWindow = glfwCreateWindow( 1400, 800, "fuaekt", NULL, NULL );
    if( !g_pWindow ) {
        glfwTerminate();
        ThrowError( "Failed to create window!" );
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent( g_pWindow );
    glfwSwapInterval(0);
}

void Window_Close() {

}
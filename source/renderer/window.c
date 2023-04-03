#include "window.h"

#include "core/error.h"

GLFWwindow *g_pWindow = NULL;


void Window_Create() {
    g_pWindow = glfwCreateWindow(1400, 800, "fuaekt", NULL, NULL);
    if( !g_pWindow ) {
        glfwTerminate();
        ThrowError( "Failed to create window!" );
    }
}

void Window_Close() {

}
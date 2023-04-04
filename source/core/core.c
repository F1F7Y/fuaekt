#include "core.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/error.h"
#include "filesystem/filesystem.h"
#include "input/input.h"
#include "map/map.h"
#include "material/shader.h"
#include "renderer/renderer.h"
#include "renderer/window.h"

void Core_Initilaze() {
    Log_Info( "Initilazing core!\n" );

    if( !glfwInit() )
        ThrowError( "Failed to initilaze GLFW!" );

    Window_Create();
    Renderer_Initilaze();
    Input_Initilaze();

    Shader_LoadDefault();

    // Load first map
}

void Core_MainLoop() {
    while( !glfwWindowShouldClose( g_pWindow ) ) {
        glfwPollEvents();
    }
}

void Core_Shutdown() {
    Log_Info( "Shutting down core!\n" );

    glfwTerminate();
}
#include "core.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/error.h"
#include "material/shader.h"
#include "renderer/window.h"

void Core_Initilaze() {
    Log_Info( "Initilazing core!\n" );

    if( !glfwInit() )
        ThrowError( "Failed to initilaze GLFW!" );
    
    Window_Create();

    Shader_LoadDefault();
}

void Core_Shutdown() {
    Log_Info( "Shutting down core!\n" );

    glfwTerminate();
}
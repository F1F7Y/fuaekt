#include "renderer.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/error.h"
#include "core/logging.h"

void Renderer_Initilaze() {
    if( glewInit() != GLEW_OK ) {
        ThrowError( "Failed to initilaze GLEW!" );
    }

    Log_Info( "Renderer initilazed!\n" );
}
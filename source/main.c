#include <stdio.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/core.h"
#include "renderer/window.h"

int main( int argc, char *argv[] ) {
    Log_Info( "fuaekt\n" );

    Core_Initilaze();

    Core_MainLoop();

    Core_Shutdown();
    
    return 0;
}
#include "core.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/error.h"
#include "entities/player.h"
#include "filesystem/filesystem.h"
#include "input/input.h"
#include "map/map.h"
#include "material/material.h"
#include "material/shader.h"
#include "physics/physics.h"
#include "renderer/renderer.h"
#include "renderer/window.h"
#include "utils/math.h"

void Core_Initilaze() {
    Log_Info( "Initilazing core!\n" );

    if( !glfwInit() )
        ThrowError( "Failed to initilaze GLFW!" );

    Window_Create();
    Renderer_Initilaze();
    Input_Initilaze();
    Player_Initilaze();

    Material_Init();
    Material_CreateErrorMaterial();
    Material_LoadMaterials();
    Shader_LoadDefault();

    // Load first map
    Map_LoadMap( "maps/box.bsp" );
}

void Core_MainLoop() {
    const float fTargetDelta = 1.0f / 60.0f;
    float fLastDelta = fTargetDelta;
    float fFrameStart;
    while( !glfwWindowShouldClose( g_pWindow ) ) {
        fFrameStart = glfwGetTime();

        glfwPollEvents();

        Player_UpdateAngles( fLastDelta );
        Player_UpdateVelocity( fLastDelta );

        Physics_CheckPlayerAgainstMap( fLastDelta );

        Player_UpdateOrigin( fLastDelta );
        Player_UpdateViewMatrix( fLastDelta );

        Renderer_Render();

        glfwSwapBuffers(g_pWindow);

        while( glfwGetTime() - fFrameStart < fTargetDelta ) {}
        fLastDelta = glfwGetTime() - fFrameStart;
    }
}

void Core_Shutdown() {
    Log_Info( "Shutting down core!\n" );

    Map_UnLoad();
    Input_CleanUp();
    Material_ShutDown();

    glfwTerminate();
}
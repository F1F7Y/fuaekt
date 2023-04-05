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

    Shader_LoadDefault();
    Material_CreateErrorMaterial();

    Matrix_t *mat = Matrix_New(4, 4);
    Matrix_Perspective( mat );
    Matrix_Translate( mat, 600.0f, 200.0f, 1000.0f);
    printf("%f %f %f %f\n", mat->array[0], mat->array[1], mat->array[2], mat->array[3] );
    printf("%f %f %f %f\n", mat->array[4], mat->array[5], mat->array[6], mat->array[7] );
    printf("%f %f %f %f\n", mat->array[8], mat->array[9], mat->array[10], mat->array[11] );
    printf("%f %f %f %f\n", mat->array[12], mat->array[13], mat->array[14], mat->array[15] );
    free(mat);

    // Load first map
    Map_LoadMap( "maps/test.bsp" );
}

void Core_MainLoop() {
    const float fTargetDelta = 1.0f / 60.0f;
    float fLastDelta = fTargetDelta;
    float fFrameStart;
    while( !glfwWindowShouldClose( g_pWindow ) ) {
        fFrameStart = glfwGetTime();

        glfwPollEvents();

        Player_Update( fLastDelta );
        Player_UpdateViewMatrix();

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

    glfwTerminate();
}
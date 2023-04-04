#include "core.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/error.h"
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

    Shader_LoadDefault();
    Material_CreateErrorMaterial();

    // Matrix_t *mat = Matrix_New(4, 4);
    // Matrix_Perspective( mat );
    // Matrix_Translate( mat, 600.0f, 200.0f, 1000.0f);
    // printf("%f %f %f %f\n", mat->array[0], mat->array[1], mat->array[2], mat->array[3] );
    // printf("%f %f %f %f\n", mat->array[4], mat->array[5], mat->array[6], mat->array[7] );
    // printf("%f %f %f %f\n", mat->array[8], mat->array[9], mat->array[10], mat->array[11] );
    // printf("%f %f %f %f\n", mat->array[12], mat->array[13], mat->array[14], mat->array[15] );
    // free(mat);

    // Load first map
    Map_LoadMap( "maps/test.bsp" );
}

Matrix_t *mat;

void Core_MainLoop() {
    mat = Matrix_New( 4, 4 );
    Matrix_Perspective( mat );

    while( !glfwWindowShouldClose( g_pWindow ) ) {
        glfwPollEvents();

        int display_w, display_h;
        glfwGetFramebufferSize( g_pWindow, &display_w, &display_h );
        glViewport( 0, 0, display_w, display_h );
        
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glUseProgram( g_iShader );

        // float mat[16];
        // mat[0]  = 0.816085;
        // mat[1]  = 0.000000;
        // mat[2]  = 0.000000;
        // mat[3]  = 0.000000;
        // mat[4]  = 0.000000;
        // mat[5]  = 0.000000;
        // mat[6]  = 1.000000;
        // mat[7]  = 1.000000;
        // mat[8]  = 0.000000;
        // mat[9]  = 1.428148;
        // mat[10] = 0.000000;
        // mat[11] = 0.000000;
        // mat[12] = 0.000000;
        // mat[13] = 0.000000;
        // mat[14] = -0.20000;
        // mat[15] = 0.000000;

        unsigned int transLoc = glGetUniformLocation( g_iShader, "transform" );
        glUniformMatrix4fv( transLoc, 1, GL_FALSE, mat->array );

        // float matrix[4 * 4];

        for( int i = 0; i < g_mapInfo.numMeshes; i++ ) {
            Mesh_t mesh = g_mapInfo.meshes[i];
            // Log_Info( "%i\n", mesh.numTris);

            glActiveTexture(GL_TEXTURE0);
            unsigned int texLoc = glGetUniformLocation( g_iShader, "CurrentTexture" );
            glUniform1i( texLoc, 0 );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            glBindTexture( GL_TEXTURE_2D, Material_GetErrorMaterial() );


            glDrawElements( GL_TRIANGLES, mesh.numTris, GL_UNSIGNED_SHORT, (void*)(sizeof(int16_t) * mesh.firstTri ) );
        }

        glfwSwapBuffers(g_pWindow);
    }

    free( mat );
}

void Core_Shutdown() {
    Log_Info( "Shutting down core!\n" );

    Map_UnLoad();

    glfwTerminate();
}
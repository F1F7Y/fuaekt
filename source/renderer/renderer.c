#include "renderer.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/error.h"
#include "core/logging.h"
#include "entities/player.h"
#include "map/map.h"
#include "material/material.h"
#include "material/shader.h"
#include "renderer/window.h"

void Renderer_Initilaze() {
    if( glewInit() != GLEW_OK ) {
        ThrowError( "Failed to initilaze GLEW!" );
    }

    glEnable( GL_DEPTH_TEST );
    glCullFace( GL_FRONT );
    glEnable( GL_CULL_FACE );

    Log_Info( "Renderer initilazed!\n" );
}

void Renderer_Render() {
    int display_w, display_h;
    glfwGetFramebufferSize( g_pWindow, &display_w, &display_h );
    glViewport( 0, 0, display_w, display_h );
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUseProgram( g_iShader );

    unsigned int transLoc = glGetUniformLocation( g_iShader, "transform" );
    glUniformMatrix4fv( transLoc, 1, GL_FALSE, g_pPlayer->mat4->array );

    for( int i = 0; i < g_mapInfo.numMeshes; i++ ) {
        Mesh_t mesh = g_mapInfo.meshes[i];

        glActiveTexture(GL_TEXTURE0);
        unsigned int texLoc = glGetUniformLocation( g_iShader, "CurrentTexture" );
        glUniform1i( texLoc, 0 );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glBindTexture( GL_TEXTURE_2D, Material_GetErrorMaterial() );


        glDrawElements( GL_TRIANGLES, mesh.numTris, GL_UNSIGNED_SHORT, (void*)(sizeof(int16_t) * mesh.firstTri ) );
    }
}
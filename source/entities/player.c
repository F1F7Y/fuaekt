#include "player.h"

#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "input/input.h"

Player_t *g_pPlayer;

static void PlayerCallback_MoveForward_Start()  { if( g_pPlayer != NULL ) { g_pPlayer->iForward = 1; } }
static void PlayerCallback_MoveBackward_Start() { if( g_pPlayer != NULL ) { g_pPlayer->iBackward = 1; } }
static void PlayerCallback_MoveLeft_Start()     { if( g_pPlayer != NULL ) { g_pPlayer->iLeft = 1; } }
static void PlayerCallback_MoveRight_Start()    { if( g_pPlayer != NULL ) { g_pPlayer->iRight = 1; } }

static void PlayerCallback_MoveForward_End()  { if( g_pPlayer != NULL ) { g_pPlayer->iForward = 0; } }
static void PlayerCallback_MoveBackward_End() { if( g_pPlayer != NULL ) { g_pPlayer->iBackward = 0; } }
static void PlayerCallback_MoveLeft_End()     { if( g_pPlayer != NULL ) { g_pPlayer->iLeft = 0; } }
static void PlayerCallback_MoveRight_End()    { if( g_pPlayer != NULL ) { g_pPlayer->iRight = 0; } }

static void PlayerCallback_MoveJump()     {  }

void Player_Initilaze() {
    Log_Info( "Registering player key callbacks!\n" );

    Input_RegisterKeyCallback( GLFW_KEY_W, GLFW_PRESS, PlayerCallback_MoveForward_Start );
    Input_RegisterKeyCallback( GLFW_KEY_S, GLFW_PRESS, PlayerCallback_MoveBackward_Start );
    Input_RegisterKeyCallback( GLFW_KEY_A, GLFW_PRESS, PlayerCallback_MoveLeft_Start );
    Input_RegisterKeyCallback( GLFW_KEY_D, GLFW_PRESS, PlayerCallback_MoveRight_Start );

    Input_RegisterKeyCallback( GLFW_KEY_W, GLFW_RELEASE, PlayerCallback_MoveForward_End );
    Input_RegisterKeyCallback( GLFW_KEY_S, GLFW_RELEASE, PlayerCallback_MoveBackward_End );
    Input_RegisterKeyCallback( GLFW_KEY_A, GLFW_RELEASE, PlayerCallback_MoveLeft_End );
    Input_RegisterKeyCallback( GLFW_KEY_D, GLFW_RELEASE, PlayerCallback_MoveRight_End );

    Input_RegisterKeyCallback( GLFW_KEY_SPACE, GLFW_PRESS, PlayerCallback_MoveJump );
}

void Player_Create( Vector3f origin, Vector3f angles, float radius ) {
    g_pPlayer = malloc( sizeof(Player_t) );
    g_pPlayer->v3Origin = origin;
    g_pPlayer->v3Angles = angles;
    g_pPlayer->fRadius = radius;
    g_pPlayer->mat4 = Matrix_New( 4, 4 );

    g_pPlayer->iForward = 0;
    g_pPlayer->iBackward = 0;
    g_pPlayer->iLeft = 0;
    g_pPlayer->iRight = 0;
    g_pPlayer->fSpeed = 300.0f;
}

void Player_Update( float delta ) {
    if( !g_pPlayer )
        return;

    g_pPlayer->v3Origin.z += delta * g_pPlayer->fSpeed * ( g_pPlayer->iForward - g_pPlayer->iBackward );
    g_pPlayer->v3Origin.x += delta * g_pPlayer->fSpeed * ( g_pPlayer->iLeft - g_pPlayer->iRight );

    // Log_Info( "%f\n", g_pPlayer->v3Origin.z );
}

void Player_UpdateViewMatrix() {
    if( !g_pPlayer )
        return;

    Matrix_Perspective( g_pPlayer->mat4 );
    Matrix_Translate( g_pPlayer->mat4, g_pPlayer->v3Origin.x, g_pPlayer->v3Origin.y, g_pPlayer->v3Origin.z );
}

void Player_Delete() {
    free(g_pPlayer->mat4);
    free(g_pPlayer);
}
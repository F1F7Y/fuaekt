#include "player.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "input/input.h"
#include "renderer/window.h"
#include "utils/math.h"

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
    // g_pPlayer->mat4 = Matrix_New( 4, 4 );

    g_pPlayer->iForward = 0;
    g_pPlayer->iBackward = 0;
    g_pPlayer->iLeft = 0;
    g_pPlayer->iRight = 0;
    g_pPlayer->fSpeed = 300.0f;
}

void Player_Update( float delta ) {
    if( !g_pPlayer )
        return;

    // Update rotation
    static bool ignore = true;
    if( Input_IsMouseCaptured() ) {
        static double dXPos, dYPos;
        double xPos, yPos;
        glfwGetCursorPos( g_pWindow, &xPos, &yPos);

        dXPos = dXPos - xPos;
        dYPos = dYPos - yPos;

        if( !ignore ) {
            g_pPlayer->v3Angles.x += dXPos;
            g_pPlayer->v3Angles.y -= dYPos;

            g_pPlayer->v3Angles.y = g_pPlayer->v3Angles.y > 0.0f ? 0.0f : g_pPlayer->v3Angles.y;
            g_pPlayer->v3Angles.y = g_pPlayer->v3Angles.y < -180.0f ? -180.0f : g_pPlayer->v3Angles.y;
        }

        ignore = false;

        dXPos = xPos;
        dYPos = yPos;
    } else {
        ignore = true;
    }

    // Update position
    float sf = sin( DegToRad( g_pPlayer->v3Angles.x + 90.0f) );
    float cf = cos( DegToRad( g_pPlayer->v3Angles.x + 90.0f) );

    float ss = sin( DegToRad( g_pPlayer->v3Angles.x ) );
    float cs = cos( DegToRad( g_pPlayer->v3Angles.x ) );
    
    g_pPlayer->v3Origin.y += delta * g_pPlayer->fSpeed * ( g_pPlayer->iBackward - g_pPlayer->iForward ) * sf;
    g_pPlayer->v3Origin.x += delta * g_pPlayer->fSpeed * ( g_pPlayer->iBackward - g_pPlayer->iForward ) * cf;
    
    g_pPlayer->v3Origin.y += delta * g_pPlayer->fSpeed * ( g_pPlayer->iLeft - g_pPlayer->iRight ) * ss;
    g_pPlayer->v3Origin.x += delta * g_pPlayer->fSpeed * ( g_pPlayer->iLeft - g_pPlayer->iRight ) * cs;
}

void Player_UpdateViewMatrix() {
    if( !g_pPlayer )
        return;

    Matrix_Perspective( g_pPlayer->m4ViewMatrix );

    Matrix_Rotate( g_pPlayer->m4ViewMatrix, DegToRad( g_pPlayer->v3Angles.y ), Vector3f_New( 1.0f, 0.0f, 0.0f ) );
    Matrix_Rotate( g_pPlayer->m4ViewMatrix, DegToRad( -g_pPlayer->v3Angles.x ), Vector3f_New( 0.0f, 0.0f, 1.0f ) );


    Matrix_Translate( g_pPlayer->m4ViewMatrix, g_pPlayer->v3Origin.x, g_pPlayer->v3Origin.y, g_pPlayer->v3Origin.z );
}

void Player_Delete() {
    free(g_pPlayer);
}
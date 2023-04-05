#include "input.h"

#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "renderer/window.h"

struct KeyCallbackEntry_t{
    int key;
    int action;
    KeyCallback callback;
    struct KeyCallbackEntry_t *pNext;
};

struct KeyCallbackEntry_t *g_pCallbacks;

bool bMouseCaptured = false;

static void Input_KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods ) {
    // Log_Info( "Key callback called!\n" );

    struct KeyCallbackEntry_t *entry = g_pCallbacks;
    while( entry != NULL ) {
        if( key != entry->key ) {
            entry = entry->pNext;
            continue;
        }
        
        if( action != entry->action ) {
            entry = entry->pNext;
            continue;
        }
        
        entry->callback();

        entry = entry->pNext;
    }
}


static void InputCallback_ToggleMouseCapture() {
    if( bMouseCaptured )
        glfwSetInputMode( g_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
    else
        glfwSetInputMode( g_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    bMouseCaptured = !bMouseCaptured;
}

void Input_Initilaze() {
    Log_Info( "Input handler initilazed!\n" );
    glfwSetKeyCallback( g_pWindow, Input_KeyCallback );

    Input_RegisterKeyCallback( GLFW_KEY_ESCAPE, GLFW_PRESS, InputCallback_ToggleMouseCapture );
}

void Input_RegisterKeyCallback( int key, int action, KeyCallback callback ) {
    struct KeyCallbackEntry_t *entry = malloc( sizeof(struct KeyCallbackEntry_t) );
    entry->key = key;
    entry->action = action;
    entry->callback = callback;
    entry->pNext = NULL;

    if( g_pCallbacks == NULL ) {
        g_pCallbacks = entry;
        return;
    }

    struct KeyCallbackEntry_t *walker = g_pCallbacks;
    while( walker->pNext != NULL ) { walker = walker->pNext; }

    walker->pNext = entry;
}

void Input_CleanUp() {
    if( !g_pCallbacks )
        return;

    struct KeyCallbackEntry_t *current = g_pCallbacks;
    struct KeyCallbackEntry_t *next = current->pNext;
    
    while( true ) {
        free( current );

        if( !next )
            return;
        
        current = next;
        next = current->pNext;
    }
}

bool Input_IsMouseCaptured() {
    return bMouseCaptured;
}
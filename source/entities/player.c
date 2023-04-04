#include "player.h"

#include <stdlib.h>

Player_t *g_pPlayer;

void Player_Initilaze() {

}

void Player_Create( Vector3f origin, Vector3f angles, float radius ) {
    g_pPlayer = malloc( sizeof(Player_t) );
    g_pPlayer->v3Origin = origin;
    g_pPlayer->v3Angles = angles;
    g_pPlayer->fRadius = radius;
    g_pPlayer->mat4 = Matrix_New( 4, 4 );
}

void Player_Update() {
    Matrix_Perspective( g_pPlayer->mat4 );
    Matrix_Translate( g_pPlayer->mat4, g_pPlayer->v3Origin );
}

void Player_Delete() {
    free(g_pPlayer->mat4);
    free(g_pPlayer);
}
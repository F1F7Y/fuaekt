#ifndef _PLAYER
#define _PLAYER

#include "utils/math.h"

typedef struct {
    // Globals
    Vector3f v3Origin;
    Vector3f v3Angles;

    // Input
    int iForward, iBackward, iLeft, iRight;
    float fSpeed;

    // Private
    Vector3f v3CameraOffset;
    Matrix_t *mat4;

    // Collider
    float fRadius;
} Player_t;

extern Player_t *g_pPlayer;

void Player_Initilaze();
void Player_Create( Vector3f origin, Vector3f angles, float radius );
void Player_Update( float delta );
void Player_UpdateViewMatrix();
void Player_Delete();

#endif // _PLAYER
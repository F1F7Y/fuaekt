#ifndef _PLAYER
#define _PLAYER

#include "utils/math.h"

typedef struct {
    // Globals
    Vector3f v3Origin;
    Vector3f v3Angles;
    Vector3f v3Velocity;

    // Input
    int iForward, iBackward, iLeft, iRight;
    float fSpeed;

    // Private
    Vector3f v3CameraOffset;
    Matrix4_t m4ViewMatrix;

    // Collider
    float fRadius;
} Player_t;

extern Player_t *g_pPlayer;

void Player_Initilaze();
void Player_Create( Vector3f origin, Vector3f angles, float radius );
void Player_UpdateAngles( float delta );
void Player_UpdateVelocity( float delta );
void Player_UpdateOrigin( float delta );
void Player_UpdateViewMatrix( float delta );
void Player_Delete();

#endif // _PLAYER
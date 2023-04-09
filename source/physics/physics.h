#ifndef _PHYSICS
#define _PHYSICS

#include <stdbool.h>
#include "utils/math.h"

typedef struct {
    Vector3f v3Origin;
    Vector3f v3Velocity;
    float    fRadius;
} Collider_Sphere_t;

typedef struct {
    Vector3f v3Mins;
    Vector3f v3Maxs;
    Vector3f v3Velocity;
} Collider_AABB_t;

void Physics_CheckPlayerAgainstMap();
bool Physics_CheckSphereAABB( Collider_Sphere_t *sphere, Collider_AABB_t *aabb );


#endif // _PHYSICS
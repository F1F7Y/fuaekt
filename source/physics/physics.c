#include "physics.h"

#include <math.h>

#include "core/logging.h"
#include "entities/player.h"
#include "map/map.h"

void Physics_CheckPlayerAgainstMap( float fDelta ) {
    if( g_pPlayer == NULL )
        return;
    
    // Stores our origin next frame if we dont modify our velocity
    Vector3f v3NextOrigin = Vector3f_Add( g_pPlayer->v3Origin, Vector3f_MultFloat( g_pPlayer->v3Velocity, fDelta ) );

    // Check against every brush
    for( int i = 0; i < g_mapInfo.numBrushes; i++ ) {
        Brush_t brush = g_mapInfo.brushes[i];

        // Check brush AABB
        Vector3f v3ClosestPoint;
        v3ClosestPoint.x = MAX( brush.mins.x, MIN( v3NextOrigin.x, brush.maxs.x ) );
        v3ClosestPoint.y = MAX( brush.mins.y, MIN( v3NextOrigin.y, brush.maxs.y ) );
        v3ClosestPoint.z = MAX( brush.mins.z, MIN( v3NextOrigin.z, brush.maxs.z ) );

        float distance = Vector3f_Distance( v3NextOrigin, v3ClosestPoint );
        if( distance < g_pPlayer->fRadius ) {
            // At this point we are in close proximity to this brush
            int iInside = 0;
            Plane_t touchingPlane = {0};
            float touchingDistance = 100.0f;

            // Loop through all the planes and store the one we're the most likely to collide with
            for( int idx = brush.firstPlaneIdx; idx < brush.firstPlaneIdx + brush.numPlaneIdxs; idx++ ) {
                Plane_t plane = g_mapInfo.planes[idx];
                Vector3f v3Normal = Vector3f_New( plane.a, plane.b, plane.c );

                // Calculate distance to plane
                float fNextResult = plane.a * v3NextOrigin.x + plane.b * v3NextOrigin.y + plane.c * v3NextOrigin.z - plane.d;
                // Log_Info( "%f\n", fNextResult );
                if( fNextResult > 0.0f ) {
                    Vector3f v3Point = Vector3f_Add( g_pPlayer->v3Origin, Vector3f_MultFloat( g_pPlayer->v3Velocity, fDelta ) );
                    v3Point = Vector3f_Add( v3Point, Vector3f_MultFloat( v3Normal, -1.0f * g_pPlayer->fRadius ) );
                    float fResult = plane.a * v3Point.x + plane.b * v3Point.y + plane.c * v3Point.z - plane.d;
                    iInside++;

                    // We're too close to plane
                    if( fResult < 0.0f) {
                        touchingPlane = plane;
                    }
                }
            }

            // We're colliding with a plane
            if( iInside == 1 ) {
                Vector3f v3Normal = Vector3f_New( touchingPlane.a, touchingPlane.b, touchingPlane.c );
                v3Normal.x = fabs( v3Normal.x );
                v3Normal.y = fabs( v3Normal.y );
                v3Normal.z = fabs( v3Normal.z );

                Vector3f v3Impulse = Vector3f_New( v3Normal.x * g_pPlayer->v3Velocity.x, v3Normal.y * g_pPlayer->v3Velocity.y, v3Normal.z * g_pPlayer->v3Velocity.z );
                g_pPlayer->v3Velocity = Vector3f_Add( g_pPlayer->v3Velocity, Vector3f_MultFloat( v3Impulse, -1.0f ) );
            }
        }
    }


    // Friction
    g_pPlayer->v3Velocity.x *= 0.97f;
    g_pPlayer->v3Velocity.y *= 0.97f;
}
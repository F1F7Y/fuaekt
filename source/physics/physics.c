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
    Vector3f v3VelocityNormal = Vector3f_Normalize( g_pPlayer->v3Velocity );

    // Check against every brush
    for( int i = 0; i < g_mapInfo.numBrushes; i++ ) {
        Brush_t brush = g_mapInfo.brushes[i];

        // Check if the player is within g_pPlayer->fRadius of a brush AABB
        Vector3f v3ClosestPointToAABB;
        v3ClosestPointToAABB.x = MAX( brush.mins.x, MIN( v3NextOrigin.x, brush.maxs.x ) );
        v3ClosestPointToAABB.y = MAX( brush.mins.y, MIN( v3NextOrigin.y, brush.maxs.y ) );
        v3ClosestPointToAABB.z = MAX( brush.mins.z, MIN( v3NextOrigin.z, brush.maxs.z ) );

        float fAABBDistance = Vector3f_Distance( v3NextOrigin, v3ClosestPointToAABB );
        if( fAABBDistance < g_pPlayer->fRadius ) {
            // Stores closest plane used for collision
            float fClosestPlane = g_pPlayer->fRadius * 2.0f;
            Plane_t ClosestPlane = {0};

            // Check if we're going to be inside the brush
            bool bIsInside = true;
            for( int idx = brush.firstPlaneIdx; idx < brush.firstPlaneIdx + brush.numPlaneIdxs; idx++ ) {
                Plane_t plane = g_mapInfo.planes[idx];

                Vector3f v3PlaneNormal = Vector3f_New( plane.a, plane.b, plane.c );
                Vector3f v3ClosestPointToPlane = Vector3f_Add( v3NextOrigin, Vector3f_MultFloat( v3PlaneNormal, -1.0f * g_pPlayer->fRadius ) );
                float fPlaneDistance = plane.a * v3ClosestPointToPlane.x + plane.b * v3ClosestPointToPlane.y + plane.c * v3ClosestPointToPlane.z - plane.d;
                
                // If we're in the positives for at least on plane we're
                // outside the brush
                if( fPlaneDistance > 0.0f ) {
                    bIsInside = false;
                }

                // Check closest plane
                if( fabs( fPlaneDistance ) <  fClosestPlane && !FloatCompare( fabs( fPlaneDistance ), 0.0f ) ) {
                    fClosestPlane = fabs( fPlaneDistance );
                    ClosestPlane = plane;
                }
            }

            // If bIsInside is true we're colliding, update the velocity
            if( bIsInside ) {
                Vector3f v3Normal = Vector3f_New( ClosestPlane.a, ClosestPlane.b, ClosestPlane.c );
                Vector3f v3Impulse = Vector3f_MultFloat( v3Normal, -1.0f * Vector3f_Dot( v3Normal, g_pPlayer->v3Velocity ) );
                g_pPlayer->v3Velocity = Vector3f_Add( v3Impulse, g_pPlayer->v3Velocity );
            }
        }
    }

    // Friction
    g_pPlayer->v3Velocity.x *= 0.97f;
    g_pPlayer->v3Velocity.y *= 0.97f;
}
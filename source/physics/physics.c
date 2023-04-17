#include "physics.h"

#include <math.h>

#include "core/logging.h"
#include "entities/player.h"
#include "map/map.h"

void Physics_CheckPlayerAgainstMap( float fDelta ) {
    if( g_pPlayer == NULL )
        return;

    // TODO: Check if next pos + radius is going to be inside brush, if it is we're colliding
    // TODO: If we're colliding get the closest plane to origin + velocity * radius, use that 
    
    // Stores our origin next frame if we dont modify our velocity
    Vector3f v3NextOrigin = Vector3f_Add( g_pPlayer->v3Origin, Vector3f_MultFloat( g_pPlayer->v3Velocity, fDelta ) );
    Vector3f v3VelocityNormal = Vector3f_Normalize( g_pPlayer->v3Velocity );
    Vector3f v3NextOriginRadius = Vector3f_Add( v3NextOrigin, Vector3f_MultFloat( v3VelocityNormal, g_pPlayer->fRadius ) );

    // Check against every brush
    for( int i = 0; i < g_mapInfo.numBrushes; i++ ) {
        Brush_t brush = g_mapInfo.brushes[i];

        // Check if the player is within g_pPlayer->fRadius of a brush
        Vector3f v3ClosestPoint;
        v3ClosestPoint.x = MAX( brush.mins.x, MIN( v3NextOrigin.x, brush.maxs.x ) );
        v3ClosestPoint.y = MAX( brush.mins.y, MIN( v3NextOrigin.y, brush.maxs.y ) );
        v3ClosestPoint.z = MAX( brush.mins.z, MIN( v3NextOrigin.z, brush.maxs.z ) );

        float fAABBDistance = Vector3f_Distance( v3NextOrigin, v3ClosestPoint );
        if( fAABBDistance < g_pPlayer->fRadius ) {
            //Log_Info( "Colliding with AABB %i\n", i );
            float fClosestPlane = g_pPlayer->fRadius * 2.0f;
            Plane_t ClosestPlane = {0};
            bool bIsInside = true;
            for( int idx = brush.firstPlaneIdx; idx < brush.firstPlaneIdx + brush.numPlaneIdxs; idx++ ) {
                Plane_t plane = g_mapInfo.planes[idx];
                Vector3f v3PlaneNormal = Vector3f_New( plane.a, plane.b, plane.c );
                Vector3f v3Test = Vector3f_Add( v3NextOrigin, Vector3f_MultFloat( v3PlaneNormal, -1.0f * g_pPlayer->fRadius ) );
                // TODO: Test Player distance from each plane
                float fNextResult = plane.a * v3Test.x + plane.b * v3Test.y + plane.c * v3Test.z - plane.d;
                Log_Info( "%f\n", fNextResult );
                if( fNextResult > 0.0f ) {
                    bIsInside = false;
                }

                if( fabs( fNextResult ) <  fClosestPlane && !FloatCompare( fabs( fNextResult ), 0.0f ) ) {
                    fClosestPlane = fabs( fNextResult );
                    ClosestPlane = plane;
                }
            }
            Log_Info("-------\n");
            if( bIsInside ) {
                Vector3f v3Normal = Vector3f_New( ClosestPlane.a, ClosestPlane.b, ClosestPlane.c );
                v3Normal.x = fabs( v3Normal.x );
                v3Normal.y = fabs( v3Normal.y );
                v3Normal.z = fabs( v3Normal.z );

                Vector3f v3Impulse = Vector3f_New( v3Normal.x * g_pPlayer->v3Velocity.x, v3Normal.y * g_pPlayer->v3Velocity.y, v3Normal.z * g_pPlayer->v3Velocity.z );
                g_pPlayer->v3Velocity = Vector3f_Add( g_pPlayer->v3Velocity, Vector3f_MultFloat( v3Impulse, -1.0f ) );
                // g_pPlayer->v3Velocity = Vector3f_New( 0.0f, 0.0f, 0.0f );
            }
        }
    }


    // Friction
    g_pPlayer->v3Velocity.x *= 0.97f;
    g_pPlayer->v3Velocity.y *= 0.97f;
}
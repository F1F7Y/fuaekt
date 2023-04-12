#include "physics.h"

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

        Vector3f v3ClosestPoint;
        v3ClosestPoint.x = MAX( brush.mins.x, MIN( v3NextOrigin.x, brush.maxs.x ) );
        v3ClosestPoint.y = MAX( brush.mins.y, MIN( v3NextOrigin.y, brush.maxs.y ) );
        v3ClosestPoint.z = MAX( brush.mins.z, MIN( v3NextOrigin.z, brush.maxs.z ) );

        float distance = Vector3f_Distance( v3NextOrigin, v3ClosestPoint );
        
        if( distance < g_pPlayer->fRadius ) {
            // Log_Info( "%f\n", distance );
            g_pPlayer->v3Velocity.x = 0.0f;
            g_pPlayer->v3Velocity.y = 0.0f;
            g_pPlayer->v3Velocity.z = 0.0f;
            // break;
        }
    }
}
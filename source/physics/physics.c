#include "physics.h"

#include "core/logging.h"
#include "entities/player.h"
#include "map/map.h"

void Physics_CheckPlayerAgainstMap() {
    if( g_pPlayer == NULL )
        return;
    
    // Construct player collider
    Collider_Sphere_t player;
    player.v3Origin   = g_pPlayer->v3Origin;
    player.v3Velocity = g_pPlayer->v3Velocity;
    player.fRadius    = g_pPlayer->fRadius;

    player.v3Origin.x += player.v3Velocity.x;
    player.v3Origin.y += player.v3Velocity.y;
    player.v3Origin.z += player.v3Velocity.z;

    Log_Info( "%f %f %f\n", player.v3Origin.x, player.v3Origin.y, player.v3Origin.z );

    // Check against every brush
    for( int i = 0; i < g_mapInfo.numBrushes; i++ ) {
        Brush_t brush = g_mapInfo.brushes[i];

        float x, y, z;
        x = MAX( brush.mins.x, MIN( player.v3Origin.x, brush.maxs.x));
        y = MAX( brush.mins.y, MIN( player.v3Origin.y, brush.maxs.y));
        z = MAX( brush.mins.z, MIN( player.v3Origin.z, brush.maxs.z));

        float distance = Vector3f_Distance( player.v3Origin, Vector3f_New( x, y, z ) );
        // Log_Info( "%f\n", distance );
        
        if( distance < player.fRadius ) {
            // Log_Info( "%f\n", distance );
            g_pPlayer->v3Velocity.x = 0.0f;
            g_pPlayer->v3Velocity.y = 0.0f;
            g_pPlayer->v3Velocity.z = 0.0f;
            // break;
        }
    }
}

bool Physics_CheckSphereAABB( Collider_Sphere_t *sphere, Collider_AABB_t *aabb ) {

}
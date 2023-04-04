#include "math.h"

#include <stdlib.h>
#include <math.h>

Matrix_t *Matrix_New( int w, int h ) {
    Matrix_t *mat = malloc( sizeof(Matrix_t) );
    mat->array = malloc( sizeof(float) * w * h );
    mat->width = w;
    mat->height = h;

    for( int i = 0; i < w; i++ ) {
        for( int j = 0; j < h; j++ ) {
            mat->array[i * h + j] = 0.0f;
        }
    }

    return mat;
}

void Matrix_Set( Matrix_t *mat, int x, int y, float value ) {
    // if( mat != NULL || x > mat->width || y > mat->height )
    //     return;
    
    mat->array[mat->width * y + x] = value;
}

void Matrix_Add( Matrix_t *mat, int x, int y, float value ) {
    if( mat == NULL || x > mat->width || y > mat->height )
        return;
    
    mat->array[mat->width * y + x] += value;
}

void Matrix_Perspective( Matrix_t *mat ) {
    if( mat == NULL || mat->width != 4 && mat->height != 4 )
        return;
    
    float fov = ( 70.0f / 180.0f ) * 3.141592f;
    float ratio = 1400.0f / 800.0f; // 1.75
    float near = 0.1f;
    float far = 1000000.0f;

    float tan_half_fov = tan(fov/2);
    Matrix_Set( mat, 0, 0, ( 1 / ( ratio * tan_half_fov ) ) / 2 );
    Matrix_Set( mat, 2, 1, 1 );
    Matrix_Set( mat, 3, 1, 1 );
    Matrix_Set( mat, 1, 2, 1 / tan_half_fov );
    // Matrix_Set( mat, 2, 2, -(far + near) / (far - near) );
    Matrix_Set( mat, 2, 3, -(2 * far * near) / (far - near) );
}

void Matrix_Translate( Matrix_t *mat, float x, float y, float z ) {
    Matrix_Add( mat, 0, 3, x * mat->array[0] );
    Matrix_Add( mat, 1, 3, y * mat->array[9] );
    Matrix_Add( mat, 3, 3, -z );
    Matrix_Add( mat, 2, 3, -z );
}
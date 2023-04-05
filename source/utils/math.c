#include "math.h"

#include <stdlib.h>
#include <math.h>

#define PI 3.141592653

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

float Matrix_At( Matrix_t *mat, int x, int y ) {
    return mat->array[mat->width * y + x];
}

void Matrix_Perspective( Matrix_t *mat ) {
    if( mat == NULL || mat->width != 4 && mat->height != 4 )
        return;
    
    for( int i = 0; i < 16; i++ )
        mat->array[i] = 0.0f;
    
    float fov = ( 70.0f / 180.0f ) * PI;
    float ratio = 1400.0f / 800.0f; // 1.75
    float near = 0.1f;
    float far = 1000000.0f;

    float tan_half_fov = tan(fov/2);
    Matrix_Set( mat, 0, 0, 1.0f / ( ratio * tan_half_fov ) );
    Matrix_Set( mat, 1, 1, 1.0f / tan_half_fov );
    Matrix_Set( mat, 2, 2, (far + near) / (near - far) );
    Matrix_Set( mat, 2, 3, -1.0f );
    Matrix_Set( mat, 3, 2, (2.0f * far * near) / (near - far) );
}

// 0 4 8 12
// 1 5 9 13
// 2 6 10 14
// 3 7 11 15
void Matrix_Translate( Matrix_t *mat, float x, float y, float z ) {
    // R[3][0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0]
    // R[3][1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1]
    // R[3][2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2]
    // R[3][3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3]
    Matrix_Set( mat, 3, 0, Matrix_At( mat, 0, 0 ) * x + Matrix_At( mat, 1, 0 ) * y + Matrix_At( mat, 2, 0 ) * z + Matrix_At( mat, 3, 0 ) );
    Matrix_Set( mat, 3, 1, Matrix_At( mat, 0, 1 ) * x + Matrix_At( mat, 1, 1 ) * y + Matrix_At( mat, 2, 1 ) * z + Matrix_At( mat, 3, 1 ) );
    Matrix_Set( mat, 3, 2, Matrix_At( mat, 0, 2 ) * x + Matrix_At( mat, 1, 2 ) * y + Matrix_At( mat, 2, 2 ) * z + Matrix_At( mat, 3, 2 ) );
    Matrix_Set( mat, 3, 3, Matrix_At( mat, 0, 3 ) * x + Matrix_At( mat, 1, 3 ) * y + Matrix_At( mat, 2, 3 ) * z + Matrix_At( mat, 3, 3 ) );
}
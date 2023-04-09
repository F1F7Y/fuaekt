#include "math.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653
#define EPSILON 0.0001f


float DegToRad( float deg ) {
    return ( deg / 180.0f ) * PI;
}

bool FloatCompare( float i, float j ) {
    return fabs(i - j) < EPSILON;
}

Vector3f Vector3f_New( float x, float y, float z ) {
    Vector3f vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}


void Matrix_Zero( Matrix4_t mat ) {
    memset( mat, 0, sizeof(float) * 4 * 4 );
}
void Matrix_Perspective( Matrix4_t mat ) {
    Matrix_Zero( mat );
    
    float fov = DegToRad( 70.0f );
    float ratio = 1400.0f / 800.0f; // 1.75
    float near = 0.1f;
    float far = 1000000.0f;

    float tan_half_fov = tan(fov/2);
    mat[0][0] = 1.0f / ( ratio * tan_half_fov );
    mat[1][1] = 1.0f / tan_half_fov;
    mat[2][2] = (far + near) / (near - far);
    mat[2][3] = -1.0f;
    mat[3][2] = (2.0f * far * near) / (near - far);
}

// 0 4 8 12
// 1 5 9 13
// 2 6 10 14
// 3 7 11 15
void Matrix_Translate( Matrix4_t mat, float x, float y, float z ) {
    mat[3][0] = mat[0][0] * x + mat[1][0] * y + mat[2][0] * z + mat[3][0];
    mat[3][1] = mat[0][1] * x + mat[1][1] * y + mat[2][1] * z + mat[3][1];
    mat[3][2] = mat[0][2] * x + mat[1][2] * y + mat[2][2] * z + mat[3][2];
    mat[3][3] = mat[0][3] * x + mat[1][3] * y + mat[2][3] * z + mat[3][3];
}

void Matrix_Rotate( Matrix4_t mat, float angle, Vector3f vec ) {
    // Create rotated matrix
    Matrix4_t rmat;
    float sx, sy, sz, cx, cy, cz;

    sx = sin(vec.x * angle);
    sy = sin(vec.y * angle);
    sz = sin(vec.z * angle);

    cx = cos(vec.x * angle);
    cy = cos(vec.y * angle);
    cz = cos(vec.z * angle);

    rmat[0][0] =  cy * cz;
    rmat[0][1] =  cz * sx * sy + cx * sz;
    rmat[0][2] = -cx * cz * sy + sx * sz;
    rmat[1][0] = -cy * sz;
    rmat[1][1] =  cx * cz - sx * sy * sz;
    rmat[1][2] =  cz * sx + cx * sy * sz;
    rmat[2][0] =  sy;
    rmat[2][1] = -cy * sx;
    rmat[2][2] =  cx * cy;
    rmat[0][3] =  0.0f;
    rmat[1][3] =  0.0f;
    rmat[2][3] =  0.0f;
    rmat[3][0] =  0.0f;
    rmat[3][1] =  0.0f;
    rmat[3][2] =  0.0f;
    rmat[3][3] =  1.0f;


    // Multiply passed matrix with the rotated one
    Matrix4_t cmat;
    memcpy( cmat, mat, sizeof( float ) * 16 );

    Matrix_Mult( cmat, rmat, mat );
}


void Matrix_Mult( Matrix4_t matA, Matrix4_t matB, Matrix4_t dest ) {
    dest[0][0] = matA[0][0] * matB[0][0] + matA[1][0] * matB[0][1] + matA[2][0] * matB[0][2] + matA[3][0] * matB[0][3];
    dest[0][1] = matA[0][1] * matB[0][0] + matA[1][1] * matB[0][1] + matA[2][1] * matB[0][2] + matA[3][1] * matB[0][3];
    dest[0][2] = matA[0][2] * matB[0][0] + matA[1][2] * matB[0][1] + matA[2][2] * matB[0][2] + matA[3][2] * matB[0][3];
    dest[0][3] = matA[0][3] * matB[0][0] + matA[1][3] * matB[0][1] + matA[2][3] * matB[0][2] + matA[3][3] * matB[0][3];

    dest[1][0] = matA[0][0] * matB[1][0] + matA[1][0] * matB[1][1] + matA[2][0] * matB[1][2] + matA[3][0] * matB[1][3];
    dest[1][1] = matA[0][1] * matB[1][0] + matA[1][1] * matB[1][1] + matA[2][1] * matB[1][2] + matA[3][1] * matB[1][3];
    dest[1][2] = matA[0][2] * matB[1][0] + matA[1][2] * matB[1][1] + matA[2][2] * matB[1][2] + matA[3][2] * matB[1][3];
    dest[1][3] = matA[0][3] * matB[1][0] + matA[1][3] * matB[1][1] + matA[2][3] * matB[1][2] + matA[3][3] * matB[1][3];

    dest[2][0] = matA[0][0] * matB[2][0] + matA[1][0] * matB[2][1] + matA[2][0] * matB[2][2] + matA[3][0] * matB[2][3];
    dest[2][1] = matA[0][1] * matB[2][0] + matA[1][1] * matB[2][1] + matA[2][1] * matB[2][2] + matA[3][1] * matB[2][3];
    dest[2][2] = matA[0][2] * matB[2][0] + matA[1][2] * matB[2][1] + matA[2][2] * matB[2][2] + matA[3][2] * matB[2][3];
    dest[2][3] = matA[0][3] * matB[2][0] + matA[1][3] * matB[2][1] + matA[2][3] * matB[2][2] + matA[3][3] * matB[2][3];

    dest[3][0] = matA[0][0] * matB[3][0] + matA[1][0] * matB[3][1] + matA[2][0] * matB[3][2] + matA[3][0] * matB[3][3];
    dest[3][1] = matA[0][1] * matB[3][0] + matA[1][1] * matB[3][1] + matA[2][1] * matB[3][2] + matA[3][1] * matB[3][3];
    dest[3][2] = matA[0][2] * matB[3][0] + matA[1][2] * matB[3][1] + matA[2][2] * matB[3][2] + matA[3][2] * matB[3][3];
    dest[3][3] = matA[0][3] * matB[3][0] + matA[1][3] * matB[3][1] + matA[2][3] * matB[3][2] + matA[3][3] * matB[3][3];
}
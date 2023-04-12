#ifndef _MATH
#define _MATH

#include <stdbool.h>


#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))


typedef struct {
    float x, y, z;
} Vector3f;

typedef struct {
    float x, y;
} Vector2f;


typedef float Matrix4_t[4][4];

float DegToRad( float deg );

bool FloatCompare( float i, float j );

Vector3f Vector3f_New(float x, float y, float z);
Vector3f Vector3f_Add( Vector3f vecA, Vector3f vecB );
Vector3f Vector3f_MultFloat( Vector3f vec, float f );
float Vector3f_Distance( Vector3f a, Vector3f b );

void Matrix_Zero( Matrix4_t mat );
void Matrix_Perspective( Matrix4_t mat );
void Matrix_Translate( Matrix4_t mat, float x, float y, float z );
void Matrix_Rotate( Matrix4_t mat, float angle, Vector3f vec );
void Matrix_Mult( Matrix4_t matA, Matrix4_t matB, Matrix4_t dest );
#endif // _MATH
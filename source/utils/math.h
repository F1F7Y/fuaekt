#ifndef _MATH
#define _MATH

typedef struct {
    float x, y, z;
} Vector3f;

typedef struct {
    float x, y;
} Vector2f;

typedef struct {
    float *array;
    int width;
    int height;
} Matrix_t;

Matrix_t *Matrix_New( int w, int h );
void Matrix_Set( Matrix_t *mat, int x, int y, float value );
void Matrix_Add( Matrix_t *mat, int x, int y, float value );
void Matrix_Perspective( Matrix_t *mat );
void Matrix_Translate( Matrix_t *mat, float x, float y, float z );
#endif // _MATH
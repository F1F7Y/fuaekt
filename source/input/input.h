#ifndef _INPUT
#define _INPUT

#include <stdbool.h>

typedef void (*KeyCallback)();

void Input_Initilaze();
void Input_RegisterKeyCallback( int key, int action, KeyCallback callback );
void Input_CleanUp();
bool Input_IsMouseCaptured();

#endif // _INPUT
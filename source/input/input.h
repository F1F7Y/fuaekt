#ifndef _INPUT
#define _INPUT

typedef void (*KeyCallback)();

void Input_Initilaze();
void Input_RegisterKeyCallback( int key, int action, KeyCallback callback );
void Input_CleanUp();

#endif // _INPUT


#ifndef CX_GAME_UTILS_1892CC387418E0EF092AB370D0F0418234182374812348FD0A2D123C83
#define CX_GAME_UTILS_1892CC387418E0EF092AB370D0F0418234182374812348FD0A2D123C83


#include <windows.h>		// added for DEVC++ Portable
#include <math.h> // for the camera and other
#include <stdio.h> // 
#include "cx_camera.h"
// #include "logprn.h"

/** shows all the parameters of the camera */
int PrintCoords(cxCam* pCam, HDC hdc);		


/** shows the parameters of the command device... */
int PrintParams(float fds, float fdq, float fdt, float fdf, float fdh, float Pow, HDC hdc);		

/** prints a welcome message before the game starts */
int PrintWelcomeW(HDC hdc, LPCWSTR wszMsg);			




#endif//CX_GAME_UTILS_1892CC387418E0EF092AB370D0F0418234182374812348FD0A2D123C83

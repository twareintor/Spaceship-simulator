
/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
// copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" 

/****************************************************************************************************/


#include <Windows.h>

#include <tchar.h>
#include <stdio.h>
#include <hidsdi.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))
#define WC_MAINFRAME	TEXT("MainFrame")
#define MAX_BUTTONS		16
#define CHECK(exp)		{ if(!(exp)) goto Error; }
#define SAFE_FREE(p)	{ if(p) { HeapFree(hHeap, 0, p); (p) = NULL; } }

//
// Global variables
//


typedef struct _cxJoyStk
{
	BOOL bButtonStates[MAX_BUTTONS];
	LONG lAxisX;
	LONG lAxisY;
	LONG lAxisZ;
	LONG lAxisRz;
	LONG lHat;
	INT  g_NumberOfButtons;
} CxJoyStk, cxJoyStk;


void ParseRawInput(PRAWINPUT pRawInput, CxJoyStk* pJoX);

int PrintJoystickCoords(CxJoyStk* pJoX, HDC hdc);






































/****************************************************************************************************/


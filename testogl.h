
/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// testogl.h /////
#ifndef TESTOGL_H_192839818238812381289384281
#define TESTOGL_H_192839818238812381289384281
// Modified for Code::Blocks // 
// Actually running in Orwell-DevC++ portable with MinGW // compiler: TDM-GCC 4.8.1 32-bit Release
#include <windows.h>		// added for DEVC++ Portable
#include <time.h>       	/* time for random */
// 
// #include <stdlib.h>
// #include <cstdio>
// #include <math.h> // for the camera and other
// #include <sstream>

// #define GLFW_INCLUDE_GLCOREARB			// ??
// #include <gl/glcorearb.h>			// Which library??? be careful!!!!!!! 
// #include <GL/glfw3.h> 		// 
// #define GLEW_STATIC			//
// #include <GL/glew.h>		//
// #ifndef GL_GLEXT_PROTOTYPES
// #define GL_GLEXT_PROTOTYPES
// #endif
#include <gl/gl.h>			// original 001
#include <gl/glu.h>			// original 001
// #include <gl/wglext.h>		// 
// #include <gl/glaux.h> 		// introducing, special for a terrain tutorial from NeHe 
// #include <gl/glext.h>		// is documented???		// reincluded...

#include "opengl.h"
#include "resource.h"
#include "cx_camera.h"			// for the "camera" structure
// my headers:
#include "loadTextures.h"

#include "logprn.h"
#include "celestial_objects.h"
#include "terrestrial_objects.h"
#include "test_triangles.h"
// printing something in the HDC:
#include "cx_game_utils.h"

/** special types for game development e.g. vectors */
#include "cxtypes.h"

/** include constants as the last include */

#include "constants.h"
//
//
// Functions

void Redraw(HDC hdc, BOOL bLight, CxCam* pCam, float* params);         // // // function as original
void Initializations(float fFovy, float fWidth, float fHeight); // performs initializations in a separate function
void Finalizaitions();		// perform finalizations in all of them

//
#endif//TESTOGL_H_192839818238812381289384281
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////












/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
// copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" 

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4

// #include "globals.h"

#include "testogl.h"
#include "triangles.h"

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4
float 	g_fAng;					// no more in use! no more in use! no more in use!

HBITMAP		g_hBmp[24];						// handles to global bitmap images...

float XUP[3] = {1,0,0}, XUN[3] = {-1, 0, 0},
      YUP[3] = {0,1,0}, YUN[3] = { 0,-1, 0},
      ZUP[3] = {0,0,1}, ZUN[3] = { 0, 0,-1},
      ORG[3] = {0,0,0};

GLfloat viewangle = 0, tippangle = 0, vertangle = 0, traj[120][3];

GLfloat d[3] = {0.1, 0.1, 0.1};
GLfloat fL[] = {0.0, 0.0, 1.0, 25.0};
GLfloat fA[] = {0.0, 0.0, 0.0};
GLfloat fMovL = 1;

GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;

GLfloat zoomF = 1.0f;

GLboolean   booExit = false;

VEC3 pos, rad;

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4


//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4

void Redraw(HDC hdc, BOOL bLight, CxCam* pCam, float* params)
{
	// main function that draws all
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();
	gluLookAt(pCam->x, pCam->y, pCam->z, pCam->x0, pCam->y0, pCam->z0, pCam->xv, pCam->yv, pCam->zv);
	// // // // // // // Begin of: Drawing objects:
    // Triad ();
	TheSky(pCam);
	// RenderTriangles();			// BUG: Assertion fault message from MinGW!!! (pfnGlGenBuffers() unusual way)
	// TheSea();
	glEnable(GL_LIGHT0);
	// TheStar(pCam);				// shows the sun on the sky// long distance simulated by moving with the camera..
	TheStar2(pCam);
    ThePlanet(pCam, params[0]);				// shows the planet, relative to position of the cam, simulating a very long distance...
    TheAsteroid(pCam, 0, pos, rad);			// 
	/**************** begin of terrestrial objects: **************************/
	// DrawCubes(8, 240);			// cubes		// CUBURI> Rows, Units // it was just for testing
	// StreetLights(60, 8.0);		// lighting spheres // pairs, distance between
	// TheHall();				
	// CeilLightsOnHall();		
	// RestrictCamOnTheHall(pCam);
	// Scari(15);
	// Punte();
	/**************** ~~end of terrestrial objects: **************************/
	
	glDisable(GL_LIGHT0);
	// // // // // // //   End of: Drawing objects
	SwapBuffers(hdc);
}

void Initializations(float fFovy, float fWidth, float fHeight)
{
	// 
	glClearColor(0.0, 0.0, 0.0, 0.0);			// in space
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 16.0/9.0, 0.1, 10120.0);
	glMatrixMode(GL_MODELVIEW);
	// 
	srand(time(NULL)); pos.x = (float)(rand()%400);
	srand(time(NULL)); pos.y = (float)(rand()%400);
	srand(time(NULL)); pos.z = (float)(rand()%100);
	srand(time(NULL)); rad.x = (float)(rand()%100);
	// 
}

void Finalizaitions()
{
	// MessageBoxW(NULL, L"Finalization", L"Program terminated", MB_OK);
}

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4


//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
// ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//   ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
// ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
//   ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
// ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||  ||
////\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





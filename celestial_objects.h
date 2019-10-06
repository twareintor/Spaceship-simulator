/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
// "celestial_objects.h"
// 	The Sun, The Stars, The Moon, The Earth as well and The Celestial Sphere (The Sky)
//		all using "gluQuadric"

// copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CX_CELESTIAL_OBJECTS_013209013209013209013209013209013209013209013209013209
#define CX_CELESTIAL_OBJECTS_013209013209013209013209013209013209013209013209013209


#include <windows.h>		// added for DEVC++ Portable
// 
#include <gl/gl.h>			// original 001
#include <gl/glu.h>			// original 001 // for quadrics
#include "opengl.h"
extern "C"{
#include "stbi.h"
}
#include "loadTextures.h"
#include "cx_camera.h"			// for the "camera" structure
#include "cxtypes.h"			// vectors, arrays and other user defined types
#include "rawSphere.h"			// for random object for asteroids

/** Shoots the star in the sky: quadric, sphere */
void TheStar(cxCam* pCam);		
		
/** Shoots the star in the sky: simple (transparent) billboard */
void TheStar2(cxCam* pCam);		// shows the star on the sky;		

/** Skydome texture skydome with stars, galaxy, interstellar clouds etc. */
void TheSky(cxCam* pCam);		

/** The planet: */
void ThePlanet(cxCam* pCam, float theta);	// // // // 

/** draws a satellite around the planet */
void TheSatellite(cxCam* pCam, float theta, float theta2); // a satelite around the planet ???

/** drawing asteroid(s) on our way: */
void TheAsteroid(cxCam* pCam, float theta, VEC3 pos, VEC3 rad);
















#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



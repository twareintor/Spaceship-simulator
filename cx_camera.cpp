/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
////////////////////////////////////////////////////// cx_camera.cpp //////////////////////////////////////////////////////////////////////

#include <math.h>
#include "cx_camera.h"
#include "constants.h"


int MoveIt(cxCam* pCam, float fds, float fdv, float fdw)		// note that fdy and fdz are optional!!!
{	// TO BE OPTIMIZED // TO BE OPTIMIZED // TO BE OPTIMIZED // or to conglomerate with TurnIt()
	// moves the camera forward (or backward, if fdx is negative) its direction
	float R = (float)sqrt((pCam->x0-pCam->x)*(pCam->x0-pCam->x)+(pCam->x0-pCam->x)*(pCam->x0-pCam->x)+(pCam->x0-pCam->x)*(pCam->x0-pCam->x));
	// float R = 2.0;		// reserve for optimization
	float x = (pCam->x0-pCam->x)/R;			// the calculated components of the orientation vector
	float y = (pCam->y0-pCam->y)/R;
	float z = (pCam->z0-pCam->z)/R;
	pCam->x+=fds*x;		// increment with the x-component of "fds"
	pCam->y+=fds*y;		// increment with the y-component of "fds"
	pCam->z+=fds*z;		// increment with the z-component of "fds"
	pCam->x0+=fds*x;	// increment with the x-component of "fds"
	pCam->y0+=fds*y;	// increment with the y-component of "fds"
	pCam->z0+=fds*z;	// increment with the z-component of "fds"
	// now the displacement up-down and left-right:
	// guess the components of the normal vector (in fact, they are stored in the pCam structure)
	float u = pCam->xv;
	float v = pCam->yv;
	float w = pCam->zv;
	// define the components of the yaw vector: // in fact, the rotation with 90 degrees of the normal vector about the direction vector	
	float r = x;	// will be calculated accrodingly...
	float s = y;
	float t = z;
	RotateVector(-PI/2, u, v, w, &r, &s, &t);
	// now we have the whole triad of the camera, let's position it left-right and up-down
	pCam->x+=fdv*r+fdw*u;
	pCam->y+=fdv*s+fdw*v;
	pCam->z+=fdv*t+fdw*w;
	pCam->x0+=fdv*r+fdw*u;
	pCam->y0+=fdv*s+fdw*v;
	pCam->z0+=fdv*t+fdw*w;
	return 0;		// return success	
}


int TurnIt(cxCam* pCam, float fdt, float fdf, float fdh)	// TO BE OPTIMIZED	// TO BE OPTIMIZED // TO BE OPTIMIZED
{	// NOTE: for optimization, is possible to conglomerate this function with MoveIt() 
	//				as a lot of computing operation are repeated here and there
	// NOTE: the view (turn) vector and the normal (pitch) vector are stored in the "cxCam" structure;
	// 		the yaw vector is to be calculated by every function call!
	float R = (float)sqrt((pCam->x0-pCam->x)*(pCam->x0-pCam->x)+(pCam->y0-pCam->y)*(pCam->y0-pCam->y)+(pCam->z0-pCam->z)*(pCam->z0-pCam->z));
	// float R = 2.0;		// reserve for optimization
	// use the components of the normal vector: fdt (delta-theta) rotates about this vector
	// guess the components of the orientation vector:
	float x = (pCam->x0-pCam->x)/R;			// the calculated components of the orientation vector
	float y = (pCam->y0-pCam->y)/R;
	float z = (pCam->z0-pCam->z)/R;
	// guess the components of the normal vector (in fact, they are stored in the pCam structure)
	float u = pCam->xv;
	float v = pCam->yv;
	float w = pCam->zv;
	// define the components of the yaw vector: // in fact, the rotation with 90 degrees of the normal vector about the direction vector	
	float r = x;	// will be calculated accrodingly...
	float s = y;
	float t = z;
	RotateVector(-PI/2, u, v, w, &r, &s, &t);
	// at this point, we have all three vectors in order to pitch, yaw or roll the camera, the normal vector remains unchanged...
	// first pitch the camera (turn it about the normal vector) // it works!!!!!
	RotateVector(fdt, u, v, w, &x, &y, &z);
	RotateVector(fdt, u, v, w, &r, &s, &t);
	pCam->x0 = pCam->x+R*x;
	pCam->y0 = pCam->y+R*y;
	pCam->z0 = pCam->z+R*z;
	// rotate (elevate) now the orientation and the normal vector about the yaw vector, the yaw vector remains unchanged...
	x = (pCam->x0-pCam->x)/R;			// the calculated components of the orientation vector
	y = (pCam->y0-pCam->y)/R;
	z = (pCam->z0-pCam->z)/R;
	u = pCam->xv;
	v = pCam->yv;
	w = pCam->zv;
	RotateVector(fdf, r, s, t, &x, &y, &z);
	RotateVector(fdf, r, s, t, &u, &v, &w);
	pCam->x0 = pCam->x+R*x;
	pCam->y0 = pCam->y+R*y;
	pCam->z0 = pCam->z+R*z;
	pCam->xv = u;
	pCam->yv = v;
	pCam->zv = w;
	// now the camera is turned about the yaw vector...
	// Turn the camera (rotate about the view vector) now// first the normal then guess the yaw vector again:
	RotateVector(fdh, x, y, z, &u, &v, &w);
	// the yaw vector is at this point no needed anymore..., update the camera parameters from the calculated  vectors:
	pCam->x0 = pCam->x+R*x;
	pCam->y0 = pCam->y+R*y;
	pCam->z0 = pCam->z+R*z;
	pCam->xv = u;
	pCam->yv = v;
	pCam->zv = w;
	return 0;		// return success
}


int RotateVector(float fdt, float u, float v, float w, float* px, float* py, float* pz)
{	
	// !!!!!!!!!!!!!!!!!!!!! better use quaternion class
	// fdt = the angle of rotation in RAD
	// u, v, v = the coordinates of the UNIT vector ABOUT to rotate
	// *px, *py, *pz = the coordinates of the UNIT vector TO BE rotated
	float x = *px;
	float y = *py;
	float z = *pz;
	float xt = u*(u*x+v*y+w*z)*(1-cos(fdt))+x*cos(fdt)+(-w*y+v*z)*sin(fdt);
	float yt = v*(u*x+v*y+w*z)*(1-cos(fdt))+y*cos(fdt)+(+w*x-u*z)*sin(fdt);
	float zt = w*(u*x+v*y+w*z)*(1-cos(fdt))+z*cos(fdt)+(-v*x+u*y)*sin(fdt);
	*px = xt;
	*py = yt;
	*pz = zt;
	
	return 0;
}

int RotateIt(cxCam* pCam, float fdt, float fdf)		// will be replaced!!!
{	// this rotates the camera (only) around the point of view (around the camera position)
	
	return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

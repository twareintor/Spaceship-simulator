/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
/////////////////////////////////////////// cx_camera.h ////////////////////////////////////////////////////////////

#ifndef CX_CAMERA_H_1892A37CEE5B412FF389D0041283947189234123
#define CX_CAMERA_H_1892A37CEE5B412FF389D0041283947189234123



// Structures
typedef struct __CxCam
{
	float	x;		// x, y, z of the eye position
	float	y;
	float	z;
	float	x0;		// x, y, z of the origin position
	float	y0;
	float	z0;
	float	xv;		// x, y, z of the normal vector
	float	yv;
	float	zv;	
	
}CxCam, cxCam;		// camera coordinates, 

/** moves the camera forward (or backward, if fds is negative) its direction */
int MoveIt(cxCam* pCam, float fds, float fdv=0.0, float fdw=0.0);	

/** yawns, pitch or rolls the camera about the observation point */
int TurnIt(cxCam* pCam, float fdt, float fdf, float fdh); 

/** roatates the camera in horizontal plane fth and vertica plane ffi */
int RotateIt(cxCam* pCam, float fdt, float fdf);	

//** */
int RotateVector(float fdt, float u, float v, float w, float* px, float* py, float* pz);











#endif//CX_CAMERA_H_1892A37CEE5B412FF389D0041283947189234123


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

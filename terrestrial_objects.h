
/////////////////////////////////// terrestrial_objects.h ////////////////////////////////////////////////////////////////////////

#include "loadTextures.h"	// already includes the <gl/gl.h> but not the <gl/glu.h>
#include <gl/glu.h>			// included after the <gl/gl.h> always!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "cx_camera.h"		// my "camera" view 


/** NOTE: Everything here is just for testing during development */

/** draw cubes from triangles using DrawElements() */
void DrawCubes(int nRows, int nUnits);		

/** lighting spheres imitating street lights */
void StreetLights(int nPairs, float fDist);			

/** spheres lighting on the ceil */
void CeilLightsOnHall();	

/** draws seawater */
void TheSea();			

/** the same as TheSea()... */
void TheSea2();			

/**  a hallway  */
void TheHall();		

/** another hallway */
void NewHall();

/** stairs */
void Scari(int nTrepte);		// Deseneaza scari// draws the steps

/** deck */
void Punte();					// Deseneaza puntea// draws the deck

/** a very raw collision response animator */ 
void RestrictCamOnTheHall(cxCam* pCam);
















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


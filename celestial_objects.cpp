

/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// "celestial_objects.cpp" / 
// 	The Sun, The Stars, The Moon, The Earth as well and The Celestial Sphere (The Sky)
//		all using "gluQuadric"

// copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" 

#include "celestial_objects.h"

void TheStar(cxCam* pCam)		// shows the star on the sky
{
	float fLight[] = {-800.0f, +3000.0f, +300.0f, +0.0f};
	float fColor[] = {+1.0f, +0.9f, +0.7f, +1.0f};
	
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, fColor);
	// glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, fLight); // GL_SPOT_CUTOFF
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, fLight); // GL_SPOT_CUTOFF
	
	glPushMatrix();	
	glTranslatef(pCam->x+fLight[0], pCam->y+fLight[1], pCam->z+fLight[2]);
	GLUquadric*	pqdrBall = gluNewQuadric();		// a quadric required
	if(pqdrBall)
	{
		gluQuadricNormals(pqdrBall, GLU_SMOOTH);
		gluSphere(pqdrBall, 220.1, 24, 24);
	}
	glPopMatrix();
}

void TheStar2(cxCam* pCam) // shows the star on the sky; this time as billboard only
{
	// no need for it when included in the skydome texture........	
	float fLight[] = {-800.0f, +3000.0f, +300.0f, +0.0f};
	float fColor[] = {+1.0f, +0.9f, +0.7f, +1.0f};
	
	// glEnable(GL_LIGHTING); // for no lighting ...
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fColor);
	glLightfv(GL_LIGHT0, GL_POSITION, fLight);		// GL_DIFFUSE
	
	glPushMatrix();	
	glTranslatef(pCam->x+fLight[0], pCam->y+fLight[1], pCam->z+fLight[2]);
	// roate also?? must be!
	glScalef(0.5f, 0.5f, 0.5f);
	GLfloat fVerts[] = {
					-1000.00f,  +0000.00f, -1000.00f,
					+1000.00f,  +0000.00f, -1000.00f,
					+1000.00f,  +0000.00f, +1000.00f,
					-1000.00f,  +0000.00f, +1000.00f,
						};
	GLuint	nIndex[] = {0, 1, 2, 0, 2, 3};
	GLfloat fTexCo[] = {0, 0,	0, 1,	1, 1,	1, 0};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	LoadJpegTexture(112);
	glVertexPointer(3, GL_FLOAT, 0, fVerts);
	glTexCoordPointer(2, GL_FLOAT, 0, fTexCo); 					
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nIndex);
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);	
	 // 
	glPopMatrix();
	// glDisable(GL_LIGHT0); // don't disable here!!
    // glDisable(GL_LIGHTING);
}

void ThePlanet(cxCam* pCam, float theta)
{
	UINT			iBuf;
	GLUquadric*		pqABall;
	GLUquadric*		pqAtm;
	
	const float diameter = 1600.0f;
	glPushMatrix();	
	glTranslatef(pCam->x+4000.0f, pCam->y-900.0f, pCam->z+0.0f);
	glRotatef(theta, 0.f, 0.f, 1.f);
	glEnable(GL_LIGHTING);
	pqABall = gluNewQuadric();			// a quadric required
	if(pqABall)
	{
		glEnable(GL_TEXTURE_2D);
		LoadBitmapTexture(19);
		gluQuadricTexture(pqABall, 1);
		gluQuadricNormals(pqABall, GLU_SMOOTH);
		gluSphere(pqABall, diameter, 40, 40);
		glDisable(GL_TEXTURE_2D);
		gluDeleteQuadric(pqABall);
	}
	glDisable(GL_LIGHTING);		
	/******************************* Atmosphere *******
	pqAtm = gluNewQuadric();			// a quadric required
	if(pqAtm)
	{
	   	glColor4f(0.9f, 0.6f, 0.6f, 0.03f);
	   	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	   	glEnable(GL_BLEND);
	   	gluQuadricDrawStyle(pqAtm, GLU_FILL);		
		gluQuadricNormals(pqAtm, GLU_SILHOUETTE);
		for(int i=0; i<1; i++) // just a single layer this time...
		{
			gluSphere(pqAtm, diameter*1.07f+4.0f*(i+1), 40, 80);
		}				
		glDisable(GL_BLEND);
	}
	gluDeleteQuadric(pqAtm);
	******************************* Atmosphere *******/
	glPopMatrix();
}

void TheSky(cxCam* pCam)	// draws the sky as a big textured sphere with the center in the point of view
{
	GLUquadric*		pqABall = gluNewQuadric();
	// float 			skytex[] = {0, 0,   0, 2,   2, 2,   2, 0};
	
	glPushMatrix();
	glTranslatef(pCam->x, pCam->y, pCam->z);
	if(pqABall)
	{
		// glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_TEXTURE_2D);
		LoadBitmapTexture(11);					// 17 / the universe...
		gluQuadricTexture(pqABall, 1);
		// glTexCoordPointer(2, GL_FLOAT, 0, skytex);
		gluQuadricNormals(pqABall, GLU_SMOOTH);	
		gluSphere(pqABall, 5000.0f, 40, 40);
		glDisable(GL_TEXTURE_2D);
		// glDisable(GL_TEXTURE_COORD_ARRAY);
		gluDeleteQuadric(pqABall);
	}	
	glPopMatrix();
	
}


void TheAsteroid(cxCam* pCam, float theta, VEC3 pos, VEC3 rad)
{
	// draws an asteroid: we need a lot of them!!!
	GLUquadric*		pqAnAsteroid = gluNewQuadric();
	if(pqAnAsteroid)
	{
		glEnable(GL_LIGHTING);
		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glEnable(GL_TEXTURE_2D);
		LoadBitmapTexture(20);
		gluQuadricTexture(pqAnAsteroid, 1);
		gluQuadricNormals(pqAnAsteroid, GLU_SMOOTH);
		gluSphere(pqAnAsteroid, (GLdouble)rad.x, 10, 10);
		glDisable(GL_TEXTURE_2D);
		gluDeleteQuadric(pqAnAsteroid);
		glPopMatrix();
		glDisable(GL_LIGHTING);
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



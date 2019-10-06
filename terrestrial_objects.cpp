
///////////////////////////////////////////// terrestrial_objects.cpp /////////////////////////////////////////////////////////


#include "terrestrial_objects.h"


void DrawCubes(int nRows, int nUnits)		// cubes
{    //
    GLfloat     vertices[] =
    {
        -1.0, -1.0, -1.0,   +1.0, -1.0, -1.0,   +1.0, +1.0, -1.0,   -1.0, +1.0, -1.0,
        -1.0, -1.0, +1.0,   +1.0, -1.0, +1.0,   +1.0, +1.0, +1.0,   -1.0, +1.0, +1.0,
    };
    GLfloat     fcolors[] =
    {
        0.2, 0.9, 0.5,      0.9, 0.2, 0.9,      0.0, 0.8, 0.4,      0.5, 0.2, 0.0,
        0.8, 0.4, 0.1,      0.1, 0.0, 0.4,      0.0, 0.2, 0.3,      0.0, 0.8, 0.5
    };
    GLfloat     fcolors2[] =
    {
        0.5, 0.5, 0.5,      0.5, 0.5, 0.5,      0.5, 0.5, 0.5,      0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,      0.5, 0.5, 0.5,      0.5, 0.5, 0.5,      0.5, 0.5, 0.5
    };
    GLfloat     fcolors3[] =
    {
        0.1, 0.5, 0,1,      0.1, 0.5, 0,1,      0.1, 0.5, 0,1,      0.1, 0.5, 0,1,
        0.1, 0.5, 0,1,      0.1, 0.5, 0,1,      0.1, 0.5, 0,1,      0.1, 0.5, 0,1
    };
    GLubyte     indices[] =
    {
        0, 1, 2,    2, 3, 0,
        0, 3, 4,    4, 7, 3,
        0, 1, 4,    1, 5, 4,
        1, 2, 5,    5, 6, 2,
        2, 3, 7,    7, 6, 2,
        4, 5, 6,    6, 7, 4
    };
    GLubyte		indicet[] = 
	{
        0, 1, 2,    2, 3, 0,
        
        0, 1, 4,    1, 5, 4,
        
        2, 3, 7,    7, 6, 2,
        4, 5, 6,    6, 7, 4
	};
	
	glEnable(GL_LIGHTING); // for no lighting ...
	// drawing blocks:
	for(int j=0; j<nRows	/*RANDURI*/; j++)		// how many rows in the scene ...
	{
	    for(int i=0; i<nUnits	/*CUBURI*/; i++)			// howm many elements in a row ...
	    {
	    	for(int k=0; k<=23; k+=3)
			{
				vertices[k+0]+=3;		// modify just the x;
			}
						
		    glEnableClientState(GL_VERTEX_ARRAY);
		    glEnableClientState(GL_COLOR_ARRAY);
			// then draw:
		    glVertexPointer(3, GL_FLOAT, 0, vertices);
		    glColorPointer(3, GL_FLOAT, 0, fcolors3);
		    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
		    glDisableClientState(GL_COLOR_ARRAY);
		    glDisableClientState(GL_VERTEX_ARRAY);
	    }
		// then modify the y's:
	    for(int k=0; k<=23; k+=3)	
	    {
	    	vertices[k+1]+=3;		// modify just the y;
	    }
	}
  	glDisable(GL_LIGHTING); // for no lighting ...
    //
}


void StreetLights(int nPairs, float fDist)			// lighting spheres imitating street lights
{
    float fTest = 3.5092;			// MODIFY THIS VALUE BEFORE EVERY DEBUG/ RUN/ COMPILATION
	float fLight[] = {+0.0, +0.3, +0.0, +1.0};
	float fColor[] = {+1.0, +1.0, +0.4, +1.0};
    
    glEnable(GL_LIGHTING);		// GL_EMISSION		// GL_LIGHTING
	glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, fColor);
	// drawing sphere:
	glPushMatrix();
	glTranslatef(2.0, -2.0, 4.0);
	for(int i = 0; i<=nPairs; i++)			// Pairs of L+R street lights 
	{
		glTranslatef(fDist, 0.0, 0.0);			// Distance between lights
		for(int j=0; j<=1; j++)
		{
			if(j==0){glTranslatef(0.0, +4.0, 0.0);}else{glTranslatef(0.0, -4.0, 0.0);}
			GLUquadric* pqdrs01;
		    pqdrs01 = gluNewQuadric();		// a quadric required 
		    if(pqdrs01)
		    {
		    	gluQuadricNormals(pqdrs01, GLU_SMOOTH);
				// gluQuadricTexture(pqdrs01, GL_TRUE);
				// gluQuadricDrawStyle(pqdrs01, GLU_SILHOUETTE);
		    	gluSphere(pqdrs01, 0.2f, 10, 10);
				
		    }
		    else
			{
				// MessageBoxW(NULL, L"no shpere!", L"", MB_OK);
			}
		    gluDeleteQuadric(pqdrs01);
		}
	}
	glPopMatrix();
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}


void TheSea2()
{	// based only on moving terrain...
	// draws sea
	const int 		nLin = 40;
	const int		nCol = 40;
	
	float* 			vertices = (float*)GlobalAlloc(GPTR, nLin*nCol*3);
	short*			indices = (short*)GlobalAlloc(GPTR, nLin*nCol);
	
	for(int i=0; i<=nLin; i++)
	{
		for(int j=0; j<=nCol; j+=3)
		{
			vertices[i+j+0]=(float)i;
			vertices[i+j+1]=(float)j;
			vertices[i+j+2]=0.0f;
		}
	}
	GlobalFree(vertices);
}

void TheSea()
{	// based on texture:
	// draws a quadratic area representing just a seawater and nothing more...
	//////////////////////////////////////////////////////////////////
 	float vertices[] = { 		
	 					-850.0f, -850.0f, 0.0f,  	//0 index
						+850.0f, -850.0f, 0.0f, 	//1
						+850.0f, +850.0f, 0.0f, 	//2
						-850.0f, +850.0f, 0.0f, 	//3
	};
	short indices[] = { 0, 1, 2, 2, 3, 0};
	float texture[] = { 0, 0,	0, 48,	48, 48,	48, 0,	//... I repeat these 4 coordinate ...  times
						};
    glEnableClientState( GL_VERTEX_ARRAY );        // Enable Vertex Arrays
 	glEnableClientState( GL_TEXTURE_COORD_ARRAY );   	// Enable Texture Coord Arrays
	glEnable(GL_TEXTURE_2D);		// ... forgotten!!!						
	LoadBitmapTexture(15);
	glVertexPointer( 3, GL_FLOAT, 0, vertices ); 					// Set The Vertex Pointer To Our Vertex Data
	glTexCoordPointer( 2, GL_FLOAT, 0, texture ); 					// Set The Vertex Pointer To Our TexCoord Data
	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_SHORT, indices);	// Draw the wall	
    glDisableClientState( GL_VERTEX_ARRAY );        				// Enable Vertex Arrays
 	glDisableClientState( GL_TEXTURE_COORD_ARRAY );   				// Enable Texture Coord Arrays
	glDisable(GL_TEXTURE_2D);
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	}

void TheHall()
{
	float fTest = 0.000;
	float	fVerts[] = {
		+00.00, -01.00, +00.00,		+00.00, +01.00, +00.00,		+04.00, -01.00, +00.00,		+04.00, +01.00, +00.00,
		+00.00, -01.00, +03.00,		+00.00, +01.00, +03.00,		+04.00, -01.00, +03.00,		+04.00, +01.00, +03.00,		
	};
	float	fColor[] = {
		+00.20, +00.30, +30.00,		+00.20, +00.20, +30.00,		+00.20, +00.10, +00.00,		+00.20, +00.40, +00.40,
		+00.20, +00.90, +30.00,		+00.30, +00.40, +30.00,		+00.30, +00.00, +00.50,		+00.20, +00.10, +00.00,
	};
	float	fCoords[] = {
		0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
	};
	BYTE 	fIndex[] = {
		0, 1, 2,	2, 3, 1,		0, 2, 4, 	4, 6, 2,		4, 5, 6,	6, 7, 5,		1, 5, 3,	3, 7, 5
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glPushMatrix();
	for(int i=0; i<=80; i++)
	{
		glVertexPointer(3, GL_FLOAT, 0, fVerts);
		glColorPointer(3, GL_FLOAT, 0, fColor);	    	
		glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_BYTE, fIndex);
		glTranslatef(4.0, 0.0, 0.0);
	}
	glPopMatrix();
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

void NewHall()
{
	// 
}

void Scari(int nTrepte)			// deseneaza scari
{
	float 	fVerts[] = {
		0.0, -1.0, 0.0, 	0.0, +1.0, 0.0,		
		0.2, -1.0, 0.0,		0.2, +1.0, 0.0, 	
		0,2, -1.0, 0.2, 	0.2, +1.0, 0.2
	};
	
	float 	fColor[] = {
		0.1, 0.8, 0.2, 		0.3, 0.5, 0.4, 	
		0.4, 0.7, 0.5,		0.8, 0.3, 0.1, 	
		0.5, 0.4, 0.8, 		0.9, 0.0, 0.8
	};
	
	BYTE	fIndex[] = {
		0, 1, 2, 	1, 2, 3, 
		2, 3, 4,	3, 4, 5
	};
	
}

void Punte()		// deseneaza puntea	// draw the deck
{
	
	glPushMatrix();
	
	glTranslatef(84.0f*4.0f, 10.0f-2.0f, 3.0f);
	// glTranslatef(0.00f, 0.00f, -0.10f);
	GLfloat fVerts[] = {
					-10.00f, -10.00f, +00.00f, 
					+10.00f, -10.00f, +00.00f, 
					+10.00f, +10.00f, +00.00f, 
					-10.00f, +10.00f, +00.00f
						};
	GLuint	nIndex[] = {0, 1, 2, 0, 2, 3};
	GLfloat fTexCo[] = {0, 0,	0, 1,	1, 1,	1, 0};
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	
	LoadJpegTexture(106);
	glVertexPointer(3, GL_FLOAT, 0, fVerts);
	glTexCoordPointer(2, GL_FLOAT, 0, fTexCo); 					
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nIndex);
	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);	
	 // 
	glPopMatrix();
}

void CeilLightsOnHall()
{
	float fLight[] = {+0.0, +0.0, -4.0, +1.0};
	float fColor[] = {+1.0, +0.9, +0.0, +1.0};
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fColor);

	glPushMatrix();
	glTranslatef(2.0, 0.0, 3.0);
	for(int i = 0; i<=80; i++)
	{
		GLUquadric*	pqdrLamp = gluNewQuadric();		// a quadric required
		if(pqdrLamp)
		{
			gluQuadricNormals(pqdrLamp, GLU_SMOOTH);
			gluSphere(pqdrLamp, 0.2, 8, 8);
		}
		glTranslatef(4.0, 0.0, 0.0);
	}
	glPopMatrix();
	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void RestrictCamOnTheHall(cxCam* pCam) // a kind of primitive collision response animator
{			// temporary solution 
	if((pCam->x>0.0)&&(pCam->x<81*4))
	{
		if(pCam->y<-0.7){pCam->y=-0.68; return;}	
		if(pCam->y>+0.7){pCam->y=+0.68; return;}	
		if(pCam->z<+0.3){pCam->z=+0.32; return;}		
		if(pCam->z>+2.7){pCam->z=+2.68; return;}		
	}
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

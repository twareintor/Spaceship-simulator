
/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
//////////////////////////////////// loadTextures.cpp //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "loadTextures.h"


void LoadJpegTexture(int id)
{	//
    LPWSTR			wszFNm = (LPWSTR)GlobalAlloc(GPTR, 0x60);		// for the image...
	swprintf(wszFNm, L"Tex%03d.jpg", id);
	int x, y, n;
	int force_channels = 4;
	unsigned char*  image_data;
	FILE *filTex = _wfopen(wszFNm, L"rb");
	// image_data = stbi_load(sz_FNm, &x, &y, &n, force_channels);	// replaced with the function next, just to may have files with unicode name
	image_data = stbi_load_from_file(filTex, &x, &y, &n, force_channels);
	fclose(filTex);
	GlobalFree(wszFNm);
	if (!image_data)
	{
		// some error message
	}
	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) 
	{
		// some warning message here...
	}
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0,	GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	free(image_data);
}

void LoadBitmapTexture(int id) 
{       // from ""		// thanks to Rachel Grey
		
		HDC				hdcY = CreateCompatibleDC(NULL);
		HBITMAP 		hBmp = NULL;
        LPWSTR			wszTexImg = (LPWSTR)GlobalAlloc(GPTR, 0x60);		// for the image...

		swprintf(wszTexImg, L"TEX1%02d.BMP", id);
		// hBmp = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(id), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		// hBmp = (HBITMAP)LoadImageW(GetModuleHandle(NULL), MAKEINTRESOURCEW(id), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		hBmp = (HBITMAP)LoadImageW(GetModuleHandle(NULL), wszTexImg, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		// hBmp = (HBITMAP)LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(id));
		GlobalFree(wszTexImg);
        if(hBmp==INVALID_HANDLE_VALUE)
			MessageBoxW(NULL, L"Texture bitmap image not loaded", L"", MB_OK);
        BITMAP 				bm;
        BITMAPINFO 			bi;
		GetObject(hBmp, sizeof(bm), &bm);

		LPBYTE			lpbytImg = (LPBYTE)GlobalAlloc(GPTR, bm.bmWidth*bm.bmHeight*3);

	    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	    bi.bmiHeader.biWidth = bm.bmWidth;
	    bi.bmiHeader.biHeight = bm.bmHeight;
	    bi.bmiHeader.biPlanes = 1;
	    bi.bmiHeader.biBitCount = 24;
	    bi.bmiHeader.biCompression = BI_RGB;        
	    bi.bmiHeader.biSizeImage = 0;        
		GetDIBits(hdcY, hBmp, 0, bm.bmHeight, lpbytImg, &bi, DIB_RGB_COLORS);
		// now the texture itself:
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, bm.bmWidth, bm.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, lpbytImg);
        // free resources: closing operations:
		GlobalFree(lpbytImg);
        DeleteObject((HGDIOBJ)hBmp);  //avoid memory leak (Windows)
}


void TestTexture()
{	// texture:
    glEnable(GL_TEXTURE_2D);
    // SetTextureFilter(TF_NONE);
    LoadBitmapTexture(6);
    float oneFortieth = 1.0/40.0;
    //define how the s parameter depends on x, y, z, w
    GLfloat myparamsS[] = {oneFortieth, 0.00, 0.00, 1.0};
    //define how the t parameter depends on x, y, z, w
    GLfloat myparamsT[] = {0.00, oneFortieth, 0.00, 1.0};
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, myparamsS);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, myparamsT);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //use GL_MODULATE instead of GL_REPLACE if lighting is being used
	// ~texture
}


void TestBitmap(HDC hdc)
{	// does not work!!!!!!!!
	
	LPWSTR			wszMsg = (LPWSTR)GlobalAlloc(GPTR, 0x400);
	
	HDC				hdcB = CreateCompatibleDC(hdc);
	HWND			hwnd = WindowFromDC(hdc);
	// HBITMAP 		hbm = (HBITMAP)LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_TEX_101));
	// HBITMAP 		hbm = (HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(IDB_TEX_101), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
	HBITMAP			hbm = (HBITMAP)LoadImage(NULL, "TEX101.BMP", IMAGE_BITMAP, 128, 128, LR_LOADFROMFILE);
	BITMAP			bm;
	HBITMAP 		hbmOld;
	PAINTSTRUCT		ps;
	LPRECT			lprcCli = (LPRECT)GlobalAlloc(GPTR, sizeof(RECT));	

	if(hbm==NULL)
	{
		MessageBoxW(NULL, wszMsg, L"bitmap not loaded!!!", 0);
	}
	GetObject(hbm, sizeof(bm), &bm);
	GetClientRect(hwnd, lprcCli);
	BeginPaint(hwnd, &ps);
	hbmOld = (HBITMAP)SelectObject(hdcB, hbm);
	BitBlt(hdc, lprcCli->left, lprcCli->top, lprcCli->left+bm.bmWidth, lprcCli->top+bm.bmHeight, hdcB, 0, 0, SRCPAINT);

	SelectObject(hdcB, hbmOld);
	DeleteObject(hbmOld);
	DeleteObject(hbm);
	EndPaint(hwnd, &ps);
	GlobalFree(lprcCli);
	CloseHandle(hbmOld);
	CloseHandle(hbm);
	CloseHandle(hwnd);
	
	GlobalFree(wszMsg);
}




















////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

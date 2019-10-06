
///////////////////////////////////////////// cx_game_utils.h ///////////////////////////////////////////////////////////////////////////////

#include "cx_game_utils.h"


int PrintCoords(cxCam* pCam, HDC hdc)			// DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!
{
	return 0;	
	LPWSTR			wszMsg = (LPWSTR)GlobalAlloc(GPTR, 0x400);
	float R = (float)sqrt((pCam->x0-pCam->x)*(pCam->x0-pCam->x)+(pCam->y0-pCam->y)*(pCam->y0-pCam->y)+(pCam->z0-pCam->z)*(pCam->z0-pCam->z));
	float fi = (float)asin(pCam->z0-pCam->z)/R;
	float Rp = (float)sqrt((pCam->x0-pCam->x)*(pCam->x0-pCam->x)+(pCam->y0-pCam->y)*(pCam->y0-pCam->y));
	float th = (float)acos(pCam->x0-pCam->x)/Rp;
	
	swprintf(wszMsg, L" x  : %+08.3f    x0 : %+08.3f    xv : %+08.3f", pCam->x, pCam->x0, pCam->xv);
	TextOutW(hdc, 4, 28, wszMsg, wcslen(wszMsg));
	swprintf(wszMsg, L" y  : %+08.3f    y0 : %+08.3f    yv : %+08.3f", pCam->y, pCam->y0, pCam->yv);
	TextOutW(hdc, 4, 40, wszMsg, wcslen(wszMsg));
	swprintf(wszMsg, L" z  : %+08.3f    z0 : %+08.3f    zv : %+08.3f", pCam->z, pCam->z0, pCam->zv);
	TextOutW(hdc, 4, 52, wszMsg, wcslen(wszMsg));
	swprintf(wszMsg, L" th : %+08.3f    fi : %+08.3f    R  : %+08.3f    Rp : %+08.3f", th, fi, R, Rp);
	TextOutW(hdc, 4, 04, wszMsg, wcslen(wszMsg));
	GlobalFree(wszMsg);
	return 0;		
}

int PrintParams(float fds, float fdq, float fdt, float fdf, float fdh, float Pow, HDC hdc) // DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!
{	
	// shows the parameters of the command device...
	return 0;
	LPWSTR			wszMsg = (LPWSTR)GlobalAlloc(GPTR, 0x400);
	
	swprintf(wszMsg, L" fds: %+08.3f    fdq: %+08.3f", fds, fdq);
	TextOutW(hdc, 580, 04, wszMsg, wcslen(wszMsg));
	swprintf(wszMsg, L" fdt: %+08.3f    fdf: %+08.3f    fdh: %+08.3f", fdt, fdf, fdh);
	TextOutW(hdc, 580, 16, wszMsg, wcslen(wszMsg));
	swprintf(wszMsg, L" Pow: %+08.3f", Pow);
	TextOutW(hdc, 580, 28, wszMsg, wcslen(wszMsg));
	GlobalFree(wszMsg);
	return 0;
}
		
		
int PrintWelcomeW(HDC hdc, LPCWSTR wszMsg)
{
	HFONT		hFont;
	HFONT		hFOld;
	
	hFont = CreateFont(40,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, VARIABLE_PITCH,TEXT("Terminal"));
    hFOld = (HFONT)SelectObject(hdc, hFont);
    // set BK_Mode as transparent...
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 0));
    TextOutW(hdc, 128, 128, wszMsg, wcslen(wszMsg));
    SelectObject(hdc, hFOld);
    CloseHandle(hFOld);
    CloseHandle(hFont);
    
    return wcslen(wszMsg);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
// Credits: Microsoft Corporation

// #include "globals.h"
#include "main.h"

#define PI 3.14159265359f

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    // float theta = 0.0f;

    /* register window class */
    // wc.style = CS_OWNDC;
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(127, 18, 127));
	wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);
    /* create main window */
    HDC 	hdcMainScr = GetWindowDC(NULL);
    hWnd = CreateWindowW(
      L"GLSample", L"OpenGL Sample", 
      WS_CAPTION|WS_POPUPWINDOW|WS_VISIBLE,
      0, 
	  0, 
	  GetDeviceCaps(hdcMainScr, HORZRES), 
	  GetDeviceCaps(hdcMainScr, HORZRES)*9/16,
      NULL, NULL, hInstance, NULL);
	// Print welcome string:
	// MessageBoxW(NULL, L"Program start here", L"", MB_OK);
	
	HDC		hdc = GetDC(hWnd);

	PrintWelcomeW(hdc, L"Welcome! Press <ENTER> to start");
	ReleaseDC(hWnd, hdc);
    /* enable OpenGL for the window */
        
    EnableOpenGL (hWnd, &hDC, &hRC);   
    
	// now the initialization of the game, and the start screen:
	// InitializationsVBO();
	
	Initializations(60.0, (float)GetDeviceCaps(hdcMainScr, HORZRES), (float)(GetDeviceCaps(hdcMainScr, HORZRES)*600/900));
	ShowCursor(FALSE);
	//when create window class for application window
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */
			// not here, but in the main loop of WndProc()
        }
    }
 
    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);
	ShowCursor(TRUE);
    /* destroy the window explicitly */
    DestroyWindow (hWnd);
	Finalizaitions();
    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC 		hdc;
	static BOOL		bTest;
	static BOOL 	bLight;
	static float	fds;			// delta-s displacement along the axis of view
	static float	fdsq;			// delta-s variable displacement to simulate acceleration
	static float	fas;			// delta-s displacement iterated one-by-one in timer to simulate accelerating/ decelerating
	static float 	fdt;			// delta-theta 		// pitch increment		// azimouth
	static float 	fdtq;			// delta-theta acceleration effect
	static float	fdf;			// delta-phi		// yaw increment		// elevation
	static float	fdfq;			// delta-phi acceleration effect
	static float	fdh;			// delta-hi			// roll increment		// inclination
	static float 	fdhq;			// delta-hi acceleration effect
	static float	fdu;			// delta-Y			// position left-right
	static float	fduq;			// delta-Y acceleration effect
	static float	fdw;			// delta-Z			// position up-down
	static float	fdwq;			// delta-Z acceleration effect
	static float 	Pow;			// power of the engine // zero to 10
	static float	fIt;			// iteration over time, to simulate the inertial effect
	
	static double	R;				// the distance to the poiningn object // 
	// static float 	fX, fY, fZ;		// not used anymore
	static CxCam	Cam;
	static float	fAng;			// angle of rotation for glRotatef() function for special effects:
	static BOOL		bMove;			// engine status
	static BOOL		bJoyX;			// command taken from joystick
	static BOOL		bStop;			// engine stopped
	static BOOL		brake;			// brake pressed
	static BOOL		bBall;			// there is a ball or not on the scene...

	static HFONT	hFont;
	static HFONT	hFOld;
	
	static POINT	pM[2];			// Mouse position
	
	// rotating the planet:
	static float	thPl;			// instant theta of the planet, 
	static float	thRevStar;		// the "revolution" angle of the star
	
	// Joystick variables:
	// Get the pointer to the raw device data, process it and update the window
	static CxJoyStk* pJoX = (CxJoyStk*)GlobalAlloc(GPTR, sizeof(CxJoyStk));
	
	static PRAWINPUT 	pRawInput;
	static UINT      	bufferSize;
	static HANDLE    	hHeap;
	
	LPWSTR 			wszMsg = (LPWSTR)GlobalAlloc(GPTR, 0xff);
	
   	switch (message)
    {
	    case WM_CREATE:
	    {
	    	SetStdOutToNewConsole();	// just for debug and development
	    	
	    	// all parameter initialization..................... 
			bTest = FALSE;
	    	bLight = FALSE;
	    	fds = 0.1f;						// 10 cm
			// fX = 0.0f; fY = 0.0f; fZ = 0.0f; // not used anymore
			fdt = (float)DEG;						// 1 Deg.
			// fdf = (float)DEG;						// 1 Deg.
			fdh = (float)DEG;						// 1 Deg. // rolling angle
			Pow = 1;
			ZeroMemory(&Cam, sizeof(CxCam));
			ZeroMemory(pM, sizeof(POINT)*2);
			Cam.x = 0.0f;
			Cam.x0 = Cam.x+2.0f;
			Cam.z = 1.75f;
			Cam.z0 = Cam.z;		// look direct to the horizon
			Cam.xv = 0.0f;
			Cam.yv = 0.0f;
			Cam.zv = 1.0f;		// normal vector oriented just up
			fIt = 0.0002f;		// iteration to simulate the inertial effect at acceleration (use it in "case WM_TIMER:{}")
			fAng = 0.0f;
			bMove = FALSE;		// engine stopped
			bJoyX = FALSE;		// no default control to joystick, but mouse at first
			bStop = TRUE;		// engine stopped
			brake = FALSE;		// no brake pressed
			bBall = FALSE;		// no ball on the scene...
			// R = sqrt((Cam.x0-Cam.x)*(Cam.x0-Cam.x)+(Cam.y0-Cam.y)*(Cam.y0-Cam.y)+(Cam.z0-Cam.z)*(Cam.z0-Cam.z));
			// swprintf(wszMsg, L"R = %g (it must be 1.0)", R);
			// MessageBoxW(NULL, wszMsg, L"", MB_OK);
			hdc = GetDC(hWnd);
			// Prepare the font size and face for runtime messages and displays:
			hFont = CreateFont(10,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		        CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, FIXED_PITCH, TEXT("Courier"));
		    hFOld = (HFONT)SelectObject(hdc, hFont);
		    // set BK_Mode as transparent...
		    SetBkMode(hdc, TRANSPARENT);
		    SetTextColor(hdc, RGB(255, 255, 0));
            /////// code for joystick:
            // Register for joystick devices
			RAWINPUTDEVICE rid;

			rid.usUsagePage = 1;
			rid.usUsage     = 4;	// Joystick
			rid.dwFlags     = 0;
			rid.hwndTarget  = hWnd;
			// rotating the planet: according to the daytime of the system
			
			if(RegisterRawInputDevices(&rid, 1, sizeof(RAWINPUTDEVICE)))
			{
				bJoyX = TRUE;
			}
			else
			{
				MessageBoxW(NULL, L"Joystick registering failed", L"Joystick message", MB_OK);
			}
			// controlling the rotation of the planet: initial rotation
			thPl = (float)(GetTickCount()%360);
			SetTimer(hWnd, ID_TIMER, 30, NULL);			// ??? FPS
			// SetTimer(hWnd, ID_TIMER2, 30, NULL); // then start the rotation
			break;
	    }
	    case WM_ACTIVATE:
	    {
	    	if(LOWORD(wParam==WA_ACTIVE))
	    	{
	    		float params = thPl;
		    	Redraw(hdc, false, &Cam, &params);
		    	MoveIt(&Cam, 0.0);
	    	}
	    	break;
	    }
	    case WM_CLOSE:
	    {
	    	SelectObject(hdc, hFOld);
	    	CloseHandle(hFOld);
	    	CloseHandle(hFont);
			GlobalFree(pJoX);
	    	GlobalFree(wszMsg);
	        ReleaseDC(hWnd, hdc);
	        ShowCursor(TRUE);
			PostQuitMessage (0);
	        return 0;
	    }
	    case WM_DESTROY:
		{
			// KillTimer(hWnd, ID_TIMER2);
			KillTimer(hWnd, ID_TIMER);        // Timer to move...
			ReleaseDC(hWnd, hdc);
	        return 0;	
		}
		case WM_INPUT:
		{
			if(bJoyX)
			{
				GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &bufferSize, sizeof(RAWINPUTHEADER));
	
				hHeap     = GetProcessHeap();
				pRawInput = (PRAWINPUT)HeapAlloc(hHeap, 0, bufferSize);
				if(!pRawInput)
					return 0;
	
				GetRawInputData((HRAWINPUT)lParam, RID_INPUT, pRawInput, &bufferSize, sizeof(RAWINPUTHEADER));
				ParseRawInput(pRawInput, pJoX);
	
				HeapFree(hHeap, 0, pRawInput);
				
				// NOTE: the yaw and pitch rate react proportionally to "fds" 
				// PrintJoystickCoords(pJoX, hdc);
				if(bMove)		// replace with a condition like activating the joystick
				{
					// Traveling:
					fds = -(float)pJoX->lAxisY/128*Pow; // travel speed
					if(fds>+3.9*Pow)		fds=+3.9*Pow;
					if(fds<-3.9*Pow)		fds=-3.9*Pow;
					// Yawing (left-right):
					fdt = -(float)pJoX->lAxisX*0.1/DEG*(Pow*0.25f); // the pitch angle: Joystick left-right
					// fdt = -(float)pJoX->lAxisRz*0.1/DEG;
					// Rolling					
					if(pJoX->bButtonStates[6])		// in order to avoid unwanted rolling by pitching with the stick...
					{
						fdh = -(float)pJoX->lAxisRz*0.1/DEG*(1+(Pow-1)*0.32f)*(Pow*0.25f); // fdh is rolling???
					}
					else
					{
						fdh = 0;
					}
					// rolling also through buttons 2 (left) and 3 (right)
					fdh-=-0.05*fds*(pJoX->bButtonStates[2]-pJoX->bButtonStates[3]);
					if(fdh>+35*DEG)		fdh=+35*DEG;					// limit to ... degrees the roll angle...
					if(fdh<-35*DEG)		fdh=-35*DEG;
				}
				fdf = (+0.01*(pJoX->lHat==1)-0.01*(pJoX->lHat==5))*(1.f+fabs(fds/3.f)); // pitch angle: the speed also count
				Pow = 1+(1.0-(128.0+(float)pJoX->lAxisZ)/255)*9; 		// the power
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			// TurnIt(&Cam, +0.0f, +0.0f, +fdh);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			// TurnIt(&Cam, +0.0f, +0.0f, -fdh);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			if(bMove)
			{
				float 	fD = GET_WHEEL_DELTA_WPARAM(wParam)/120.0/50;
				switch(LOWORD(wParam))
				{
					case MK_SHIFT:
					{
						Cam.y+=fD;
						Cam.y0+=fD;
						MoveIt(&Cam, 0.0);
						break;
					}
					case MK_CONTROL:
					{
						Cam.z+=fD;
						Cam.z0+=fD;
						MoveIt(&Cam, 0.0);
						break;
					}
					default:
					{
						fdf = fD/5.0;
						TurnIt(&Cam, 0.0f, fD/5.0f, 0.0f);
						break;
					}
				}
			}
			break;
		}
		case WM_MOUSEMOVE:
		{
			if(!bJoyX)
			{
				// to be replaced with the function used for joystick...
			}
			break;
		}
		case WM_TIMER:
		{
			switch(wParam)
			{
				case ID_TIMER:
				{
					thPl+=0.01;			// this rotates the planet....
					if(fds+fdsq+fdu+fduq+fdw+fdwq+fdt+fdtq+fdf+fdtq+fdh+fdhq)	// accelerating	effect by moving along, up/ down
					{
						if(!bStop)		
						{	// accelerating
							fdsq+=(fds-fdsq)*sqrt(1+fdsq)*0.01;  	// speed ispoint following the setpoint
							fduq+=(fdu-fduq)*0.01;		// position left-right
							fdwq+=(fdw-fdwq)*0.01;		// position up-down
							fdtq+=(fdt-fdtq)*0.1;
							fdfq+=(fdf-fdfq)*0.1;
							fdhq+=(fdh-fdhq)*0.1;
						}
						else
						{	// decelerating 
							fdsq*=0.95;		// speed ispoint decreasing till zero - deceleration...
							fduq*=0.95;
							fdwq*=0.95;
							fdtq*=0.95;
							fdfq*=0.95;
							fdhq*=0.95;
						}
						MoveIt(&Cam, fdsq, fduq, fdwq);
						TurnIt(&Cam, +fdtq, +fdfq, +fdhq); // pitch and roll the camera; yaw is done also here and no more in the case WM_INPUT
					}
					if(!bMove)		// if engine stopped by user ...
					{
	    				if(abs(fdsq)+abs(fduq)+abs(fdwq)<0.005)	// if engine is stopped and no more speed
	    				{	
							fds = 0.1;		// reset all to the initial values
							fdsq = 0.0;		
							fdt = DEG;
							fdtq = 0.0;
							fdf = DEG;
							fdfq = 0.0;
							fdh = DEG;
							fdhq = 0.0;
							fdu = 0.0;
							fduq = 0.0;
							fdw = 0.0;
							fdwq = 0.0;
		        			bMove = FALSE;
	    				}
					}
					if(brake)		// ... as long as the brake is pressed
					{
						fds = 0.0;			// speed setpoint to zero
						fdsq*=0.85;			// speed increment ispoint decreasing
						fdu = 0.0;
						fduq*=0.85;
						fdw = 0.0;
						fdwq*=0.85;
						fdt = 0.0;			// angle increment set to zero
						fdtq*=0.85;
						fdf = 0.0;
						fdfq*=0.85;
						fdh = 0.0;
						fdhq*=0.85 ;
					}
					float params = thPl; 
    				Redraw(hdc, bLight, &Cam, &params);
					// PrintCoords(&Cam, hdc);
    				// PrintParams(fds, fdsq, fdt, fdf, fdh, Pow, hdc);
					break;
				}
				case ID_TIMES:
				{
					// SetFAng(fAng++);			// __???
					break;
				}
			}
			break;
		}
		case WM_KEYUP:
		{
			switch(wParam)
			{
				case VK_SPACE:
				{
					brake = FALSE;		// brake released
					pM[0].x = pM[1].x;
					pM[0].y = pM[1].y;	// in order to not to have to repoint the mouse in the zero-position
					break;
				}
				case VK_UP:			// move  forward alongside the eye==>pointing direction
	        	{
					fds = 0.0;
					break;
				}
				case VK_DOWN:		// move  forward alongside the eye==>pointing direction
	        	{
					fds = 0.0;
					break;
				}
				case VK_RIGHT:		// turn right stop
				{
					fdt = 0.0;
					break;
				}
				case VK_LEFT:		// turn left stop
				{
					fdt = 0.0;
					break;
				}
	        	case 0x52:			// R - Pitch positive stop
	        	{
					fdf = 0.0;
	        		break;
				}
				case 0x46:			// F - Pitch negative stop
				{
					fdf = 0.0;
					break;
				}
				case 0x41:			// A - Roll positive stop
				{
					fdh = 0.0;
					break;
				}
				case 0x53:			// S - Roll negative stop
				{
					fdh = 0.0;
					break;
				}
				case 0x51:			// Q - Lateral disp negative (poistion left)
				{
					fdu = 0.0;
					break;
				}
				case 0x57:			// W - Lateral disp negative (poistion right)
				{
					fdu = 0.0;
					break;
				}
				case 0x54:			// T - Elevate positive (poistion up)
				{
					fdw = 0.0;
					break;
				}
				case 0x47:			// G - Elevate negative (poistion up)
				{
					fdw = 0.0;
					break;
				}
			}
			break;
		}
	    case WM_KEYDOWN:
	        switch (wParam)
	        {
	        	case VK_RETURN:
	        	{
	        		float params = thPl;
	        		// Redraw(hdc, bLight, &Cam, &params);
	        		// PrintCoords(&Cam, hdc);
	        		break;
	        	}
		        case VK_ESCAPE:		// terminating the application
	        	{
			    	GlobalFree(wszMsg);
			        SelectObject(hdc, hFOld);
			        ReleaseDC(hWnd, hdc);
			        ShowCursor(TRUE);
					PostQuitMessage (0);
		            return 0;
        		}
        		case VK_INSERT:		// starting the engines
        		{
					// starting effect:
        			// end of starting effect
        			bStop = FALSE;
        			if(!bMove)
					{
						fds = 0.0;		// set all to zero, in order to be set again from the mouse position
						fdu = 0.0;
						fdw = 0.0;
						fdt = 0.0;		// and the increment value of the angles
						fdf = 0.0;		// 
						fdh = 0.0;		// 
					}
					bMove = TRUE;
        			break;
        		}
        		case VK_DELETE:		// engine stop
        		{
    				// first stop attenuately:
    				bStop = TRUE;
    				bMove = FALSE;
        			break;
        		}
        		case VK_SPACE:		// braktriggered
        		{
        			brake = TRUE;
        			break;
        		}
        		case 0x57:			// W
	        	case VK_UP:			// move  forward alongside the eye==>pointing direction
	        	{
					fds = +1.0;
					fds*=Pow;
					if(fds>+0.9*Pow)		fds=+0.9*Pow;
					//if(fds<-0.9*Pow)		fds=-0.9*Pow;
					break;
	        	}
	        	case 0x53:			// S
	        	case VK_DOWN:		// move backwards 
	        	{
					fds = -1.0;
					fds*=Pow;
					//if(fds>+0.9*Pow)		fds=+0.9*Pow;
					if(fds<-0.9*Pow)		fds=-0.9*Pow;
					break;
	        	}
	        	case 0x44:			// D
		        case VK_RIGHT:		// turn right
	        	{	
					fdt = -1.0*DEG*Pow;
					//if(fdt>+35*DEG)		fdt=+35*DEG;	// limit to ... degrees the pitch angle
					if(fdt<-35*DEG)		fdt=-35*DEG;
					break;
	        	}
	        	case 0x41:			// A
	        	case VK_LEFT:		// turn left
	        	{
					fdt = +1.0*DEG*Pow;
					if(fdt>+35*DEG)		fdt=+35*DEG;	// limit to ... degrees the pitch angle
					//if(fdt<-35*DEG)		fdt=-35*DEG;
	        		break;
	        	}
	        	case 0x52:			// R - Pitch positive
	        	{
					fdf = +1.0*DEG*Pow;
					if(fdf>+15*DEG)		fdf=+15*DEG;	// limit to ... degrees the pitch angle
					//if(fdf<-15*DEG)		fdf=-15*DEG;
	        		break;
				}
				case 0x46:			// F - Pitch negative
				{
					fdf = -1.0*DEG*Pow;
					//if(fdf>+15*DEG)		fdf=+15*DEG;	// limit to ... degrees the pitch angle
					if(fdf<-15*DEG)		fdf=-15*DEG;
					break;
				}
				case 0x51:			// Q - Roll positive
				{
					fdh = +1.0*DEG*Pow;
					if(fdh>+15*DEG)		fdh=+15*DEG;	// limit to ... degrees the pitch angle
					//if(fdh<-15*DEG)		fdh=-15*DEG;
					break;
				}
				case 0x45:			// E - Roll negative
				{
					fdh = -1.0*DEG*Pow;
					//if(fdh>+15*DEG)		fdh=+15*DEG;	// limit to ... degrees the pitch angle
					if(fdh<-15*DEG)		fdh=-15*DEG;
					break;
				}
				case 0x59:			// Y - Lateral disp negative (poistion left)
				{
					fdu = -1.0*Pow;
					//if(fdu>+10)		fdu=+10;	// limit to ... degrees the pitch angle
					if(fdu<-10)		fdu=-10;
					break;
				}
				case 0x43:			// C - Lateral disp negative (poistion right)
				{
					fdu = +1.0*Pow;
					if(fdu>+10)		fdu=+10;	// limit to ... degrees the pitch angle
					//if(fdu<-10)		fdu=-10;
					break;
				}
				case 0x54:			// T - Elevate positive (poistion up)
				{
					fdw = +1.0*Pow;
					//if(fdw>+10)		fdw=+10;	// limit to ... degrees the pitch angle
					if(fdw<-10)		fdw=-10;
					break;
				}
				case 0x47:			// G - Elevate negative (poistion up)
				{
					fdw = -1.0*Pow;
					if(fdw>+10)		fdw=+10;	// limit to ... degrees the pitch angle
					if(fdw<-10)		fdw=-10;
					break;
				}
	        	case VK_F2:			// mouse/ joystick control switch
	        	{
	        		if(bStop)
	        		{
		        		if(bJoyX)
		        		{
		        			MessageBoxW(NULL, L"Mouse control", L"Input option changed", MB_OK);
						}
						else
						{
							MessageBoxW(NULL, L"Stick control", L"Input option changed", MB_OK);
						}
						bJoyX = !bJoyX;
					}
	        		break;
				}
				case 50: // key "2" from keyboard
				{
					thPl++;
					if (thPl>=360.f) thPl = 0.f; // reset to zero 
					break;
				}
				case 51: // key "3" from keyboard
				{
					thPl--;
					if (thPl<=0.f) thPl = 360.f; // reset to zero 
					break;
				}
	        	case VK_HOME:		// back to the origin
	        	{	
	        		if(bStop)
	        		{
		        		int nOpt = MessageBoxW(NULL, L"Would you like to return to the start?", L"Back to the start", MB_YESNO);
		        		if(nOpt==IDYES)
	        			{
							ZeroMemory(&Cam, sizeof(CxCam));
							Cam.x = 0.0;
							Cam.x0 = Cam.x+2;
							Cam.z = 1.75;
							Cam.z0 = Cam.z;		// look direct to the horizon
							Cam.zv = 1.0;		// for the moment, constant
							MoveIt(&Cam, +fds);
							float params = thPl;
							Redraw(hdc, bLight, &Cam, &params);
							// PrintCoords(&Cam, hdc);
	        			}
	        		}
	        		break;
	        	}
	        	case VK_ZOOM:
	        	{
	        		// MessageBoxW(NULL, L"ZOOM", L"", MB_OK);
	        		break;
				}
	   	        break;
	        }
	        return 0;
	    default:
		{
			return DefWindowProc (hWnd, message, wParam, lParam);
	    }
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}





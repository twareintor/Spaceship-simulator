

// sends the standard output to new console (for debug only)

#include "stdout2con.h"


void SetStdOutToNewConsole()
{
    // allocate a console for this app
    AllocConsole();

    // redirect unbuffered STDOUT to the console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int fileDescriptor = _open_osfhandle((intptr_t)consoleHandle, _O_WTEXT);		// _O_TEXT or _O_WTEXT
    FILE *fp = _fdopen( fileDescriptor, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // give the console window a nicer title
    SetConsoleTitleW(L"Debug Output");

    // give the console window a bigger buffer size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(consoleHandle, &csbi))
    {
        COORD bufferSize;
        // bufferSize.X = csbi.dwSize.X;
        bufferSize.Y = 900;
        bufferSize.Y = 9999;
        SetConsoleScreenBufferSize(consoleHandle, bufferSize);
    	SMALL_RECT rcCon = {100, 100, 1700, 1700};
		SetConsoleWindowInfo(consoleHandle, false, &rcCon);    	
        
    }
}



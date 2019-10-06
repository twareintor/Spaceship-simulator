/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////// logprn.cpp ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" 

#include "logprn.h"

LogFile::LogFile(LPCWSTR wszFNm, LPWSTR wszLogName)
{
	wszAppName = (LPWSTR)GlobalAlloc(GPTR, 0x400);
	wszExeName = (LPWSTR)GlobalAlloc(GPTR, 0x400);
	wszAppPath = (LPWSTR)GlobalAlloc(GPTR, 0x400);
	GetModuleFileNameW(NULL, wszAppName, 0x400);
    wszExeName = wcsrchr(wszAppName, L'\\');
    wcsncpy(wszAppPath, wszAppName, wszExeName-wszAppName);
    // MessageBoxW(NULL, wszAppPath, wszAppPath, MB_OK);
	swprintf(wszLogName, L"%s", wszAppPath);
    wcscat(wszLogName, L"\\");
    wcscat(wszLogName, wszFNm);

}

LogFile::~LogFile()
{
    GlobalFree(wszAppPath);
    GlobalFree(wszExeName);
	GlobalFree(wszAppName);
	
}



int CnnLogPrnW(LPCWSTR wszFNm, LPCWSTR wszWhat, double xWhat)
{
        int                     nOut = 0;
        LPWSTR          wszTmp = (LPWSTR)GlobalAlloc(GPTR, 0x400);

        swprintf(wszTmp, wszWhat, xWhat);
        // MessageBoxW(NULL, wsszTmp, wszWhat, MB_OK);   // TEST
        CxxLogPrnW(wszFNm, wszTmp);
        GlobalFree(wszTmp);
        return nOut;
}

int CxxLogPrnW(LPCWSTR wszFNm, LPCWSTR wszWhat)
{
    // does nothing more than appending the string wszWhat at the end of the file wszFNm.....
    int            	nOut = 0;
    LPWSTR			wszLogName = (LPWSTR)GlobalAlloc(GPTR, 0x400);
    
	// LogFile			CrLogFile(wszFNm, wszLogName);    
    HANDLE        	hLogFile = CreateFileW(
                                        wszFNm,
                                        GENERIC_READ+GENERIC_WRITE,
                                        FILE_SHARE_DELETE+FILE_SHARE_READ+FILE_SHARE_WRITE,
                                        NULL,
                                        OPEN_ALWAYS,
                                        FILE_ATTRIBUTE_NORMAL,
                                        NULL
                                        );
    DWORD        dwBytesWritten = 0;
    if(hLogFile!=INVALID_HANDLE_VALUE)
    {
		SetFilePointer(hLogFile, 0, NULL, FILE_END);
        WriteFile(
                    hLogFile,
                    wszWhat,
                    wcslen(wszWhat)*2,
                    &dwBytesWritten,
                    NULL
                    );          // write what to log is...
		nOut = 1;
    }
    else
    {
        // nOut = -3209;		// zero means error...
        // MessageBoxW(NULL, L"here!!!", L"", MB_OK);
    }
    CloseHandle(hLogFile);
    GlobalFree(wszLogName);
    return nOut;

}


int TEST_CastTypes()            // DEACTIVATED!!!! // DEACTIVATED!!!! // DEACTIVATED!!!! // DEACTIVATED!!!!
{
        /****************************************************************
        void*                   pInv = (void*)GlobalAlloc(GPTR, sizeof(DWORD));
        double*                 pxOut = (double*)GlobalAlloc(GPTR, sizeof(double));
        LPWSTR                  wszTmp;

        swprintf(wszTmp, L"Value = %d", *static_cast<double>(pInv));
        MessageBoxW(NULL, wszTmp, );

        GlobalFree(pxOut);
        GlobalFree(pInv);

        ****************************************************************/
        return 0;

}



//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////




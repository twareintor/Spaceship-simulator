
/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
///////////////////////////////////////////////////// file2buf.cpp ////////////////////////////////////////////////////

#include "file2buf.h"


DWORD FileToBufW(LPCWSTR lpwszFNm, LPSTR lpszBuf)
{
	HANDLE		hFile;
	DWORD		dwBytesRead;
	BOOL		bRead;
	
	hFile = CreateFileW(
						lpwszFNm, 
						GENERIC_READ, 
						FILE_SHARE_READ+FILE_SHARE_WRITE, 
						(LPSECURITY_ATTRIBUTES)NULL, 
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						(HANDLE)NULL
						);
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		// get the file size: 
		DWORD 	dwSize = GetFileSize(hFile, NULL);
		bRead = ReadFile(
						hFile,
						lpszBuf,
						dwSize,
						&dwBytesRead,
						(LPOVERLAPPED)NULL
						);
	}
	return dwBytesRead;	
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

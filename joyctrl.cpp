
/** Copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" */
// copyright (c) 2007 - 2018 Claudiu Ciutacu "Twareintor" 

/****************************************************************************************************/

#include "joyctrl.h"


void ParseRawInput(PRAWINPUT pRawInput, CxJoyStk* pJoX)
{
	PHIDP_PREPARSED_DATA pPreparsedData;
	HIDP_CAPS            Caps;
	PHIDP_BUTTON_CAPS    pButtonCaps;
	PHIDP_VALUE_CAPS     pValueCaps;
	USHORT               capsLength;
	UINT                 bufferSize;
	HANDLE               hHeap;
	USAGE                usage[MAX_BUTTONS];
	ULONG                i, usageLength, value;

	pPreparsedData = NULL;
	pButtonCaps    = NULL;
	pValueCaps     = NULL;
	hHeap          = GetProcessHeap();

	//
	// Get the preparsed data block
	//

	CHECK( GetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_PREPARSEDDATA, NULL, &bufferSize) == 0 );
	CHECK( pPreparsedData = (PHIDP_PREPARSED_DATA)HeapAlloc(hHeap, 0, bufferSize) );
	CHECK( (int)GetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_PREPARSEDDATA, pPreparsedData, &bufferSize) >= 0 );

	//
	// Get the joystick's capabilities
	//

	// Button caps
	CHECK( HidP_GetCaps(pPreparsedData, &Caps) == HIDP_STATUS_SUCCESS )
	CHECK( pButtonCaps = (PHIDP_BUTTON_CAPS)HeapAlloc(hHeap, 0, sizeof(HIDP_BUTTON_CAPS) * Caps.NumberInputButtonCaps) );

	capsLength = Caps.NumberInputButtonCaps;
	CHECK( HidP_GetButtonCaps(HidP_Input, pButtonCaps, &capsLength, pPreparsedData) == HIDP_STATUS_SUCCESS )
	pJoX->g_NumberOfButtons = pButtonCaps->Range.UsageMax - pButtonCaps->Range.UsageMin + 1;

	// Value caps
	CHECK( pValueCaps = (PHIDP_VALUE_CAPS)HeapAlloc(hHeap, 0, sizeof(HIDP_VALUE_CAPS) * Caps.NumberInputValueCaps) );
	capsLength = Caps.NumberInputValueCaps;
	CHECK( HidP_GetValueCaps(HidP_Input, pValueCaps, &capsLength, pPreparsedData) == HIDP_STATUS_SUCCESS )

	//
	// Get the pressed buttons
	//

	usageLength = pJoX->g_NumberOfButtons;
	CHECK(
		HidP_GetUsages(
			HidP_Input, pButtonCaps->UsagePage, 0, usage, &usageLength, pPreparsedData,
			(PCHAR)pRawInput->data.hid.bRawData, pRawInput->data.hid.dwSizeHid
		) == HIDP_STATUS_SUCCESS );

	ZeroMemory(pJoX->bButtonStates, sizeof(pJoX->bButtonStates));
	for(i = 0; i < usageLength; i++)
		pJoX->bButtonStates[usage[i] - pButtonCaps->Range.UsageMin] = TRUE;

	//
	// Get the state of discrete-valued-controls
	//

	for(i = 0; i < Caps.NumberInputValueCaps; i++)
	{
		CHECK(
			HidP_GetUsageValue(
				HidP_Input, pValueCaps[i].UsagePage, 0, pValueCaps[i].Range.UsageMin, &value, pPreparsedData,
				(PCHAR)pRawInput->data.hid.bRawData, pRawInput->data.hid.dwSizeHid
			) == HIDP_STATUS_SUCCESS );

		switch(pValueCaps[i].Range.UsageMin)
		{
		case 0x30:	// X-axis
			pJoX->lAxisX = (LONG)value - 128;
			break;

		case 0x31:	// Y-axis
			pJoX->lAxisY = (LONG)value - 128;
			break;

		case 0x32: // Z-axis
			pJoX->lAxisZ = (LONG)value - 128;
			break;

		case 0x35: // Rotate-Z
			pJoX->lAxisRz = (LONG)value - 128;
			break;

		case 0x39:	// Hat Switch
			pJoX->lHat = value;
			break;
		}
	}

	//
	// Clean up
	//

Error:
	SAFE_FREE(pPreparsedData);
	SAFE_FREE(pButtonCaps);
	SAFE_FREE(pValueCaps);
}

int PrintJoystickCoords(CxJoyStk* pJoX, HDC hdc) // DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!DEACTIVATED!!!!!!!!!!!!
{
	return 0;
	LPWSTR			wszMsg = (LPWSTR)GlobalAlloc(GPTR, 0x400);
 
	TextOutW(hdc, 4, 600, L"Stick control:", 14);
	swprintf(wszMsg, L" lAX: %0000d    lAY: %0000d    lAZ: %0000d", pJoX->lAxisX, pJoX->lAxisY, pJoX->lAxisZ);
	TextOutW(hdc, 4, 612, wszMsg, wcslen(wszMsg));
	swprintf(wszMsg, L" iNB: %0000d    lAR: %0000d    lHa: %0000d", pJoX->g_NumberOfButtons, pJoX->lAxisRz, pJoX->lHat);
	TextOutW(hdc, 4, 624, wszMsg, wcslen(wszMsg));
	GlobalFree(wszMsg);

	return 0;	
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/****************************************************************************************************/



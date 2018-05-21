#include "stdafx.h"
#include "gui_common.h"


bool MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{
	// Get the required size of the buffer that receives the Unicode
	// string.
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);
 
	if(dwSize < dwMinSize)
	{
		return false;
	}
 
	// Convert headers from ASCII to Unicode.
	MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);  
	return true;
}
bool WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,NULL,0,NULL,FALSE);
	if(dwSize < dwMinSize)
	{
		return false;
	}
	WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,lpszStr,dwSize,NULL,FALSE);
	return true;
}



void	SetTextToEdit(CEdit *pEdt, char *value)
{
	if (NULL == pEdt)		return;
	if (NULL == value)		return;

	wchar_t wszValue[512] = {0};
	memset(wszValue, 0x00, sizeof(wszValue));
	MByteToWChar(value, wszValue, sizeof(wszValue)/sizeof(wszValue[0]));
	if (NULL != pEdt)	pEdt->SetWindowText(wszValue);
}
void	SetTextToEdit(CEdit *pEdt, int value)
{
	if (NULL == pEdt)		return;
	if (NULL == value)		return;

	wchar_t wszValue[512] = {0};
	wsprintf(wszValue, TEXT("%d"), value);
	if (NULL != pEdt)	pEdt->SetWindowText(wszValue);
}
void	GetTextToInt(CEdit *pEdt, int *value)
{
	if (NULL == pEdt)		return;

	wchar_t wszValue[512] = {0};
	memset(wszValue, 0x00, sizeof(wszValue));
	pEdt->GetWindowText(wszValue, sizeof(wszValue));

	if (NULL != value)		*value = _wtoi(wszValue);
}

void	GetTextToChar(CEdit *pEdt, char *value, int valueSize)
{
	if (NULL == pEdt)		return;
	if (NULL == value || valueSize<1)	return;

	memset(value, 0x00, valueSize);

	wchar_t wszValue[512] = {0};
	memset(wszValue, 0x00, sizeof(wszValue));
	pEdt->GetWindowText(wszValue, sizeof(wszValue));

	WCharToMByte(wszValue, value, valueSize);
}


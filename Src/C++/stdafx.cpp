

#include "stdafx.h"



RENDER_FORMAT		RenderFormat = RENDER_FORMAT_RGB24_GDI;
PLAYER_HANDLE		playerHandle = NULL;



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



int CheckFolder(wchar_t *folderName, int bCreate)
{
#ifdef _WIN32
	//?¨¬2¨¦???t?D¨º?¡¤?¡ä??¨²
	WIN32_FIND_DATA wfd;
	HANDLE m_hFile = NULL;
	
	if (NULL == folderName)		return -1;
	
	m_hFile = FindFirstFile(folderName, &wfd);
	if (INVALID_HANDLE_VALUE == m_hFile)	//2?¡ä??¨²
	{
		if (bCreate==0x01)
		{
			if (! CreateDirectory(folderName, NULL))	//¡ä¡ä?¡§???t?D¨º¡ì¡ã¨¹
			{
				//TRACE(szLog, "¡ä¡ä?¡§???t?D¨º¡ì¡ã¨¹: %s\n", folderName);
				return -1;
			}
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return 0;
	}
#else

	DIR *dir = opendir(folderName);
	if (NULL != dir)
	{
		closedir(dir);
		_TRACE(TRACE_LOG_WARNING, "Path already exist.\n");
		return 0;
	}
	else
	{
		if (bCreate==0x01)
		{
			int err = mkdir(folderName, 0755);
			if (err == 0)
			{
				_TRACE(TRACE_LOG_DEBUG, "Path not exist. create success.\n");
			}
			else
			{
				_TRACE(TRACE_LOG_ERROR, "Path not exist. create fail.%d\n", err);
				return -1;
			}
			return 0;
		}
		else
		{
			return -1;
		}
	}

	return 0;
#endif
	return -1;
}


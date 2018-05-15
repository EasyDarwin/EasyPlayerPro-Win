

#include "stdafx.h"



PRO_CONFIG_T	proConfig;

RENDER_FORMAT		RenderFormat = RENDER_FORMAT_RGB24_GDI;
PLAYER_HANDLE		playerHandle = NULL;



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


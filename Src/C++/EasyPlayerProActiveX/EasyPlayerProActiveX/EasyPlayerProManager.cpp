/*
	Copyright (c) 2013-2018 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
#include "StdAfx.h"
#include "EasyPlayerProManager.h"
#include <io.h>
#include <direct.h>

#include <string>
using namespace std;

#define gap_char ('\\')

EasyPlayerProManager::EasyPlayerProManager(void)
{
	memset(&m_sSourceInfo, 0x0, sizeof(EASY_LOCAL_SOURCE_T));
	m_sSourceInfo.sourceId = 0;

}

EasyPlayerProManager::~EasyPlayerProManager(void)
{
}

//打开流
int EasyPlayerProManager::Start(char* szURL, HWND hShowWnd, int renderFormat,  int nRTPOverTCP, int nCache, 
	BOOL bShownToScale, int nVolume, BOOL bStatisticalInfo)
{
	//Stop
	if (InRunning())
	{
		//AfxMessageBox(_T("InRunning()"));
		//Close();
		return -1;
	}

	char* file_url = szURL;
	EASY_CHANNEL_SOURCE_TYPE_ENUM				sourceType = EASY_CHANNEL_SOURCE_TYPE_RTSP;
	if (0 == strncmp(szURL, "rtsp", 4))			sourceType = EASY_CHANNEL_SOURCE_TYPE_RTSP;
	else if (0 == strncmp(szURL, "rtmp", 4))	sourceType = EASY_CHANNEL_SOURCE_TYPE_RTMP;
	else if (0 == strncmp(szURL, "http", 4))	sourceType = EASY_CHANNEL_SOURCE_TYPE_HLS;
	else if (0 == strncmp(szURL, "file", 4))
	{
		sourceType = EASY_CHANNEL_SOURCE_TYPE_FILE;
		file_url = szURL + 7;
	}

	// player open file
	m_sSourceInfo.sourceId = EasyPlayerPro_Open(file_url, hShowWnd, EASY_VIDEO_RENDER_TYPE_D3D,
		(EASY_VIDEO_SCALE_MODE)bShownToScale, (EASY_STREAM_LINK_MODE)nRTPOverTCP, 100, nVolume-182);
	if (m_sSourceInfo.sourceId)
	{
		m_sSourceInfo.nVolume = nVolume;
		//SetTimer(TIMER_ID_PROGRESS, 1000, NULL);
// 		if (NULL != pDlgRender)
// 		{
// 			pDlgRender->SetChannelId(m_ChannelId);
// 			pDlgRender->SetSourceType(sourceType);
// 		}

	}

	return (int)m_sSourceInfo.sourceId;
}


//关闭流
int EasyPlayerProManager::Close(void)
{
	if (!InRunning())
		return -1;

	EasyPlayerPro_Close(m_sSourceInfo.sourceId);
	m_sSourceInfo.sourceId = 0;
	return 0;
}
int EasyPlayerProManager::InRunning()
{
	return m_sSourceInfo.sourceId>0?TRUE:FALSE;
}

//设置OSD
int EasyPlayerProManager::SetOSD(int show,  int x, int y, int color, const char* osd)
{
	if (!InRunning())
		return -1;

	if (show)
	{
		//需要整改
		return EasyPlayerPro_SetOSD(m_sSourceInfo.sourceId, show, 0,0,0,0,0,0,0,0,0,0,0);
	}
	else
	{
		return EasyPlayerPro_SetOSD(m_sSourceInfo.sourceId, 0, 0,0,0,0,0,0,0,0,0,0,0);
	}
}

int EasyPlayerProManager::EnsureDirExist(CString dir)
{
	int len = 0;
	char temp_dir[MAX_PATH];
	char * pindex = NULL;
	int access_flag = 0;
	USES_CONVERSION;
	const char * p_dir = T2A(dir.GetBuffer(dir.GetLength()));

	if (!_access(p_dir, 0))
	{
		return 1;
	}
	//
	len = strlen(p_dir);
	if (len >= MAX_PATH)
	{
		return 0;
	}

	memset(temp_dir, 0, MAX_PATH);
	memcpy(temp_dir, p_dir, len);

	pindex = temp_dir;
	pindex = strrchr(pindex, gap_char);
	if (pindex >= (temp_dir + len - 1))
	{
		*pindex = 0;
	}

	pindex = temp_dir;
	pindex = strchr(pindex, gap_char);
	if (!pindex)
	{
		return 0;
	}
	pindex++;

	access_flag = 0;
	do
	{
		pindex = strchr(pindex, gap_char);

		if (pindex)
		{
			*pindex = 0;
		}

		access_flag = _access(temp_dir, 0);

		if (access_flag)
		{
#ifdef _WIN32
			if (_mkdir(temp_dir))
#else
			if (mkdir(temp_dir, 0x777))
#endif
			{
				return 0;
			}
		}

		if (pindex)
		{
			*pindex = gap_char;
			pindex++;
		}
	} while (pindex);

	//
	if (_access(p_dir, 0))
	{
		return 0;
	}
	return 1;
}

//录像
int EasyPlayerProManager::StartRecord(const char *filename, int duration/*录像切片时长(min), 为0则表示不切片*/)
{
	if (!InRunning())
		return -1;
	m_sSourceInfo.recording = (m_sSourceInfo.recording==0x00?0x01:0x00);

#if 0
	char sztmp[36] = {0};
	time_t tt = time(NULL);
	struct tm *_time = localtime(&tt);
	memset(sztmp, 0x00, sizeof(sztmp));
	strftime(sztmp, 32, "%Y%m%d_%H%M%S", _time);
	char szFilename[MAX_PATH] = {0};
	sprintf(szFilename, "ch%d_%s.mpg", m_sSourceInfo.sourceId, sztmp);
#endif
	CString sFileName = (CString)filename;
	bool bSec = EnsureDirExist(sFileName);

	if (m_sSourceInfo.recording == 0x01)
	{
		int ret = EasyPlayerPro_Record(m_sSourceInfo.sourceId, (char*)filename, duration);
		if (ret < 0)	
			m_sSourceInfo.recording = 0x00;
	}
	return 0;
}

int EasyPlayerProManager::StopRecord()
{
	if (!InRunning())
		return -1;
	if (m_sSourceInfo.recording)
	{
		return EasyPlayerPro_Stoprecord( m_sSourceInfo.sourceId );
	}
	return 0;
}

//抓图
int EasyPlayerProManager::Snapshot( char *filename,  int width, int height, int waitTime)
{
	if (!InRunning())
		return -1;
	int imageFormat = 1;/*0:bmp 1:jpg*/
	string sFilename = filename;
	int nFind = sFilename.rfind("bmp",0);
	imageFormat = (nFind>=0)?0:1;

	return EasyPlayerPro_Snapshot(m_sSourceInfo.sourceId, filename, width,height, waitTime);
}

//声音播放和控制
int EasyPlayerProManager::PlaySound(BOOL bPlay)
{
	if (!InRunning())
		return -1;
	if (bPlay)
	{
		int nVolume = -255;
		EasyPlayerPro_Getparam(m_sSourceInfo.sourceId, EASY_PARAM_AUDIO_VOLUME, &nVolume);
		if (nVolume > -182)//-182 ~ 73
		{
			nVolume = -182;
		}

		EasyPlayerPro_Setparam(m_sSourceInfo.sourceId, EASY_PARAM_AUDIO_VOLUME, &nVolume);	
		m_sSourceInfo.bPlaySound = 0x01;
	}
	else
	{
		EasyPlayerPro_Setparam(m_sSourceInfo.sourceId, EASY_PARAM_AUDIO_VOLUME, &m_sSourceInfo.nVolume);
		m_sSourceInfo.bPlaySound = 0x00;
	}
	return 0;
}

int EasyPlayerProManager::SetAudioVolume( int volume)
{
	if (!InRunning())
		return -1;
	int nVolume = volume-182;
	if (m_sSourceInfo.bPlaySound == 0x01)
	{
		EasyPlayerPro_Setparam(m_sSourceInfo.sourceId, EASY_PARAM_AUDIO_VOLUME, &nVolume);	
	}
	m_sSourceInfo.nVolume = volume;

}

int EasyPlayerProManager::GetAudioVolume()
{
	if (!InRunning())
		return -1;
	int nVolume = -255;
	EasyPlayerPro_Getparam(m_sSourceInfo.sourceId, EASY_PARAM_AUDIO_VOLUME, &nVolume);

	return nVolume+182;//m_sSourceInfo.nVolume;
}

//播放控制
// 设置播放速度(文件)
int EasyPlayerProManager::SetPlaySpeed(SPEED_RATE speed)
{
	if (!InRunning())
		return -1;
	int nRate = 100;
	switch(speed)
	{		 
	case SPEED_SLOW_X16:
		nRate =  300;
		break;
	case SPEED_SLOW_X8 :
		nRate = 250;
		break;
	case SPEED_SLOW_X4: 
		nRate = 200;
		break;
	case SPEED_SLOW_X2:
		nRate = 150;
		break;
	case SPEED_NORMAL:   
		nRate = 100;
		break;
	case SPEED_FAST_X2:   
		nRate = 75;
		break;
	case SPEED_FAST_X4 :  
		nRate = 50;
		break;
	case SPEED_FAST_X8:   
		nRate = 35;
		break;
	case SPEED_FAST_X16 :
		nRate = 25;
		break;
	case SPEED_FAST_X64 :
		nRate = 15;
		break;
	}
	//EasyPlayerPro_Play(m_sSourceInfo.sourceId);	//恢复
	EasyPlayerPro_Setparam(m_sSourceInfo.sourceId, EASY_PARAM_PLAY_SPEED, &nRate);
	return	1;
}

//单帧播放, 可调用libEasyPlayerPro_SetPlaySpeed切换回正常播放模式
int EasyPlayerProManager::PlaySingleFrame()
{
	if (!InRunning())
		return -1;
	EasyPlayerPro_StepPlay(m_sSourceInfo.sourceId);
	return 1;
}

//跳转到指定时间播放(文件)
int EasyPlayerProManager::SeekFile( unsigned int playTimeMSecs/*毫秒*/ )
{
	if (!InRunning())
		return -1;
	EasyPlayerPro_Seek(m_sSourceInfo.sourceId, playTimeMSecs);
	return 1;
}

int EasyPlayerProManager::Pause()
{
	if (!InRunning())
		return -1;
	EasyPlayerPro_Pause(m_sSourceInfo.sourceId);
}
	

int EasyPlayerProManager::Play(SPEED_RATE speed)
{
		
		EasyPlayerPro_Play(m_sSourceInfo.sourceId);	//恢复
	int nRate = 100;
	switch(speed)
	{		 
	case SPEED_SLOW_X16:
		nRate =  300;
		break;
	case SPEED_SLOW_X8 :
		nRate = 250;
		break;
	case SPEED_SLOW_X4: 
		nRate = 200;
		break;
	case SPEED_SLOW_X2:
		nRate = 150;
		break;
	case SPEED_NORMAL:   
		nRate = 100;
		break;
	case SPEED_FAST_X2:   
		nRate = 75;
		break;
	case SPEED_FAST_X4 :  
		nRate = 50;
		break;
	case SPEED_FAST_X8:   
		nRate = 35;
		break;
	case SPEED_FAST_X16 :
		nRate = 25;
		break;
	case SPEED_FAST_X64 :
		nRate = 15;
		break;
	}
	EasyPlayerPro_Setparam(m_sSourceInfo.sourceId, EASY_PARAM_PLAY_SPEED, &nRate);
	return 1;
}

/*
	Copyright (c) 2013-2014 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
#include "StdAfx.h"
#include "EasyPlayerProManager.h"
#include <string>
using namespace std;

EasyPlayerProManager::EasyPlayerProManager(void)
{
	memset(&m_sSourceInfo, 0x0, sizeof(EASY_LOCAL_SOURCE_T));
	m_sSourceInfo.sourceId = -1;

}

EasyPlayerProManager::~EasyPlayerProManager(void)
{
}

//打开流
int EasyPlayerProManager::Start(char* szURL, HWND hShowWnd, RENDER_FORMAT renderFormat, int nRTPOverTCP, int nCache, 
	BOOL bShownToScale, BOOL bPlaySound, BOOL bStatisticalInfo)
{
	//Stop
	if (InRunning())
	{
		//AfxMessageBox(_T("InRunning()"));
		//Close();
		return -1;
	}

	EASY_CHANNEL_SOURCE_TYPE_ENUM		sourceType = EASY_CHANNEL_SOURCE_TYPE_RTSP;
	if (0 == strncmp(szURL, "rtsp", 4))	sourceType = EASY_CHANNEL_SOURCE_TYPE_RTSP;
	else if (0 == strncmp(szURL, "rtmp", 4))	sourceType = EASY_CHANNEL_SOURCE_TYPE_RTMP;
	else if (0 == strncmp(szURL, "http", 4))	sourceType = EASY_CHANNEL_SOURCE_TYPE_HLS;
	else if (0 == strncmp(szURL, "file", 4))	sourceType = EASY_CHANNEL_SOURCE_TYPE_FILE;

	int queueSize = 1024 * 1024 * 2;		//2MB
	if (sourceType == EASY_CHANNEL_SOURCE_TYPE_HLS)		
		queueSize = 1024 * 1024 * 5;		//5MB

	m_sSourceInfo.sourceId = libEasyPlayerPro_OpenStream(NULL, sourceType, szURL, 
		nRTPOverTCP, 
		MEDIA_TYPE_VIDEO|MEDIA_TYPE_AUDIO|MEDIA_TYPE_EVENT,
		NULL, NULL, 0x01, 0x01, queueSize, 0x01);

#if 0
	CString strTemp;
	strTemp.Format(_T("m_sSourceInfo.sourceId = %d"), m_sSourceInfo.sourceId); 
	AfxMessageBox(strTemp);
#endif

	if (m_sSourceInfo.sourceId > 0)
	{
		//libEasyPlayerPro_StartPlayStream(playerHandle, m_ChannelId, hWnd, RenderFormat);
		libEasyPlayerPro_StartPlayStream(NULL, m_sSourceInfo.sourceId, hShowWnd, renderFormat);

		libEasyPlayerPro_SetPlayFrameCache(NULL, m_sSourceInfo.sourceId, nCache);		//设置缓存
		if(bPlaySound)
			libEasyPlayerPro_StartPlaySound(NULL, m_sSourceInfo.sourceId);				//播放声音

		libEasyPlayerPro_SetScaleDisplay(NULL, m_sSourceInfo.sourceId, bShownToScale, RGB(0x26,0x26,0x26));
		libEasyPlayerPro_ShowStatisticalInfo(NULL, m_sSourceInfo.sourceId, bStatisticalInfo);
	}
	return m_sSourceInfo.sourceId;
}


//关闭流
int EasyPlayerProManager::Close(void)
{
	if (!InRunning())
		return -1;

	libEasyPlayerPro_StopPlayStream(NULL, m_sSourceInfo.sourceId);
	libEasyPlayerPro_CloseStream(NULL, m_sSourceInfo.sourceId);
	m_sSourceInfo.sourceId = -1;
	return 0;
}
int EasyPlayerProManager::InRunning()
{
	return m_sSourceInfo.sourceId>0?TRUE:FALSE;
}

//设置OSD
int EasyPlayerProManager::SetOSD(int show, const char* osd)
{
	if (!InRunning())
		return -1;

	if (show)
	{
		return libEasyPlayerPro_SetOverlayText(NULL, m_sSourceInfo.sourceId, osd);
	}
	else
	{
		return libEasyPlayerPro_ClearOverlayText(NULL, m_sSourceInfo.sourceId);
	}
}

//录像
int EasyPlayerProManager::StartRecord(const char *foldername, 
	const char *filename, 
	unsigned int filesize/*录像文件大小 MB*/, int duration/*录像时长(second)*/,  
	unsigned char preRecording/*0x01:预录  0x00:不预录*/)
{
	if (!InRunning())
		return -1;
	m_sSourceInfo.recording = (m_sSourceInfo.recording==0x00?0x01:0x00);

	char sztmp[36] = {0};
	time_t tt = time(NULL);
	struct tm *_time = localtime(&tt);
	memset(sztmp, 0x00, sizeof(sztmp));
	strftime(sztmp, 32, "%Y%m%d_%H%M%S", _time);

	char szFilename[MAX_PATH] = {0};
	sprintf(szFilename, "ch%d_%s.mpg", m_sSourceInfo.sourceId, sztmp);

	if (m_sSourceInfo.recording == 0x01)
	{
		int ret = libEasyPlayerPro_StartRecording(NULL, m_sSourceInfo.sourceId, foldername, 
			szFilename, filesize, duration, preRecording);
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
		return libEasyPlayerPro_StopRecording(NULL, m_sSourceInfo.sourceId );
	}
	return 0;
}

//抓图
int EasyPlayerProManager::Snapshot( char *filename, unsigned char sync/*0:异步: 1:同步*/, 
	unsigned char useQueue/*1:使用队列 0:不使用队列*/)
{
	if (!InRunning())
		return -1;
	int imageFormat = 1;/*0:bmp 1:jpg*/
	string sFilename = filename;
	int nFind = sFilename.rfind("bmp",0);
	imageFormat = (nFind>=0)?0:1;

	for (int i=0; i<1; i++)
	{
		while (0 != libEasyPlayerPro_SnapshotToFile(NULL, m_sSourceInfo.sourceId, imageFormat, filename, 0,1))
		{
			Sleep(1);
		}
	}
	return 0;
}

//声音播放和控制
int EasyPlayerProManager::PlaySound(BOOL bPlay)
{
	if (!InRunning())
		return -1;
	if (m_sSourceInfo.bPlaySound == 0x00)
	{
		int ret = libEasyPlayerPro_StartPlaySound(NULL, m_sSourceInfo.sourceId);
		if (ret < 0)		m_sSourceInfo.bPlaySound = 0x00;
		else	
			m_sSourceInfo.bPlaySound = 0x01;
	}
	else
	{
		libEasyPlayerPro_StopPlaySound(NULL, m_sSourceInfo.sourceId);
		m_sSourceInfo.bPlaySound = 0x00;
	}
	return 0;
}

int EasyPlayerProManager::SetAudioVolume( int volume)
{
	if (!InRunning())
		return -1;
	return libEasyPlayerPro_SetAudioVolume(NULL, volume);
}

int EasyPlayerProManager::GetAudioVolume()
{
	if (!InRunning())
		return -1;

	return libEasyPlayerPro_GetAudioVolume(NULL);
}

//播放控制
// 设置播放速度(文件)
int EasyPlayerProManager::SetPlaySpeed(PLAY_SPEED_ENUM speed)
{
	if (!InRunning())
		return -1;
	return	libEasyPlayerPro_SetPlaySpeed(NULL, m_sSourceInfo.sourceId, speed);
}

//单帧播放, 可调用libEasyPlayerPro_SetPlaySpeed切换回正常播放模式
int EasyPlayerProManager::PlaySingleFrame()
{
	if (!InRunning())
		return -1;
	return libEasyPlayerPro_PlaySingleFrame(NULL, m_sSourceInfo.sourceId);
}

//跳转到指定时间播放(文件)
int EasyPlayerProManager::SeekFile(  unsigned int playTimeSecs/*秒*/ )
{
	if (!InRunning())
		return -1;
	return libEasyPlayerPro_SeekFile(NULL, m_sSourceInfo.sourceId, playTimeSecs);

}
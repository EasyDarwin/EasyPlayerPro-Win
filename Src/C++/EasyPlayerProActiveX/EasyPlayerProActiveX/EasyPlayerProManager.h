/*
	Copyright (c) 2013-2014 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
// RTSP流接收(播放)管理类，接收音视频流 [11/8/2015 Dingshuai]
// Add by SwordTwelve

#pragma once

#include "libEasyPlayerProAPI.h"

//Gavin's Source Struct流信息结构
typedef struct __EASY_LOCAL_SOURCE_T
{	
	int		sourceId;
	BOOL recording;
	BOOL bPlaySound;
	void* pMaster;
}EASY_LOCAL_SOURCE_T;

class EasyPlayerProManager
{
public:
	EasyPlayerProManager(void);
	~EasyPlayerProManager(void);

	//Member Function
public:
	//初始化
	static int Init()
	{
		return libEasyPlayerPro_Initialize(128);
	}

	// 释放
	static int UnInit()
	{
		return libEasyPlayerPro_Deinitialize();
	}

	//打开流
	int Start(char* szURL, HWND hShowWnd, RENDER_FORMAT renderFormat,  int nRTPOverTCP, int nCache, 
		BOOL bShownToScale, BOOL bPlaySound, BOOL bStatisticalInfo);
	//关闭流
	int Close(void);
	int InRunning();

	//设置OSD
	int SetOSD(int show, const char* osd);

	//录像
	int StartRecord(const char *foldername, 
		const char *filename, 
		unsigned int filesize/*录像文件大小 MB*/, int duration/*录像时长(second)*/,  
		unsigned char preRecording/*0x01:预录  0x00:不预录*/);
	int StopRecord();

	//抓图
	int Snapshot( 
		char *filename, unsigned char sync=0/*0:异步: 1:同步*/, 
		unsigned char useQueue=0/*1:使用队列 0:不使用队列*/);

	//声音播放和控制
	int PlaySound(BOOL bPlay);
	int SetAudioVolume( int volume);
	int GetAudioVolume();

	//播放控制
	// 设置播放速度(文件)
	int SetPlaySpeed(PLAY_SPEED_ENUM speed);
	//单帧播放, 可调用libEasyPlayerPro_SetPlaySpeed切换回正常播放模式
	int PlaySingleFrame();
	//跳转到指定时间播放(文件)
	int SeekFile( unsigned int playTimeSecs/*秒*/ );

	//Member Var
private:
	//接收的流信息
	EASY_LOCAL_SOURCE_T		m_sSourceInfo;
};


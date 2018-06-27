/*
	Copyright (c) 2013-2014 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
// RTSPï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(ï¿½ï¿½ï¿½ï¿½)ï¿½ï¿½ï¿½ï¿½ï¿½à£¬ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æµï¿½ï¿½ [11/8/2015 Dingshuai]
// Add by SwordTwelve

#pragma once

#include "libEasyPlayerProAPI.h"

/*
*¼¤»îÂë ¿ÉÔÚpvale.comÖÐ»ñÈ¡²âÊÔ¼¤»îÂë, »òÕßÓÊ¼þÁªÏµsupport@easydarwin.org
*/
#define ACTIVE_KEY "64687538665969576B5A7341676A4662704D35397065354659584E35554778686557567955484A764C6D56345A56634D5671442F70654E4659584E355247467964326C755647566862556C7A5647686C516D567A644541794D4445345A57467A65513D3D"

//Gavin's Source Structï¿½ï¿½ï¿½ï¿½Ï¢ï¿½á¹¹
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
	//³õÊ¼»¯¿âÎÄ¼þ
	static int Init()
	{
		int ret = libEasyPlayerPro_Activate(ACTIVE_KEY);
		if(ret != EASY_ACTIVATE_SUCCESS)
		{
			printf("Active error! ret = %d\r\n", ret);
			return ret;
		}
		return libEasyPlayerPro_Initialize(128);
	}

	// ï¿½Í·ï¿½
	static int UnInit()
	{
		return libEasyPlayerPro_Deinitialize();
	}

	//ï¿½ï¿½ï¿½ï¿½
	int Start(char* szURL, HWND hShowWnd, RENDER_FORMAT renderFormat,  int nRTPOverTCP, int nCache, 
		BOOL bShownToScale, BOOL bPlaySound, BOOL bStatisticalInfo);
	//ï¿½Ø±ï¿½ï¿½ï¿½
	int Close(void);
	int InRunning();

	//ï¿½ï¿½ï¿½ï¿½OSD
	int SetOSD(int show, const char* osd);

	//Â¼ï¿½ï¿½
	int StartRecord(const char *foldername, 
		const char *filename, 
		unsigned int filesize/*Â¼ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½ï¿½Ð¡ MB*/, int duration/*Â¼ï¿½ï¿½Ê±ï¿½ï¿½(second)*/,  
		unsigned char preRecording/*0x01:Ô¤Â¼  0x00:ï¿½ï¿½Ô¤Â¼*/);
	int StopRecord();

	//×¥Í¼
	int Snapshot( 
		char *filename, unsigned char sync=0/*0:ï¿½ì²½: 1:Í¬ï¿½ï¿½*/, 
		unsigned char useQueue=0/*1:Ê¹ï¿½Ã¶ï¿½ï¿½ï¿½ 0:ï¿½ï¿½Ê¹ï¿½Ã¶ï¿½ï¿½ï¿½*/);

	//ï¿½ï¿½ï¿½ï¿½ÅºÍ¿ï¿½ï¿½ï¿?
	int PlaySound(BOOL bPlay);
	int SetAudioVolume( int volume);
	int GetAudioVolume();

	//ï¿½ï¿½ï¿½Å¿ï¿½ï¿½ï¿½
	// ï¿½ï¿½ï¿½Ã²ï¿½ï¿½ï¿½ï¿½Ù¶ï¿½(ï¿½Ä¼ï¿½)
	int SetPlaySpeed(PLAY_SPEED_ENUM speed);
	//ï¿½ï¿½Ö¡ï¿½ï¿½ï¿½ï¿½, ï¿½Éµï¿½ï¿½ï¿½libEasyPlayerPro_SetPlaySpeedï¿½Ð»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä£Ê½
	int PlaySingleFrame();
	//ï¿½ï¿½×ªï¿½ï¿½Ö¸ï¿½ï¿½Ê±ï¿½ä²¥ï¿½ï¿½(ï¿½Ä¼ï¿½)
	int SeekFile( unsigned int playTimeSecs/*ï¿½ï¿½*/ );

	//Member Var
private:
	//ï¿½ï¿½ï¿½Õµï¿½ï¿½ï¿½ï¿½ï¿½Ï¢
	EASY_LOCAL_SOURCE_T		m_sSourceInfo;
};


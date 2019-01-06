/*
	Copyright (c) 2013-2018 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
// Add by SwordTwelve

#pragma once

#include "EasyDefine.h"
#include "EasyPlayerProAPI.h"

/*
*激活码 可在pvale.com中获取测试激活码, 或者邮件联系support@easydarwin.org
*/
#define ACTIVE_KEY "6A342B4E6B4969576B5A73416236316270464B517065354659584E35554778686557567955484A764C6D56345A56634D5671442F7065424859585A7062695A4359574A76633246414D6A41784E6B566863336C4559584A33615735555A5746745A57467A65513D3D"

//Gavin's Source Struct结构
typedef struct __EASY_LOCAL_SOURCE_T
{	
	void*	  sourceId;
	BOOL recording;
	BOOL bPlaySound;
	int      nVolume;
	void* pMaster;
}EASY_LOCAL_SOURCE_T;

class EasyPlayerProManager
{
public:
	EasyPlayerProManager(void);
	~EasyPlayerProManager(void);

	//Member Function
public:
	//初始化库文件
	static int Init(char* key)
	{
		char* sKey = key;
		if (sKey == NULL)
		{
			sKey = ACTIVE_KEY;
		}

		int ret = EasyPlayerPro_Authorize(sKey);
		if(ret != AUTH_SUCCESS)
		{
			CString strTemp;
			strTemp.Format(_T("Active error! ret = %d\r\n"), ret);
			AfxMessageBox(strTemp);
			return ret;
		}
		return 1;
	}

	static int UnInit()
	{
		return 1;
	}

	//开始拉流/播放文件
	int Start(char* szURL, HWND hShowWnd, int renderFormat,  int nRTPOverTCP, int nCache, 
		BOOL bShownToScale, int nVolume, BOOL bStatisticalInfo);
	//停止拉流/播放文件
	int Close(void);
	int InRunning();
	int Pause();
	int Play(SPEED_RATE speed);
	// 设置播放速度
	int SetPlaySpeed(SPEED_RATE speed);

	//设置OSD
	int SetOSD(int show, int x, int y, int color,  const char* osd);

	//开始录像
	int StartRecord(const char *filename, int duration/*录像切片时长(min), 为0则表示不切片*/);
	int StopRecord();

	//抓图
	// 		filePath			- 图片存放路径，以.xxx结束（xxx 目前只支持 jpeg 格式）
	// 		width, height       - 指定图片宽高，如果 <= 0 则默认使用视频宽高
	// 		waittime			- 是否等待截图完成 0 - 不等待，>0 等待超时 ms 为单位
	int Snapshot( char *filename,  int width, int height, int waitTime);

	//是否静音
	int PlaySound(BOOL bPlay);
	//设置播放音量
	int SetAudioVolume( int volume);
	//获取当前播放音量
	int GetAudioVolume();
	//单帧播放
	int PlaySingleFrame();
	//播放器进度seek(单位： 秒)
	int SeekFile( unsigned int playTimeSecs );
	void Resize(RECT rc)
	{
		if (m_sSourceInfo.sourceId)
		{
			EasyPlayerPro_Resize(m_sSourceInfo.sourceId, 0, 0, 0, rc.right, (rc.bottom - 2));
			EasyPlayerPro_Resize(m_sSourceInfo.sourceId, 1, 0, 0, rc.right, rc.bottom - 2);
		}
	}

protected:
	int EnsureDirExist(CString dir);


	//Member Var
private:
	//锟斤拷锟秸碉拷锟斤拷锟斤拷息
	EASY_LOCAL_SOURCE_T		m_sSourceInfo;
};


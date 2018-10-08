/*
	Copyright (c) 2013-2014 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
// RTSP������(����)�����࣬��������Ƶ�� [11/8/2015 Dingshuai]
// Add by SwordTwelve

#pragma once

#include "libEasyPlayerProAPI.h"

/*
*������ ����pvale.com�л�ȡ���Լ�����, �����ʼ���ϵsupport@easydarwin.org
*/
#define ACTIVE_KEY "64687538665969576B5A73416E727062704556687065354659584E35554778686557567955484A764C6D56345A56634D5671442F70654E4659584E355247467964326C755647566862556C7A5647686C516D567A644541794D4445345A57467A65513D3D"

//Gavin's Source Struct����Ϣ�ṹ
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
	//��ʼ�����ļ�
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

	// �ͷ�
	static int UnInit()
	{
		return libEasyPlayerPro_Deinitialize();
	}

	//����
	int Start(char* szURL, HWND hShowWnd, RENDER_FORMAT renderFormat,  int nRTPOverTCP, int nCache, 
		BOOL bShownToScale, BOOL bPlaySound, BOOL bStatisticalInfo);
	//�ر���
	int Close(void);
	int InRunning();

	//����OSD
	int SetOSD(int show, const char* osd);

	//¼��
	int StartRecord(const char *foldername, 
		const char *filename, 
		unsigned int filesize/*¼���ļ���С MB*/, int duration/*¼��ʱ��(second)*/,  
		unsigned char preRecording/*0x01:Ԥ¼  0x00:��Ԥ¼*/);
	int StopRecord();

	//ץͼ
	int Snapshot( 
		char *filename, unsigned char sync=0/*0:�첽: 1:ͬ��*/, 
		unsigned char useQueue=0/*1:ʹ�ö��� 0:��ʹ�ö���*/);

	//����źͿ���?
	int PlaySound(BOOL bPlay);
	int SetAudioVolume( int volume);
	int GetAudioVolume();

	//���ſ���
	// ���ò����ٶ�(�ļ�)
	int SetPlaySpeed(PLAY_SPEED_ENUM speed);
	//��֡����, �ɵ���libEasyPlayerPro_SetPlaySpeed�л�����������ģʽ
	int PlaySingleFrame();
	//��ת��ָ��ʱ�䲥��(�ļ�)
	int SeekFile( unsigned int playTimeSecs/*��*/ );

	//Member Var
private:
	//���յ�����Ϣ
	EASY_LOCAL_SOURCE_T		m_sSourceInfo;
};


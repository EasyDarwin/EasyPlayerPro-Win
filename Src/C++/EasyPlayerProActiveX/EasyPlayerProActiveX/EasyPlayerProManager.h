/*
	Copyright (c) 2013-2018 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.EasyDarwin.org
*/
// Add by SwordTwelve

#pragma once

#include "../libEasyPlayerPro/include/EasyDefine.h"
#include "../libEasyPlayerPro/include/EasyPlayerProAPI.h"

/*
*������ ����pvale.com�л�ȡ���Լ�����, �����ʼ���ϵsupport@easydarwin.org
*/
#define ACTIVE_KEY "EasyPlayer is Free!"

//Gavin's Source Struct�ṹ
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
	//��ʼ�����ļ�
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

	//��ʼ����/�����ļ�
	int Start(char* szURL, HWND hShowWnd, int renderFormat,  int nRTPOverTCP, int nCache, 
		BOOL bShownToScale, int nVolume, BOOL bStatisticalInfo);
	//ֹͣ����/�����ļ�
	int Close(void);
	int InRunning();
	int Pause();
	int Play(SPEED_RATE speed);
	// ���ò����ٶ�
	int SetPlaySpeed(SPEED_RATE speed);

	//����OSD
	int SetOSD(int show, int x, int y, int color,  const char* osd);

	//��ʼ¼��
	int StartRecord(const char *filename, int duration/*¼����Ƭʱ��(min), Ϊ0���ʾ����Ƭ*/);
	int StopRecord();

	//ץͼ
	// 		filePath			- ͼƬ���·������.xxx������xxx Ŀǰֻ֧�� jpeg ��ʽ��
	// 		width, height       - ָ��ͼƬ��ߣ���� <= 0 ��Ĭ��ʹ����Ƶ���
	// 		waittime			- �Ƿ�ȴ���ͼ��� 0 - ���ȴ���>0 �ȴ���ʱ ms Ϊ��λ
	int Snapshot( char *filename,  int width, int height, int waitTime);

	//�Ƿ���
	int PlaySound(BOOL bPlay);
	//���ò�������
	int SetAudioVolume( int volume);
	//��ȡ��ǰ��������
	int GetAudioVolume();
	//��֡����
	int PlaySingleFrame();
	//����������seek(��λ�� ��)
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
	//���յ�����Ϣ
	EASY_LOCAL_SOURCE_T		m_sSourceInfo;
};


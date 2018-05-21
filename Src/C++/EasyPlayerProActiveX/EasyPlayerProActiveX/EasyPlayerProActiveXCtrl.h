#pragma once

#include "MainVideoWnd.h"
#include "EasyPlayerProManager.h"

// EasyPlayerProActiveXCtrl.h : CEasyPlayerProActiveXCtrl ActiveX 控件类的声明。

// CEasyPlayerProActiveXCtrl : 有关实现的信息，请参阅 EasyPlayerProActiveXCtrl.cpp。

class CEasyPlayerProActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEasyPlayerProActiveXCtrl)

// 构造函数
public:
	CEasyPlayerProActiveXCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnSetClientSite();

// 实现
protected:
	~CEasyPlayerProActiveXCtrl();

	BEGIN_OLEFACTORY(CEasyPlayerProActiveXCtrl)        // 类工厂和 guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR *);
	END_OLEFACTORY(CEasyPlayerProActiveXCtrl)

	DECLARE_OLETYPELIB(CEasyPlayerProActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEasyPlayerProActiveXCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CEasyPlayerProActiveXCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispiSeekFile = 12L,
		dispiPlaySingleFrame = 11L,
		dispiSetPlaySpeed = 10L,
		dispiGetAudioVolume = 9L,
		dispiSetAudioVolume = 8L,
		dispiPlaySound = 7L,
		dispiSnapshot = 6L,
		dispiStopRecord = 5L,
		dispiStartRecord = 4L,
		dispiSetOSD = 3L,
		dispidClose = 2L,
		dispidStart = 1L
	};

	//接口函数
public:
	//打开流
// 	int Start(char* szURL, HWND hShowWnd, RENDER_FORMAT renderFormat,  int nRTPOverTCP, int nCache, 
// 		BOOL bShownToScale, BOOL bPlaySound, BOOL bStatisticalInfo);
// 	//关闭流
// 	int Close(void);
// 	int InRunning();
// 
// 	//设置OSD
// 	int SetOSD(int show, const char* osd);
// 
// 	//录像
// 	int StartRecord(const char *foldername, 
// 		const char *filename, 
// 		unsigned int filesize/*录像文件大小 MB*/, int duration/*录像时长(second)*/,  
// 		unsigned char preRecording/*0x01:预录  0x00:不预录*/);
// 	int StopRecord();
// 
// 	//抓图
// 	int Snapshot( 
// 		char *filename, unsigned char sync=0/*0:异步: 1:同步*/, 
// 		unsigned char useQueue=0/*1:使用队列 0:不使用队列*/);
// 
// 	//声音播放和控制
// 	int PlaySound(BOOL bPlay);
// 	int SetAudioVolume( int volume);
// 	int GetAudioVolume();
// 
// 	//播放控制
// 	// 设置播放速度(文件)
// 	int SetPlaySpeed(PLAY_SPEED_ENUM speed);
// 	//单帧播放, 可调用libEasyPlayerPro_SetPlaySpeed切换回正常播放模式
// 	int PlaySingleFrame();
// 	//跳转到指定时间播放(文件)
// 	int SeekFile( unsigned int playTimeSecs/*秒*/ );

	LONG Start(LPCTSTR sURL, LPCTSTR sRenderFormat, LPCTSTR sRTPOverTCP, LPCTSTR sCache, 
		LPCTSTR sShownToScale, LPCTSTR sPlaySound, LPCTSTR sStatisticalInfo);
	void Close(void);
	void SetOSD(LPCTSTR show, LPCTSTR osd);

	//录像
	LONG StartRecord(LPCTSTR sFoldername, LPCTSTR sFilename, 
		LPCTSTR sFilesize/*录像文件大小 MB*/, LPCTSTR sDuration/*录像时长(second)*/,  
		LPCTSTR sPreRecording/*0x01:预录  0x00:不预录*/);
	LONG StopRecord();

	//抓图
	LONG Snapshot( LPCTSTR sFilename);

	//声音播放和控制
	LONG PlaySound(LPCTSTR sbPlay);
	LONG SetAudioVolume( LPCTSTR sVolume);
	LONG GetAudioVolume();

	//播放控制
	// 设置播放速度(文件)
	LONG SetPlaySpeed(LPCTSTR sSpeed);
	//单帧播放, 可调用libEasyPlayerPro_SetPlaySpeed切换回正常播放模式
	LONG PlaySingleFrame();
	//跳转到指定时间播放(文件)
	LONG SeekFile( LPCTSTR sPlayTimeSecs/*秒*/ );

private:
	CMainVideoWnd m_pActiveDlg; 
	EasyPlayerProManager m_player;

	//配置参数
	char m_szURL[512] ;
	RENDER_FORMAT m_eRenderFormat;
	int  m_nRTPOverTCP ;
	int	   m_nFrameCache ;
	BOOL m_bPlaySound ;
	BOOL m_bShowToScale ;
	BOOL m_bShowStatisticInfo ;

};


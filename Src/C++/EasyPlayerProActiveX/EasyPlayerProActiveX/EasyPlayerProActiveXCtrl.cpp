// EasyPlayerProActiveXCtrl.cpp : CEasyPlayerProActiveXCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "EasyPlayerProActiveX.h"
#include "EasyPlayerProActiveXCtrl.h"
#include "EasyPlayerProActiveXPropPage.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEasyPlayerProActiveXCtrl, COleControl)

// 消息映射

BEGIN_MESSAGE_MAP(CEasyPlayerProActiveXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)

	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_DESTROY()

END_MESSAGE_MAP()



// 调度映射

BEGIN_DISPATCH_MAP(CEasyPlayerProActiveXCtrl, COleControl)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "Start", dispidStart, Start, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "Close", dispidClose, Close, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "SetOSD", dispiSetOSD, SetOSD, VT_EMPTY, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "StartRecord", dispiStartRecord, StartRecord, VT_I4, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "StopRecord", dispiStopRecord, StopRecord, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "Snapshot", dispiSnapshot, Snapshot, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "PlaySound", dispiPlaySound, PlaySound, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "SetAudioVolume", dispiSetAudioVolume, SetAudioVolume, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "GetAudioVolume", dispiGetAudioVolume, GetAudioVolume, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "SetPlaySpeed", dispiSetPlaySpeed, SetPlaySpeed, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "PlaySingleFrame", dispiPlaySingleFrame, PlaySingleFrame, VT_I4, VTS_NONE)
	DISP_FUNCTION_ID(CEasyPlayerProActiveXCtrl, "SeekFile", dispiSeekFile, SeekFile, VT_I4, VTS_BSTR)
END_DISPATCH_MAP()



// 事件映射

BEGIN_EVENT_MAP(CEasyPlayerProActiveXCtrl, COleControl)
END_EVENT_MAP()



// 属性页

// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CEasyPlayerProActiveXCtrl, 1)
	PROPPAGEID(CEasyPlayerProActiveXPropPage::guid)
END_PROPPAGEIDS(CEasyPlayerProActiveXCtrl)



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CEasyPlayerProActiveXCtrl, "EASYPLAYERPROACT.EasyPlayerProActCtrl.1",
	0xc826a1ce, 0x34e6, 0x4bb1, 0xb8, 0x44, 0x68, 0x1e, 0x7a, 0xc9, 0x8d, 0x9a)



// 键入库 ID 和版本

IMPLEMENT_OLETYPELIB(CEasyPlayerProActiveXCtrl, _tlid, _wVerMajor, _wVerMinor)



// 接口 ID

const IID IID_DEasyPlayerProActiveX = { 0x4FEB3DC3, 0x9794, 0x4E94, { 0xA9, 0x28, 0x5, 0xE0, 0x2B, 0xAD, 0xE8, 0x55 } };
const IID IID_DEasyPlayerProActiveXEvents = { 0x194E1B18, 0x4C63, 0x4155, { 0x97, 0x83, 0xEB, 0x38, 0x3F, 0x95, 0xDF, 0xFD } };


// 控件类型信息

static const DWORD _dwEasyPlayerProActiveXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEasyPlayerProActiveXCtrl, IDS_EASYPLAYERPROACTIVEX, _dwEasyPlayerProActiveXOleMisc)



// CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrlFactory::UpdateRegistry -
// 添加或移除 CEasyPlayerProActiveXCtrl 的系统注册表项

BOOL CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EASYPLAYERPROACTIVEX,
			IDB_EASYPLAYERPROACTIVEX,
			afxRegApartmentThreading,
			_dwEasyPlayerProActiveXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}



// 授权字符串

static const TCHAR _szLicFileName[] = _T("EasyPlayerProActiveX.lic");

static const WCHAR _szLicString[] = L"Copyright (c) 2018 ";


// CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrlFactory::VerifyUserLicense -
// 检查是否存在用户许可证

BOOL CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


// CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrlFactory::GetLicenseKey -
// 返回运行时授权密钥

BOOL CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR *pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


// CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrl - 构造函数

CEasyPlayerProActiveXCtrl::CEasyPlayerProActiveXCtrl()
{
	InitializeIIDs(&IID_DEasyPlayerProActiveX, &IID_DEasyPlayerProActiveXEvents);
	// TODO: 在此初始化控件的实例数据。
	memset(m_szURL, 0x00, 512);
	m_eRenderFormat = RENDER_FORMAT_YV12;
	m_nRTPOverTCP = 1;
	m_nFrameCache = 3;
	m_bPlaySound = TRUE;
	m_bShowToScale = FALSE;
	m_bShowStatisticInfo = TRUE;
	EasyPlayerProManager::Init();
}

// CEasyPlayerProActiveXCtrl::~CEasyPlayerProActiveXCtrl - 析构函数

CEasyPlayerProActiveXCtrl::~CEasyPlayerProActiveXCtrl()
{
	// TODO: 在此清理控件的实例数据。
}

// CEasyPlayerProActiveXCtrl::OnDraw - 绘图函数

void CEasyPlayerProActiveXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	// TODO: 用您自己的绘图代码替换下面的代码。
	// 	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	// 	pdc->Ellipse(rcBounds);
	// 	
	DoSuperclassPaint(pdc, rcBounds);

	//if (!m_pActiveDlg.IsFullScreen())
	{
		m_pActiveDlg.MoveWindow(rcBounds, TRUE);
	}

	CBrush brBackGnd(TranslateColor(AmbientBackColor()));
	pdc->FillRect(rcBounds, &brBackGnd);
}



// CEasyPlayerProActiveXCtrl::DoPropExchange - 持久性支持

void CEasyPlayerProActiveXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}


// CEasyPlayerProActiveXCtrl::OnResetState - 将控件重置为默认状态

void CEasyPlayerProActiveXCtrl::OnResetState()
{
	if (m_pClientSite) 
	{
		int ret = EasyPlayerProManager::Init();
#if 1
		CString str = _T("");
		str.Format(_T("Init = %d"), ret);
		AfxMessageBox(str);
#endif
		//父窗口及其大小并不重要，因为控件在本地激活时会自动重画和重新定位。
		VERIFY (CreateControlWindow (::GetDesktopWindow(), CRect(0,0,0,0), CRect(0,0,0,0)));
		//m_bInit = true;
	}
	else
	{
		Close();
		// 调用刷新会报错 [10/12/2017 dingshuai]
		EasyPlayerProManager::UnInit();
		AfxMessageBox(_T("页面已经关闭，重新加载OCX"));
		DestroyWindow();
		//m_bInit = false;

	}
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

	// TODO: 在此重置任意其他控件状态。
}

void CEasyPlayerProActiveXCtrl::OnSetClientSite()
{
	if (m_pClientSite) 
	{
		int ret = EasyPlayerProManager::Init();
#if 1
		CString str = _T("");
		str.Format(_T("Init = %d"), ret);
		AfxMessageBox(str);
#endif
		//父窗口及其大小并不重要，因为控件在本地激活时会自动重画和重新定位。
		VERIFY (CreateControlWindow (::GetDesktopWindow(), CRect(0,0,0,0), CRect(0,0,0,0)));
		//m_bInit = true;
	}
	else
	{
		Close();
		// 调用刷新会报错 [10/12/2017 dingshuai]
		EasyPlayerProManager::UnInit();
		AfxMessageBox(_T("页面已经关闭，重新加载OCX"));
		DestroyWindow();
		//m_bInit = false;

	}
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

}


// CEasyPlayerProActiveXCtrl::AboutBox - 向用户显示“关于”框

void CEasyPlayerProActiveXCtrl::AboutBox()
{
	CDialogEx dlgAbout(IDD_ABOUTBOX_EASYPLAYERPROACTIVEX);
	dlgAbout.DoModal();
}


// CEasyPlayerProActiveXCtrl 消息处理程序
int CEasyPlayerProActiveXCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	// OCX内置窗口必须以OCX控件为父类窗口的子窗口，否则界面显示会有问题 [4/14/2014-10:12:38 Dingshuai]
	m_pActiveDlg.Create(CMainVideoWnd::IDD, this);
	return 0;
}


void CEasyPlayerProActiveXCtrl::OnDestroy()
{
	COleControl::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	m_pActiveDlg.DestroyWindow();
}

LONG CEasyPlayerProActiveXCtrl::Start(LPCTSTR sURL, LPCTSTR sRenderFormat, 
	LPCTSTR sRTPOverTCP, LPCTSTR sCache, 
	LPCTSTR sShownToScale, LPCTSTR sPlaySound, LPCTSTR sStatisticalInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: 在此添加调度处理程序代码
	int nRet = 0;
	char szRenderFormat[128] ;
	char szRTPOverTCP[128] ;
	char szCache[128] ;
	char szShownToScale[128] ;
	char szPlaySound[128] ;
	char szStatisticalInfo[128] ;
	if (wcslen(sURL) < 1)		
		return -1;
	__WCharToMByte(sURL, m_szURL, sizeof(m_szURL)/sizeof(m_szURL[0]));
	if (wcslen(sRenderFormat) > 0)
	{
		__WCharToMByte(sRenderFormat, szRenderFormat, sizeof(szRenderFormat)/sizeof(szRenderFormat[0]));
	}
	if (wcslen(sRTPOverTCP) > 0)
	{
		__WCharToMByte(sRTPOverTCP, szRTPOverTCP, sizeof(szRTPOverTCP)/sizeof(szRTPOverTCP[0]));
		m_nRTPOverTCP = atoi(szRTPOverTCP);
	}
	if (wcslen(sCache) > 0)
	{
		__WCharToMByte(sCache, szCache, sizeof(szCache)/sizeof(szCache[0]));
		m_nFrameCache = atoi(szCache);
	}
	if (wcslen(sPlaySound) > 0)
	{
		__WCharToMByte(sPlaySound, szPlaySound, sizeof(szPlaySound)/sizeof(szPlaySound[0]));
		m_bPlaySound = atoi(szPlaySound);
	}
	if (wcslen(sShownToScale) > 0)
	{
		__WCharToMByte(sShownToScale, szShownToScale, sizeof(szShownToScale)/sizeof(szShownToScale[0]));
		m_bShowToScale = atoi(szShownToScale);
	}
	if (wcslen(sStatisticalInfo) > 0)
	{
		__WCharToMByte(sStatisticalInfo, szStatisticalInfo, sizeof(szStatisticalInfo)/sizeof(szStatisticalInfo[0]));
		m_bShowStatisticInfo = atoi(szStatisticalInfo);
	}

	int nRenderType = atoi(szRenderFormat);
	m_eRenderFormat = RENDER_FORMAT_YV12;
	switch (nRenderType)
	{
	case 0:
		m_eRenderFormat =  RENDER_FORMAT_YV12;
		break;				    
	case 1:					    
		m_eRenderFormat =  RENDER_FORMAT_YUY2;
		break;				    
	case 2:					    
		m_eRenderFormat =  RENDER_FORMAT_UYVY;
		break;				    
	case 3:					    
		m_eRenderFormat =  RENDER_FORMAT_A8R8G8B8;
		break;				    
	case 4:					    
		m_eRenderFormat =  RENDER_FORMAT_X8R8G8B8;
		break;				    
	case 5:					    
		m_eRenderFormat =  RENDER_FORMAT_RGB565;
		break;				    
	case 6:					    
		m_eRenderFormat =  RENDER_FORMAT_RGB555;
		break;				    
	case 7:					    
		m_eRenderFormat =  RENDER_FORMAT_RGB24_GDI;
		break;
	}

	nRet = m_player.Start(m_szURL, m_pActiveDlg.GetSafeHwnd(), m_eRenderFormat , m_nRTPOverTCP, 
		m_nFrameCache, m_bShowToScale, m_bPlaySound, m_bShowStatisticInfo);
	return nRet;
}
void CEasyPlayerProActiveXCtrl::Close(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_player.Close();
}
void CEasyPlayerProActiveXCtrl::SetOSD(LPCTSTR show, LPCTSTR osd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int nRet = 0;
	char szShow[128] = {0,};
	char szOsd[512]  = {0,};
	int nShow = 0;

	if (wcslen(show) > 0)
	{
		__WCharToMByte(show, szShow, sizeof(szShow)/sizeof(szShow[0]));
		nShow = atoi(szShow);
	}
	if (wcslen(osd) > 0)
	{
		__WCharToMByte(osd, szOsd, sizeof(szOsd)/sizeof(szOsd[0]));
	}
	m_player.SetOSD(nShow, szOsd);
}

//录像
LONG CEasyPlayerProActiveXCtrl::StartRecord(LPCTSTR sFoldername, LPCTSTR sFilename, 
	LPCTSTR sFilesize/*录像文件大小 MB*/, LPCTSTR sDuration/*录像时长(second)*/,  
	LPCTSTR sPreRecording/*0x01:预录  0x00:不预录*/)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char szFoldername[512] ;
	char szFilename[128] ;
	char szFilesize[128] ;
	char szDuration[128] ;
	char szPreRecording[128] ;
	int nFileSize = 0 ;
	int nDuration = 0 ;
	BOOL bPreRecording =FALSE;
	if (wcslen(sFoldername) > 0)
	{
		__WCharToMByte(sFoldername, szFoldername, sizeof(szFoldername)/sizeof(szFoldername[0]));
	}
	if (wcslen(sFilename) > 0)
	{
		__WCharToMByte(sFilename, szFilename, sizeof(szFilename)/sizeof(szFilename[0]));
	}

	if (wcslen(sFilesize) > 0)
	{
		__WCharToMByte(sFilesize, szFilesize, sizeof(szFilesize)/sizeof(szFilesize[0]));
		nFileSize = atoi(szFilesize);
	}
	if (wcslen(sDuration) > 0)
	{
		__WCharToMByte(sDuration, szDuration, sizeof(szDuration)/sizeof(szDuration[0]));
		nDuration = atoi(szDuration);
	}
	if (wcslen(sPreRecording) > 0)
	{
		__WCharToMByte(sPreRecording, szPreRecording, sizeof(szPreRecording)/sizeof(szPreRecording[0]));
		bPreRecording = atoi(szPreRecording);
	}
	return m_player.StartRecord(szFoldername,szFilename, nFileSize, nDuration,bPreRecording );
}
LONG CEasyPlayerProActiveXCtrl::StopRecord()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_player.StopRecord();
}

//抓图
LONG CEasyPlayerProActiveXCtrl::Snapshot( LPCTSTR sFilename)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char szFilename[512]  = {0,};
	if (wcslen(sFilename) > 0)
	{
		__WCharToMByte(sFilename, szFilename, sizeof(szFilename)/sizeof(szFilename[0]));
	}
	return m_player.Snapshot(szFilename);
}

//声音播放和控制
LONG CEasyPlayerProActiveXCtrl::PlaySound(LPCTSTR sbPlay)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char szbPlay[128]  = {0,};
	BOOL bPlay = FALSE;
	if (wcslen(sbPlay) > 0)
	{
		__WCharToMByte(sbPlay, szbPlay, sizeof(szbPlay)/sizeof(szbPlay[0]));
		bPlay = atoi(szbPlay);
	}
	return m_player.PlaySound(bPlay);

}

LONG CEasyPlayerProActiveXCtrl::SetAudioVolume( LPCTSTR sVolume)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char szVolume[128]  = {0,};
	int volume = 0;
	if (wcslen(sVolume) > 0)
	{
		__WCharToMByte(sVolume, szVolume, sizeof(szVolume)/sizeof(szVolume[0]));
		volume = atoi(szVolume);
	}
	return m_player.SetAudioVolume(volume);
}
LONG CEasyPlayerProActiveXCtrl::GetAudioVolume(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_player.GetAudioVolume();
}

//播放控制
// 设置播放速度(文件)
LONG CEasyPlayerProActiveXCtrl::SetPlaySpeed(LPCTSTR sSpeed)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char szSpeed[128]  = {0,};
	int speed = 0;
	if (wcslen(sSpeed) > 0)
	{
		__WCharToMByte(sSpeed, szSpeed, sizeof(szSpeed)/sizeof(szSpeed[0]));
		speed = atoi(szSpeed);
	}
	return m_player.SetPlaySpeed((PLAY_SPEED_ENUM)speed);

}
//单帧播放, 可调用libEasyPlayerPro_SetPlaySpeed切换回正常播放模式
LONG CEasyPlayerProActiveXCtrl::PlaySingleFrame()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return m_player.PlaySingleFrame();
}
//跳转到指定时间播放(文件)
LONG CEasyPlayerProActiveXCtrl::SeekFile( LPCTSTR sPlayTimeSecs/*秒*/ )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char szPlayTimeSecs[128]  = {0,};
	int playTimeSecs = 0;
	if (wcslen(sPlayTimeSecs) > 0)
	{
		__WCharToMByte(sPlayTimeSecs, szPlayTimeSecs, sizeof(szPlayTimeSecs)/sizeof(szPlayTimeSecs[0]));
		playTimeSecs = atoi(szPlayTimeSecs);
	}
	return m_player.SeekFile(playTimeSecs);
}
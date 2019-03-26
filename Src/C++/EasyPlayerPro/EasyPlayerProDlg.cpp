#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "EasyPlayerProDlg.h"
#include "afxdialogex.h"
#include "DlgAbout.h"
#include "xmlConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _WIN64
	#pragma comment(lib, "../libEasyPlayerPro/x64/libEasyPlayerPro.lib")
#else
	#pragma comment(lib, "../libEasyPlayerPro/x86/libEasyPlayerPro.lib")
#endif
#pragma comment (lib, "Version.lib")
wchar_t wszApplicationVersion[64] = {0};
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLivePlayerDlg 对话框

CLivePlayerDlg::CLivePlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLivePlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nVolume = 0;
	InitialComponents();
}

void CLivePlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLivePlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_WINDOW_MAXIMIZED, OnWindowMaximized)
	ON_MESSAGE(WM_EXIT_FULLSCREEN, OnExitFullScreen)
	ON_CBN_SELCHANGE(IDC_COMBO_SPLIT_SCREEN, &CLivePlayerDlg::OnCbnSelchangeComboSplitScreen)
	ON_CBN_SELCHANGE(IDC_COMBO_RENDER_FORMAT, &CLivePlayerDlg::OnCbnSelchangeComboRenderFormat)
	ON_BN_CLICKED(IDC_CHECK_SHOWNTOSCALE, &CLivePlayerDlg::OnBnClickedCheckShowntoscale)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_CHECKMULTIPLEX, &CLivePlayerDlg::OnBnClickedCheckmultiplex)
	ON_BN_CLICKED(IDC_CHECK_FULLSCREEN, &CLivePlayerDlg::OnBnClickedCheckFullscreen)
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()

	ON_WM_SIZE()
END_MESSAGE_MAP()


// CLivePlayerDlg 消息处理程序

BOOL CLivePlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
									
	// TODO: 在此添加额外的初始化代码
	SetBackgroundColor(RGB(0x5b,0x5b,0x5b));
	MoveWindow(0, 0, 1200, 640);

	CreateComponents();

	XMLConfig		xmlConfig;
	memset(&proConfig, 0x00, sizeof(PRO_CONFIG_T));
	xmlConfig.LoadConfig(XML_CONFIG_FILENAME, &proConfig);

	if (NULL!=pVideoWindow)		pVideoWindow->channels		=	proConfig.splitWindow;
	if (NULL != pComboxSplitScreen)
	{
		if (4 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(0);
		else if (8 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(1);
		else if (9 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(2);
		else if (16 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(3);
	}

	if (NULL!=pChkShownToScale)		pChkShownToScale->SetCheck(proConfig.scale);
	if (NULL!=pChkMultiplex)		pChkMultiplex->SetCheck(proConfig.multiple);
	if (NULL!=pChkFullScreen)		pChkFullScreen->SetCheck(proConfig.fullScreen);
	if (proConfig.fullScreen==0x01)
	{
		FullScreen();
	}

	if (NULL != pVideoWindow && NULL!=pVideoWindow->pDlgVideo)
	{
		const char url_header[4][16] = {"rtsp://", "rtmp://", "http://", "file://"};
		int idx = 0;
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			pVideoWindow->pDlgVideo[i].SetURL((char *)url_header[idx++], 0, 1, 1, 1, 3, 1, 0);

			if (idx>=4)	idx = 0;
		}

		int cfg_channel_num = sizeof(proConfig.channel)/sizeof(proConfig.channel[0]);
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (i>=cfg_channel_num)		break;

			if ( (int)strlen(proConfig.channel[i].url) < 10)		continue;

			pVideoWindow->pDlgVideo[i].SetURL(proConfig.channel[i].url, 
				proConfig.scale, proConfig.channel[i].showOSD, 
				proConfig.channel[i].protocol, proConfig.multiple, 
				proConfig.channel[i].cache, proConfig.channel[i].showToolbar,
				proConfig.channel[i].autoPlay);
		}
		/*
		FILE *f = fopen("url.txt", "rb");
		if (NULL != f)
		{
			int idx = 0;
			char szURL[128] = {0};
			while (! feof(f) && idx+1<_SURV_MAX_WINDOW_NUM)
			{
				memset(szURL, 0x00, sizeof(szURL));
				fgets(szURL, sizeof(szURL), f);

				if (0 != strcmp(szURL, "\0"))
				{
					pVideoWindow->pDlgVideo[idx++].SetURL(szURL);
				}
			}
		}
		*/
	}

	OnCbnSelchangeComboRenderFormat();

    int ret = EasyPlayerPro_Authorize("64687538665969576B5A754161356C636F3261554A65354659584E35554778686557567955484A764C6D56345A56634D5671442F7065424859585A7062695A4359574A76633246414D6A41784E6B566863336C4559584A33615735555A5746745A57467A65513D3D");
    if(ret <= 0)
    {
        MessageBox(TEXT("激活码不合法或已过期！"), TEXT("OK"), MB_OK);
    }

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLivePlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
#if 0
		CAboutDlg dlgAbout;
		CWnd *pWnd = dlgAbout.GetDlgItem(IDC_STATIC_VER);
		if (NULL != pWnd)
		{
			pWnd->SetWindowTextW(wszApplicationVersion);
		}
		dlgAbout.DoModal();
#else
		CDlgAbout	dlgAbout(wszApplicationVersion);
		dlgAbout.DoModal();
#endif
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLivePlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLivePlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CLivePlayerDlg::DestroyWindow()
{
	DeleteComponents();

	return CDialogEx::DestroyWindow();
}


LRESULT CLivePlayerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_PAINT == message || WM_SIZE==message)
	{
		UpdateComponents();
	}
	
	return CDialogEx::WindowProc(message, wParam, lParam);
}

void	CLivePlayerDlg::InitialComponents()
{
	pComboxSplitScreen	=	NULL;
	pComboxRenderFormat	=	NULL;
	pVideoWindow		=	NULL;
	pChkShownToScale	=	NULL;
	pChkMultiplex		=	NULL;
	pChkFullScreen		=	NULL;
	pStaticVolume		=	NULL;
	pSliderCtrlVolume	=	NULL;
	pStaticCopyright	=	NULL;

	//RenderFormat	=	RENDER_FORMAT_RGB24_GDI;//RGB565
	m_BrushStatic = ::CreateSolidBrush(RGB(0x5b,0x5b,0x5b));

}

void	CLivePlayerDlg::CreateComponents()
{
	__CREATE_WINDOW(pComboxSplitScreen, CComboBox,		IDC_COMBO_SPLIT_SCREEN);
	__CREATE_WINDOW(pComboxRenderFormat, CComboBox,		IDC_COMBO_RENDER_FORMAT);
	__CREATE_WINDOW(pChkShownToScale, CButton,		IDC_CHECK_SHOWNTOSCALE);
	__CREATE_WINDOW(pChkMultiplex, CButton,		IDC_CHECKMULTIPLEX);
	__CREATE_WINDOW(pChkFullScreen, CButton,		IDC_CHECK_FULLSCREEN);
	__CREATE_WINDOW(pStaticVolume, CStatic,		IDC_STATIC_VOLUME);
	__CREATE_WINDOW(pSliderCtrlVolume, CSliderCtrl,		IDC_SLIDER_VOLUME);
	
	__CREATE_WINDOW(pStaticCopyright, CStatic,		IDC_STATIC_COPYRIGHT);

	pStaticCopyright->ShowWindow(FALSE);
	GetApplicationVersion(wszApplicationVersion);
	SetWindowText(wszApplicationVersion);

	if (NULL != pChkShownToScale)		pChkShownToScale->SetWindowText(TEXT("按比例显示"));
	if (NULL != pChkMultiplex)			pChkMultiplex->SetWindowText(TEXT("复用源"));
	if (NULL != pChkFullScreen)			pChkFullScreen->SetWindowText(TEXT("全屏"));
	if (NULL != pSliderCtrlVolume)	
	{
		pSliderCtrlVolume->SetRange(0, 255);
		pSliderCtrlVolume->SetPos(182);
		m_nVolume = 0;
	}

	if (NULL == pVideoWindow)
	{
		pVideoWindow = new VIDEO_NODE_T;
		pVideoWindow->fullscreen    = false;
		pVideoWindow->maximizedId	=	-1;
		pVideoWindow->selectedId	=	-1;
		pVideoWindow->channels		=	4;
		if (pVideoWindow->channels>_SURV_MAX_WINDOW_NUM)	pVideoWindow->channels=_SURV_MAX_WINDOW_NUM;
		pVideoWindow->pDlgVideo	=	new CDlgVideo[_SURV_MAX_WINDOW_NUM];//gAppInfo.maxchannels
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			pVideoWindow->pDlgVideo[i].SetWindowId(i);
			pVideoWindow->pDlgVideo[i].SetMainDlg(this);
			pVideoWindow->pDlgVideo[i].Create(IDD_DIALOG_VIDEO, this);
			pVideoWindow->pDlgVideo[i].ShowWindow(SW_HIDE);
		}
	}

	if (NULL != pComboxSplitScreen)
	{
		pComboxSplitScreen->AddString(TEXT("4画面"));
		pComboxSplitScreen->AddString(TEXT("8画面"));
		pComboxSplitScreen->AddString(TEXT("9画面"));
		pComboxSplitScreen->AddString(TEXT("16画面"));
		//pComboxSplitScreen->AddString(TEXT("36画面"));
		//pComboxSplitScreen->AddString(TEXT("64画面"));
		pComboxSplitScreen->SetCurSel(0);
	}
	if (NULL != pComboxRenderFormat)
	{
		pComboxRenderFormat->AddString(TEXT("YV12"));
		pComboxRenderFormat->AddString(TEXT("YUY2"));
		pComboxRenderFormat->AddString(TEXT("RGB565"));
		pComboxRenderFormat->AddString(TEXT("X8R8G8B8"));
		pComboxRenderFormat->AddString(TEXT("GDI"));

		pComboxRenderFormat->SetCurSel(4);
	}
}

void	CLivePlayerDlg::UpdateComponents()
{
	CRect	rcClient;
	GetClientRect(&rcClient);
	if (rcClient.IsRectEmpty())		return;

	CRect	rcVideo;
	rcVideo.SetRect(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom-(proConfig.fullScreen?0:30));
	UpdateVideoPosition(&rcVideo);

	CRect	rcSplitScreen;
	rcSplitScreen.SetRect(rcClient.left+5, rcVideo.bottom+3, rcClient.left+100, rcVideo.bottom+3+90);
	__MOVE_WINDOW(pComboxSplitScreen, rcSplitScreen);

	CRect	rcRenderFormat;
	rcRenderFormat.SetRect(rcSplitScreen.right+5, rcSplitScreen.top, rcSplitScreen.right+5+100, rcSplitScreen.bottom);
	__MOVE_WINDOW(pComboxRenderFormat, rcRenderFormat);

	CRect	rcShownToScale;
	rcShownToScale.SetRect(rcRenderFormat.right+10, rcRenderFormat.top, rcRenderFormat.right+10+110, rcRenderFormat.top+30);
	__MOVE_WINDOW(pChkShownToScale, rcShownToScale);

	CRect	rcMultiplex;
	rcMultiplex.SetRect(rcShownToScale.right+10, rcShownToScale.top, rcShownToScale.right+10+70, rcShownToScale.bottom);
	__MOVE_WINDOW(pChkMultiplex, rcMultiplex);

	CRect	rcFullScreen;
	rcFullScreen.SetRect(rcMultiplex.right+10, rcMultiplex.top, rcMultiplex.right+10+70, rcMultiplex.bottom);
	__MOVE_WINDOW(pChkFullScreen, rcFullScreen);
	
	CRect	rcVolume;
	rcVolume.SetRect(rcFullScreen.right+10, rcFullScreen.top+5, rcFullScreen.right+10+35, rcFullScreen.bottom);
	__MOVE_WINDOW(pStaticVolume, rcVolume);
	rcVolume.SetRect(rcVolume.right+2, rcVolume.top, rcVolume.right+2+160, rcVolume.bottom-3);
	__MOVE_WINDOW(pSliderCtrlVolume, rcVolume);


	CRect	rcCopyright;
	rcCopyright.SetRect(rcClient.right-200, rcSplitScreen.top+5, rcClient.right-2, rcClient.bottom);
	__MOVE_WINDOW(pStaticCopyright, rcCopyright);
}
void	CLivePlayerDlg::DeleteComponents()
{
	if (NULL != pVideoWindow)
	{
		if (NULL != pVideoWindow->pDlgVideo)
		{
			for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
			{
				pVideoWindow->pDlgVideo[i].DestroyWindow();
			}
			delete []pVideoWindow->pDlgVideo;
			pVideoWindow->pDlgVideo = NULL;
		}
		delete pVideoWindow;
		pVideoWindow = NULL;
	}

	DeleteObject(m_BrushStatic);
}


void	CLivePlayerDlg::UpdateVideoPosition(LPRECT lpRect)
{
	CRect rcClient;
	if (NULL == lpRect)
	{
		GetClientRect(&rcClient);
		lpRect = &rcClient;
	}

	if (NULL == pVideoWindow)		return;

	//CRect rcClient;
	rcClient.CopyRect(lpRect);

	CRect rcTmp;
	rcTmp.SetRect(rcClient.left, rcClient.top, rcClient.left+rcClient.Width()/2, rcClient.top+rcClient.Height()/2);

	//

	if (pVideoWindow->maximizedId==-1)
	{
		int nTimes = 2;
		int nLeft = lpRect->left;
		int nTop  = lpRect->top;

		for (int i=pVideoWindow->channels; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (pVideoWindow->pDlgVideo[i].IsWindowVisible())
				pVideoWindow->pDlgVideo[i].ShowWindow(SW_HIDE);
		}

		switch (pVideoWindow->channels)
		{
		case 4:
		case 9:
		case 16:
		case 25:
		case 36:
		case 64:
		default:
			{
				nTimes = 2;
				if (pVideoWindow->channels == 4)		nTimes	=	2;
				if (pVideoWindow->channels == 9)		nTimes	=	3;
				if (pVideoWindow->channels == 16)		nTimes	=	4;
				if (pVideoWindow->channels == 25)		nTimes	=	5;
				if (pVideoWindow->channels == 36)		nTimes	=	6;
				if (pVideoWindow->channels == 64)		nTimes	=	8;

				RECT rcTmp;
				SetRectEmpty(&rcTmp);

				int n = 0;//videoPatrol.patrolStartId;
				for (int i = 0; i < nTimes; i++)
				{
					for (int j = 0; j < nTimes; j ++)
					{
						//SetRect(&rcTmp, nLeft, nTop, nLeft + imgSize.cx / nTimes, nTop + imgSize.cy / nTimes);
						SetRect(&rcTmp, nLeft, nTop, nLeft + rcClient.Width() / nTimes, nTop + rcClient.Height() / nTimes);
						//CopyRect(&vidRenderHandle[n].drawvid.rect, &rcTmp);

						if (j+1==nTimes && rcTmp.right<rcClient.right)
						{
							rcTmp.right = rcClient.right;
						}
						if (i+1==nTimes && rcTmp.bottom<rcClient.bottom)
						{
							rcTmp.bottom = rcClient.bottom;
						}


						pVideoWindow->pDlgVideo[n].MoveWindow(&rcTmp);
						if (! pVideoWindow->pDlgVideo[n].IsWindowVisible())
						{
							pVideoWindow->pDlgVideo[n].ShowWindow(SW_SHOW);
						}


						n ++;

						nLeft += rcClient.Width() / nTimes;
					}
					nLeft = rcClient.left;
					nTop  += (rcClient.Height()) / nTimes;
				}
			}
			break;
		case 6:		//6·??á
			{
				int nWidth = rcClient.Width() / 3;
				int nHeight= rcClient.Height()/ 3;

				int nRight = 0;
				int nBottom= 0;
				if (rcClient.right > nWidth*3)	nRight = rcClient.Width()-nWidth*3;
				if (rcClient.bottom> nHeight*3)	nBottom= rcClient.Height()-nHeight*3;
			
				nLeft = rcClient.left;
				nTop  = rcClient.top+nHeight*2;
				for (int i=3; i<6; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (i+1==6)			rcTmp.right += nRight;
					if (nBottom > 0)	rcTmp.bottom += nBottom;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
						pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);
				
					nLeft += nWidth;
				}
				nLeft -= nWidth;
				nTop  = rcClient.top;
				for (int i=1; i<3; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (nRight>0)	rcTmp.right += nRight;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
						pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);
					nTop += nHeight;
				}
			
				rcTmp.SetRect(rcClient.left, rcClient.top, rcTmp.left, rcTmp.bottom);
				pVideoWindow->pDlgVideo[0].MoveWindow(&rcTmp);
				if (! pVideoWindow->pDlgVideo[0].IsWindowVisible())
					pVideoWindow->pDlgVideo[0].ShowWindow(SW_SHOW);
			}
			break;
		case 8:		//8分屏
			{

				int nWidth = rcClient.Width() / 4;
				int nHeight= rcClient.Height()/ 4;

				int nRight = 0;
				int nBottom= 0;
				if (rcClient.right > nWidth*4)	nRight = rcClient.Width()-nWidth*4;
				if (rcClient.bottom> nHeight*4)	nBottom= rcClient.Height()-nHeight*4;

				nLeft = rcClient.left;
				nTop  = rcClient.top+nHeight*3;
				for (int i=4; i<8; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (i+1==8)			rcTmp.right += nRight;
					if (nBottom > 0)	rcTmp.bottom += nBottom;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
							pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);

					nLeft += nWidth;
				}
				nLeft -= nWidth;
				nTop  = rcClient.top;
				for (int i=1; i<4; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (nRight>0)	rcTmp.right += nRight;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
						pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);
					nTop += nHeight;
				}

				rcTmp.SetRect(rcClient.left, rcClient.top, rcTmp.left, rcTmp.bottom);
				pVideoWindow->pDlgVideo[0].MoveWindow(&rcTmp);
				if (! pVideoWindow->pDlgVideo[0].IsWindowVisible())
					pVideoWindow->pDlgVideo[0].ShowWindow(SW_SHOW);

			}
			break;
		}

		for (int vid=0; vid<_SURV_MAX_WINDOW_NUM; vid++)
		{
			//pVideoWindow->pDlgVideo[vid].SetSelectedChannel(pVideoWindow->selectedId==vid);
		}
	}
	else
	{
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (pVideoWindow->pDlgVideo[i].IsWindowVisible() && i!=pVideoWindow->maximizedId)
			{
				pVideoWindow->pDlgVideo[i].ShowWindow(SW_HIDE);
			}
		}
		rcTmp.SetRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
		pVideoWindow->pDlgVideo[pVideoWindow->maximizedId].MoveWindow(&rcTmp);
		pVideoWindow->pDlgVideo[pVideoWindow->maximizedId].ShowWindow(SW_SHOW);
	}
}



LRESULT CLivePlayerDlg::OnWindowMaximized(WPARAM wParam, LPARAM lParam)
{
	int nCh = (int)wParam;

	if (pVideoWindow->maximizedId == -1)
	{
		pVideoWindow->maximizedId = nCh;
	}
	else
	{
		pVideoWindow->maximizedId = -1;
	}
	UpdateComponents();

	return 0;
}




void CLivePlayerDlg::OnCbnSelchangeComboSplitScreen()
{
	if (NULL == pVideoWindow)		return;

	int nSplitWindow = 4;
	int nIdx = pComboxSplitScreen->GetCurSel();
	if (nIdx == 0)	nSplitWindow = 4;
	else if (nIdx == 1)	nSplitWindow = 8;
	else if (nIdx == 2)	nSplitWindow = 9;
	else if (nIdx == 3)	nSplitWindow = 16;
	else if (nIdx == 4)	nSplitWindow = 36;
	else if (nIdx == 5)	nSplitWindow = 64;

	pVideoWindow->channels		=	nSplitWindow;
	UpdateComponents();
}


void CLivePlayerDlg::OnCbnSelchangeComboRenderFormat()
{
	if (NULL == pComboxRenderFormat)		return;

	int iIdx = pComboxRenderFormat->GetCurSel();
	//if (iIdx == 0)	RenderFormat		=	RENDER_FORMAT_YV12;//YV12
	//else if (iIdx == 1)	RenderFormat	=	RENDER_FORMAT_YUY2;//YUY2
	//else if (iIdx == 2)	RenderFormat	=	RENDER_FORMAT_RGB565;//RGB565
	//else if (iIdx == 3)	RenderFormat	=	RENDER_FORMAT_X8R8G8B8;//X8R8G8B8
	//else if (iIdx == 4)	RenderFormat	=	RENDER_FORMAT_RGB24_GDI;//GDI
}


void CLivePlayerDlg::OnBnClickedCheckShowntoscale()
{
	//IDC_CHECK_SHOWNTOSCALE
	if (NULL == pVideoWindow)					return;
	if (NULL == pVideoWindow->pDlgVideo)		return;

	int shownToScale = pChkShownToScale->GetCheck();
	//static int shownToScale = 0x00;
	//shownToScale = (shownToScale==0x00?0x01:0x00);

	for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
	{
		pVideoWindow->pDlgVideo[i].SetShownToScale(shownToScale);
	}
}

void CLivePlayerDlg::OnBnClickedCheckmultiplex()
{
	if (NULL == pVideoWindow)					return;
	if (NULL == pVideoWindow->pDlgVideo)		return;

	unsigned char multiplex = (unsigned char)pChkMultiplex->GetCheck();

	for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
	{
		pVideoWindow->pDlgVideo[i].SetMultiplex(multiplex);
	}
}

BOOL CLivePlayerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	POINT	point;
	point.x = pt.x;
	point.y = pt.y;

	//ScreenToClient(&point);

	//TRACE("CLivePlayerDlg::OnMouseWheel  zDelta: %d  pt.x[%d] pt.y[%d]\n", zDelta, point.x, point.y);

	if (NULL != pVideoWindow && NULL != pVideoWindow->pDlgVideo)
	{
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (! pVideoWindow->pDlgVideo[i].IsWindowVisible() )	continue;

			CRect rcVideo;
			pVideoWindow->pDlgVideo[i].GetWindowRect(&rcVideo);
			//TRACE("Window[%d]  L:%d\tT:%d\tR:%d\tB:%d\n", i, rcVideo.left, rcVideo.top, rcVideo.right, rcVideo.bottom);

			if (PtInRect(&rcVideo, point))
			{
				//TRACE("鼠标位于第[%d]个窗口.\n", i);

				pVideoWindow->pDlgVideo[i].OnMouseWheel(zDelta, pt);

				break;
			}

		}
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}



LRESULT CLivePlayerDlg::OnExitFullScreen(WPARAM wParam, LPARAM lParam)
{
	FullScreen();

	return 0;
}

void	CLivePlayerDlg::FullScreen()
{
	INT		x, y, w, h;
	DWORD dwStyle = GetWindowLong( this->m_hWnd, GWL_STYLE );

	proConfig.fullScreen = (proConfig.fullScreen==0x01?0x00:0x01);

	bool bFullScreen = proConfig.fullScreen;
	if (bFullScreen)
	{
		//用MFC隐藏系统任务栏
		//CWnd *pWndTmp = FindWindow(TEXT("Shell_TrayWnd"), NULL);
		//if (pWndTmp!=NULL)	pWndTmp->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW);

		//::SetParent(m_hWnd, NULL);

		//dwStyle &= ~(WS_DLGFRAME);//|WS_THICKFRAME);

		//if (dwStyle & WS_DLGFRAME)	dwStyle &= ~WS_DLGFRAME;
		//if (dwStyle & WS_THICKFRAME)	dwStyle &= ~WS_THICKFRAME;
		//if (dwStyle & WS_THICKFRAME)	dwStyle &= ~WS_THICKFRAME;
		//if (dwStyle & WS_CHILD)			dwStyle &= !WS_CHILD;
		//if (! (dwStyle & WS_POPUP))		dwStyle |= WS_POPUP;

		//SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		
		//SetWindowPos(widget->m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

		x = 0;
		y = 0;
		w = GetSystemMetrics(SM_CXSCREEN);
		h = GetSystemMetrics(SM_CYSCREEN);

		//SetWindowPos(NULL, 0, 0, w, h, 0);
		// 去掉标题栏  
		ModifyStyle(WS_CAPTION, 0); 
		 // 去掉边框
		ModifyStyleEx(WS_EX_DLGMODALFRAME, 0);  
		//窗口位置和大小保持原来不变
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED); 
		//最大化窗口
		ShowWindow(SW_MAXIMIZE);
	}
	else
	{
		ModifyStyle(0, WS_CAPTION);
		ModifyStyleEx(0, WS_EX_DLGMODALFRAME);
		//SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowWindow(SW_NORMAL);
	}

	if (NULL != pComboxSplitScreen)		pComboxSplitScreen->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pComboxRenderFormat)		pComboxRenderFormat->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pChkShownToScale)		pChkShownToScale->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pChkMultiplex)		pChkMultiplex->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pChkFullScreen)		pChkFullScreen->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pStaticVolume)		pStaticVolume->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pSliderCtrlVolume)	pSliderCtrlVolume->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);

	if (NULL != pChkFullScreen)		pChkFullScreen->SetCheck(bFullScreen?1:0);
}


void CLivePlayerDlg::OnBnClickedCheckFullscreen()
{
	FullScreen();
}


HBRUSH CLivePlayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:	
		{
			pDC->SetBkColor(RGB(0x5b,0x5b,0x5b));
			pDC->SetTextColor(DIALOG_BASE_TEXT_COLOR);
			return m_BrushStatic;
		}
		break;
	default:
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CLivePlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( NULL != pScrollBar && NULL != pSliderCtrlVolume &&
		pSliderCtrlVolume->GetDlgCtrlID() == pScrollBar->GetDlgCtrlID())
	{
		int nValue = pSliderCtrlVolume->GetPos();
		nValue -= 182;
		m_nVolume = nValue;
		for (int i = 0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			//EasyPlayerPro_Setparam(pVideoWindow->pDlgVideo[i].m_hPlayer, EASY_PARAM_AUDIO_VOLUME, &nValue);
			pVideoWindow->pDlgVideo[i].SetVolume(nValue);
		}

	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CLivePlayerDlg::GetApplicationVersion(wchar_t *pVersion)
{
    TCHAR szFullPath[MAX_PATH];
    DWORD dwVerInfoSize = 0;
    DWORD dwVerHnd;
    VS_FIXEDFILEINFO * pFileInfo;
   
    GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
    dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
    if (dwVerInfoSize)
    {
        // If we were able to get the information, process it:
        HANDLE hMem;
        LPVOID lpvMem;
        unsigned int uInfoSize = 0;
       
        hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
        lpvMem = GlobalLock(hMem);
        GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);
       
        ::VerQueryValue(lpvMem, TEXT("\\"), (void**)&pFileInfo, &uInfoSize);
       
        int ret = GetLastError();
        WORD m_nProdVersion[4];
       
        // Product version from the FILEVERSION of the version info resource
        m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS);
        m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
        m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
        m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS);
       
        CString strVersion ;
        strVersion.Format(_T("EasyPlayerPro v%d.%d.%d.%d"),m_nProdVersion[0],
            m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);
       
        GlobalUnlock(hMem);
        GlobalFree(hMem);
       
		wcscpy(pVersion, strVersion);
    }
}


BOOL CLivePlayerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_ESCAPE)
	{
		if (proConfig.fullScreen==0x01)
		{
			FullScreen();
		}

		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CLivePlayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


BOOL CLivePlayerDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::OnCommand(wParam, lParam);
}

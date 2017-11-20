#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "EasyPlayerProDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "./libEasyPlayerPro/libEasyPlayerPro.lib")



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
	ON_CBN_SELCHANGE(IDC_COMBO_SPLIT_SCREEN, &CLivePlayerDlg::OnCbnSelchangeComboSplitScreen)
	ON_CBN_SELCHANGE(IDC_COMBO_RENDER_FORMAT, &CLivePlayerDlg::OnCbnSelchangeComboRenderFormat)
	ON_BN_CLICKED(IDC_CHECK_SHOWNTOSCALE, &CLivePlayerDlg::OnBnClickedCheckShowntoscale)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_CHECKMULTIPLEX, &CLivePlayerDlg::OnBnClickedCheckmultiplex)
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


	if (NULL != pVideoWindow && NULL!=pVideoWindow->pDlgVideo)
	{
		const char url_header[4][16] = {"rtsp://", "rtmp://", "http://", "file://"};
		int idx = 0;
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			pVideoWindow->pDlgVideo[i].SetURL((char *)url_header[idx++]);

			if (idx>=4)	idx = 0;
		}

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
	}

	OnCbnSelchangeComboRenderFormat();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLivePlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
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
	libEasyPlayerPro_Release(&playerHandle);
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
	pStaticCopyright	=	NULL;

	RenderFormat	=	RENDER_FORMAT_RGB24_GDI;//RGB565

	libEasyPlayerPro_Create(&playerHandle, 128);
}

void	CLivePlayerDlg::CreateComponents()
{
	__CREATE_WINDOW(pComboxSplitScreen, CComboBox,		IDC_COMBO_SPLIT_SCREEN);
	__CREATE_WINDOW(pComboxRenderFormat, CComboBox,		IDC_COMBO_RENDER_FORMAT);
	__CREATE_WINDOW(pChkShownToScale, CButton,		IDC_CHECK_SHOWNTOSCALE);
	__CREATE_WINDOW(pChkMultiplex, CButton,		IDC_CHECKMULTIPLEX);
	__CREATE_WINDOW(pStaticCopyright, CStatic,		IDC_STATIC_COPYRIGHT);

	pStaticCopyright->ShowWindow(FALSE);
	SetWindowText(TEXT("EasyPlayerPro"));

	if (NULL != pChkShownToScale)		pChkShownToScale->SetWindowText(TEXT("按比例显示"));
	if (NULL != pChkMultiplex)			pChkMultiplex->SetWindowText(TEXT("复用源"));

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
		pComboxSplitScreen->AddString(TEXT("36画面"));
		pComboxSplitScreen->AddString(TEXT("64画面"));
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
	rcVideo.SetRect(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom-30);
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
							pVideoWindow->pDlgVideo[n].ShowWindow(SW_SHOW);


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
	if (iIdx == 0)	RenderFormat	=	RENDER_FORMAT_YV12;//YV12
	else if (iIdx == 1)	RenderFormat	=	RENDER_FORMAT_YUY2;//YUY2
	else if (iIdx == 2)	RenderFormat	=	RENDER_FORMAT_RGB565;//RGB565
	else if (iIdx == 3)	RenderFormat	=	RENDER_FORMAT_X8R8G8B8;//X8R8G8B8
	else if (iIdx == 4)	RenderFormat	=	RENDER_FORMAT_RGB24_GDI;//GDI
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



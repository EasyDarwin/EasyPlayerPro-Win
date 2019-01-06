
#include "stdafx.h"
#include "DlgVideo.h"
#include "afxdialogex.h"
#include "gui_common.h"
#include "EasyPlayerProDlg.h"

// CDlgVideo 对话框
//int CALLBACK __EasyPlayerCallBack(EASY_CALLBACK_TYPE_ENUM callbackType, int channelId, void *userPtr, int mediaType, char *pbuf, EASY_FRAME_INFO *frameInfo);

IMPLEMENT_DYNAMIC(CDlgVideo, CDialogEx)

CDlgVideo::CDlgVideo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVideo::IDD, pParent)
{
	m_hPlayer = NULL;
	m_pMainDlg = NULL;
	m_WindowId	=	-1;
	m_ChannelId	=	-1;
	sourceMultiplex	=	0;
	bDrag		=	false;

	m_BrushBtn = ::CreateSolidBrush(DIALOG_BASE_BACKGROUND_COLOR);
	m_BrushEdt = ::CreateSolidBrush(RGB(0xef,0xef,0xef));
	m_BrushStatic = ::CreateSolidBrush(DIALOG_BASE_BACKGROUND_COLOR);

	InitialComponents();
	m_totalDuration = -1;
	m_bFullScreen = FALSE;
	m_pWndSave = NULL;
	m_lRecordTime = 0;//IDC_STATIC_RECORD_STATUS
	m_lRecordSliceUp = 0;
	m_bRecording = FALSE;
	m_bOpening = FALSE;
	m_speedRate = SPEED_NORMAL;
	m_strPlayFileTime = _T("");
	m_nVolume = 0;
	m_bLoopPlay = FALSE;

}

CDlgVideo::~CDlgVideo()
{
	DeleteObject(m_BrushBtn);
	DeleteObject(m_BrushEdt);
	DeleteObject(m_BrushStatic);
}

void CDlgVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgVideo, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_PREVIEW, &CDlgVideo::OnBnClickedButtonPreview)
	ON_BN_CLICKED(IDC_CHECK_OSD, &CDlgVideo::OnBnClickedCheckOsd)
	ON_WM_HSCROLL()
	ON_WM_RBUTTONUP()
	ON_MESSAGE(WM_RECORDING_CMPLETE, OnRecordingComplete)
	ON_MESSAGE(WM_SET_FILE_DURATION, OnSetFileDuration)
	ON_MESSAGE(WM_SET_FILE_PROGRESS, OnSetProgress)
	ON_MESSAGE(WM_SEEK_FILE, OnSeekFile)
	ON_MESSAGE(WM_PLAY_COMPLETE, OnPlayComplete)
	ON_MESSAGE(WM_SHOW_TOOLBAR, OnShowToolbar)
	ON_MESSAGE(WM_OPEN_FILE, OnOpenFilePlay)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgVideo 消息处理程序
LRESULT CDlgVideo::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_PAINT == message || WM_SIZE==message)
	{
		UpdateComponents();
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}

void CDlgVideo::SetMainDlg(CLivePlayerDlg* pDlg)
{
	m_pMainDlg = pDlg;
}


BOOL CDlgVideo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CreateComponents();

	SetBackgroundColor(RGB(0x7c,0x7c,0x7c));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgVideo::DestroyWindow()
{
	KillTimer(TIMER_ID_PROGRESS);
	EasyPlayerPro_Close(m_hPlayer);
	EasyPlayerPro_Release(m_hPlayer);
	m_hPlayer = NULL;
	m_totalDuration = -1;

	DeleteComponents();

	return CDialogEx::DestroyWindow();
}



void CDlgVideo::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	HWND hWnd = ::GetParent(GetSafeHwnd());
	if (NULL != hWnd)
	{
		::SendMessageW(hWnd, WM_WINDOW_MAXIMIZED, m_WindowId, 0);
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CDlgVideo::OnLButtonDown(UINT nFlags, CPoint point)
{
	bDrag = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgVideo::OnLButtonUp(UINT nFlags, CPoint point)
{
	bDrag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDlgVideo::OnMouseMove(UINT nFlags, CPoint point)
{
	if (bDrag)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		if (! rcClient.IsRectEmpty())
		{
			int nX = (int)(((float)point.x / (float)rcClient.Width() * 100.0f));
			int nY = (int)(((float)point.y / (float)rcClient.Height() * 100.0f));

			TRACE("X: %d\tY: %d\n", nX, nY);
		}
	}


	CDialogEx::OnMouseMove(nFlags, point);
}

void	CDlgVideo::SetWindowId(int _windowId)	
{
	m_WindowId = _windowId;

	//if (NULL != pDlgRender)	pDlgRender->SetChannelId(m_WindowId);

	if (m_WindowId == 0)
	{
		//if (NULL != pEdtURL)		pEdtURL->SetWindowText(TEXT("rtsp://121.15.129.227"));
		//if (NULL != pEdtURL)		pEdtURL->SetWindowText(TEXT("rtsp://192.168.1.100"));
	}
}

void	CDlgVideo::ShowToolbar(bool bShow)
{
	if (NULL!=pEdtURL)		pEdtURL->ShowWindow(bShow?SW_SHOW:SW_HIDE);
	if (NULL!=pChkOSD)		pChkOSD->ShowWindow(bShow?SW_SHOW:SW_HIDE);
	if (NULL!=pChkTCP)		pChkTCP->ShowWindow(bShow?SW_SHOW:SW_HIDE);
	if (NULL!=pSliderCache)	pSliderCache->ShowWindow(bShow?SW_SHOW:SW_HIDE);
	if (NULL!=pBtnPreview)	pBtnPreview->ShowWindow(bShow?SW_SHOW:SW_HIDE);

	if (NULL != pDlgRender)	pDlgRender->ShowToolbar(bShow);
	Invalidate();
}

void	CDlgVideo::SetURL(char *url, int scale, int osd, int tcp, int multiple, int cache, int showToolbar, int autoplay)
{
	wchar_t wszURL[1024] = {0};
	MByteToWChar(url, wszURL, sizeof(wszURL)/sizeof(wszURL[0]));
	if (NULL != pEdtURL)		pEdtURL->SetWindowText(wszURL);

	if (NULL != pChkOSD)		pChkOSD->SetCheck(osd);
	if (NULL != pChkTCP)		pChkTCP->SetCheck(tcp);
	//if (NULL != pSliderCache)	pSliderCache->SetPos(cache);

	shownToScale = scale;
	sourceMultiplex = multiple;

	ShowToolbar(showToolbar==0x01?true:false);

	if (autoplay==0x01)
	{
		OnBnClickedButtonPreview();
	}
}

void	CDlgVideo::SetShownToScale(int _shownToScale)
{
	int mode = 0;
	if (_shownToScale>-1)
	{
		mode = _shownToScale;
	}
	else
	{
		EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_VIDEO_MODE, &mode);
		mode++; mode %= EASY_VIDEO_MODE_MAX_NUM;
	}
	EasyPlayerPro_Setparam(m_hPlayer, EASY_PARAM_VIDEO_MODE, &mode);
	OnResizeVideoWnd();
}

void	CDlgVideo::SetMultiplex(unsigned char multiplex)
{
	sourceMultiplex = multiplex;
}

void	CDlgVideo::InitialComponents()
{
	pDlgRender	=	NULL;
	pProgressCtrl	=	NULL;
	pEdtURL		=	NULL;
	//pEdtUsername=	NULL;
	//pEdtPassword=	NULL;
	pChkOSD		=	NULL;
	pChkTCP		=	NULL;
	pSliderCache=	NULL;
	pBtnPreview	=	NULL;
}

void	CDlgVideo::CreateComponents()
{
	if (NULL == pDlgRender)
	{
		pDlgRender = new CDlgRender();
		pDlgRender->SetMainDlg(this);
		pDlgRender->Create(IDD_DIALOG_RENDER, this);
		pDlgRender->ShowWindow(SW_SHOW);
	}
	if (NULL == pProgressCtrl)
	{
		pProgressCtrl = new CEasyProgressCtrl();
		pProgressCtrl->Create(NULL, NULL, WS_CHILD, CRect(0, 0, 20, 20), this, IDC_EASY_PROGRESS_CTRL);
		pProgressCtrl->ShowWindow(SW_HIDE);
	}

	__CREATE_WINDOW(pEdtURL,		CEdit,		IDC_EDIT_RTSP_URL);
	//__CREATE_WINDOW(pEdtUsername,	CEdit,		IDC_EDIT_USERNAME);
	//__CREATE_WINDOW(pEdtPassword,	CEdit,		IDC_EDIT_PASSWORD);
	__CREATE_WINDOW(pChkOSD,		CButton,	IDC_CHECK_OSD);
	__CREATE_WINDOW(pChkTCP,		CButton,	IDC_CHECK_TCP);
	__CREATE_WINDOW(pSliderCache,	CSliderCtrl,IDC_SLIDER_CACHE);
	__CREATE_WINDOW(pBtnPreview,	CButton,	IDC_BUTTON_PREVIEW);


	//if (NULL != pEdtUsername)	pEdtUsername->SetWindowText(TEXT("admin"));
	//if (NULL != pEdtPassword)	pEdtPassword->SetWindowText(TEXT("12345"));
	if (NULL != pSliderCache)	pSliderCache->SetRange(0, 255);
	if (NULL != pSliderCache)	pSliderCache->SetPos(m_nVolume+182);

	if (NULL != pChkOSD)		pChkOSD->SetCheck(1);
	if (NULL != pChkTCP)		pChkTCP->SetCheck(1);

	if (NULL != pBtnPreview)		pBtnPreview->SetWindowText(TEXT("Play"));
}
void CDlgVideo::UpdateComponents()
{
	CRect	rcClient;
	GetClientRect(&rcClient);
	if (rcClient.IsRectEmpty())		return;

	bool bShowToolbar = true;
	if (NULL != pEdtURL && (!pEdtURL->IsWindowVisible()))	bShowToolbar = false;

	bool bShowFileToolbar = false;
	if (pProgressCtrl && pProgressCtrl->IsWindowVisible())		bShowFileToolbar = true;

	CRect	rcRender;
	rcRender.SetRect(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom-(bShowToolbar?20:0));
	if (bShowFileToolbar)	rcRender.bottom-=20;
	__MOVE_WINDOW(pDlgRender, rcRender);
	if (NULL != pDlgRender)		pDlgRender->Invalidate();


	CRect	rcFileToolbar;
	if (bShowFileToolbar)
	{
		rcFileToolbar.SetRect(rcRender.left, rcRender.bottom, rcRender.right, rcRender.bottom+20);
		__MOVE_WINDOW(pProgressCtrl, rcFileToolbar);
	}

	if (! bShowToolbar)	return;

	CRect	rcURL;
	rcURL.SetRect(rcClient.left, (bShowFileToolbar?rcFileToolbar.bottom+2:rcRender.bottom+2), rcClient.right-200, rcClient.bottom);
	__MOVE_WINDOW(pEdtURL, rcURL);
	if (NULL != pEdtURL)		pEdtURL->Invalidate();

	CRect	rcOSD;
	rcOSD.SetRect(rcURL.right+2, rcURL.top, rcURL.right+2+45, rcURL.bottom);
	__MOVE_WINDOW(pChkOSD, rcOSD);
	if (NULL != pChkOSD)		pChkOSD->Invalidate();
	CRect	rcTCP;
	rcTCP.SetRect(rcOSD.right+2, rcOSD.top, rcOSD.right+2+45, rcOSD.bottom);
	__MOVE_WINDOW(pChkTCP, rcTCP);
	CRect	rcCache;
	rcCache.SetRect(rcTCP.right+2, rcTCP.top, rcTCP.right+2+60, rcTCP.bottom);
	__MOVE_WINDOW(pSliderCache, rcCache);
	if (NULL != pSliderCache)		pSliderCache->Invalidate();

	CRect	rcPreview;
	rcPreview.SetRect(rcCache.right+2, rcURL.top, rcClient.right-3, rcURL.bottom);
	__MOVE_WINDOW(pBtnPreview, rcPreview);
	if (NULL != pBtnPreview)		pBtnPreview->Invalidate();
}

void CDlgVideo::DeleteComponents()
{
	__DELETE_WINDOW(pDlgRender);
	__DELETE_WINDOW(pProgressCtrl);	
}

void CDlgVideo::OnBnClickedButtonPreview()
{
	if (m_hPlayer)
	{
		//Player_CloseStream(m_ChannelId);
		//libEasyPlayerPro_StopPlayStream(playerHandle, m_ChannelId);
		//libEasyPlayerPro_CloseStream(playerHandle, m_ChannelId);
		//m_ChannelId = -1;

		KillTimer(TIMER_ID_PROGRESS);
		EasyPlayerPro_Close(m_hPlayer);
		EasyPlayerPro_Release(m_hPlayer);
		m_hPlayer = NULL;
		m_totalDuration = -1;
		if (pProgressCtrl)
		{
			pProgressCtrl->SetPos(0);
			pProgressCtrl->ShowWindow(SW_HIDE);
		}
		if (NULL != pDlgRender)
		{
			pDlgRender->SetChannelId(m_ChannelId);
			pDlgRender->ResetChannel();
		}

		if (NULL != pDlgRender)			pDlgRender->Invalidate();
		if (NULL != pBtnPreview)		pBtnPreview->SetWindowText(TEXT("Play"));

		PostMessageW(WM_SET_FILE_DURATION, 0, 0);
		PostMessageW(WM_SET_FILE_PROGRESS, 0, 0);
	}
	else
	{
		wchar_t wszURL[1024] = {0};
		if (NULL != pEdtURL)	pEdtURL->GetWindowTextW(wszURL, sizeof(wszURL));
		if (wcslen(wszURL) < 1)		return;

		char szURL[1024] = {0};
		WCharToMByte(wszURL, szURL, sizeof(szURL)/sizeof(szURL[0]));

/*
		wchar_t wszUsername[32] = {0};
		wchar_t wszPassword[32] = {0};
		if (NULL != pEdtUsername)	pEdtUsername->GetWindowText(wszUsername, sizeof(wszUsername));
		if (NULL != pEdtPassword)	pEdtPassword->GetWindowText(wszPassword, sizeof(wszPassword));


		char szUsername[32] = {0};
		char szPassword[32] = {0};
		WCharToMByte(wszUsername, szUsername, sizeof(szUsername)/sizeof(szUsername[0]));
		WCharToMByte(wszPassword, szPassword, sizeof(szPassword)/sizeof(szPassword[0]));
*/
		int	rtpOverTcp = 0x01;
		if (NULL != pChkTCP)
			rtpOverTcp = pChkTCP->GetCheck() ? 0x01 : 0x02;

		HWND hWnd = NULL;
		if (NULL != pDlgRender)	hWnd = pDlgRender->GetSafeHwnd();
		char* file_url = szURL;

		m_sourceType = EASY_CHANNEL_SOURCE_TYPE_RTSP;
		if (0 == strncmp(szURL, "rtsp", 4))			m_sourceType = EASY_CHANNEL_SOURCE_TYPE_RTSP;
		else if (0 == strncmp(szURL, "rtmp", 4))	m_sourceType = EASY_CHANNEL_SOURCE_TYPE_RTMP;
		else if (0 == strncmp(szURL, "http", 4))	m_sourceType = EASY_CHANNEL_SOURCE_TYPE_HLS;
		else if (0 == strncmp(szURL, "file", 4))
		{
			m_sourceType = EASY_CHANNEL_SOURCE_TYPE_FILE;
			//file_url = szURL + 7;
		}

		if (pProgressCtrl)
		{
			pProgressCtrl->ShowWindow(m_sourceType == EASY_CHANNEL_SOURCE_TYPE_FILE ? SW_SHOW : SW_HIDE);
		}
		
		EASY_VIDEO_SCALE_MODE scaleMode = (EASY_VIDEO_SCALE_MODE)m_pMainDlg->IsShowToScale();
		int	nVolValue = m_pMainDlg->GetAudioVolume();

		m_hPlayer = EasyPlayerPro_Create();

		// player open file
		m_hPlayer = EasyPlayerPro_Open(m_hPlayer, file_url, hWnd, EASY_VIDEO_RENDER_TYPE_D3D,
			scaleMode, (EASY_STREAM_LINK_MODE)rtpOverTcp, 100, nVolValue);
		if (m_hPlayer)
		{
			m_bPlayPause = FALSE;
			SetTimer(TIMER_ID_PROGRESS, 1000, NULL);
			SetTimer(TIMER_ID_TIME_OSD, 500, NULL);

			//libEasyPlayerPro_StartPlayStream(playerHandle, m_ChannelId, hWnd, RenderFormat);
			//libEasyPlayerPro_StartPlayStream(playerHandle, m_ChannelId, hWnd, RenderFormat);

			int iPos = pSliderCache->GetPos();
			//libEasyPlayerPro_SetPlayFrameCache(playerHandle, m_ChannelId, iPos);		//设置缓存
			//libEasyPlayerPro_StartPlaySound(playerHandle, m_ChannelId);				//播放声音
			if (NULL != pDlgRender)
			{
				pDlgRender->SetChannelId(m_ChannelId);
				pDlgRender->SetSourceType(m_sourceType);
			}

			//libEasyPlayerPro_SetScaleDisplay(playerHandle, m_ChannelId, shownToScale, RGB(0x26,0x26,0x26));

			OnBnClickedCheckOsd();

			if (NULL != pBtnPreview)		pBtnPreview->SetWindowText(TEXT("Stop"));
		}

		UpdateComponents();
	}
}



void CDlgVideo::OnBnClickedCheckOsd()
{
	int nShow = 0x00;

	if (NULL != pChkOSD)		nShow = pChkOSD->GetCheck();

	if (m_ChannelId > 0)
	{
		//libEasyPlayerPro_ShowStatisticalInfo(playerHandle, m_ChannelId, nShow);
	}
}

void CDlgVideo::SetVolume(int nValue)
{
	m_nVolume = nValue;
	if (m_hPlayer != 0)
	{
		EasyPlayerPro_Setparam(m_hPlayer, EASY_PARAM_AUDIO_VOLUME, &nValue);
	}
	pSliderCache->SetPos(nValue+182);
}


void CDlgVideo::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( NULL != pScrollBar && NULL != pSliderCache &&
		pSliderCache->GetDlgCtrlID() == pScrollBar->GetDlgCtrlID())
	{
		int nValue = pSliderCache->GetPos();
		
		if (m_hPlayer != 0)
		{
			//libEasyPlayerPro_SetPlayFrameCache(playerHandle, m_ChannelId, iPos);
			nValue -= 182;
			m_nVolume = nValue;
			EasyPlayerPro_Setparam(m_hPlayer, EASY_PARAM_AUDIO_VOLUME, &nValue);
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgVideo::OnRButtonUp(UINT nFlags, CPoint point)
{


	CDialogEx::OnRButtonUp(nFlags, point);
}

void CDlgVideo::OnMouseWheel(short zDelta, CPoint pt)
{
	if (NULL != pDlgRender)	pDlgRender->OnMouseWheel(zDelta, pt);
}




LRESULT CDlgVideo::OnRecordingComplete(WPARAM wParam, LPARAM lParam)
{
	if (NULL != pDlgRender)		pDlgRender->SetRecordingFlag(0);

	return 0;
}



//int CALLBACK __EasyPlayerCallBack(EASY_CALLBACK_TYPE_ENUM callbackType, int channelId, void *userPtr, int mediaType, char *pbuf, EASY_FRAME_INFO *frameInfo)
//{
//	CDlgVideo	*pLiveVideo = (CDlgVideo *)userPtr;
//
//	if (callbackType == EASY_TYPE_CONNECTING)
//	{
//		OutputDebugString(TEXT("EASY_TYPE_CONNECTING...\n"));
//	}
//	else if (callbackType == EASY_TYPE_CONNECTED)
//	{
//		OutputDebugString(TEXT("EASY_TYPE_CONNECTED.\n"));
//	}
//	else if (callbackType == EASY_TYPE_DISCONNECT)
//	{
//		OutputDebugString(TEXT("EASY_TYPE_DISCONNECT.\n"));
//		
//		if (NULL!=pLiveVideo)		pLiveVideo->PostMessageW(WM_PLAY_COMPLETE);
//	}
//	else if (callbackType == EASY_TYPE_RECONNECT)
//	{
//		OutputDebugString(TEXT("EASY_TYPE_RECONNECT.\n"));
//	}
//	else if (callbackType == EASY_TYPE_FILE_DURATION)
//	{
//		//wchar_t wszLog[128] = {0};
//		//wsprintf(wszLog, TEXT("EASY_TYPE_FILE_DURATION::总时长: %u\n"), frameInfo->timestamp_sec);
//		//OutputDebugString(wszLog);
//
//		if (NULL!=pLiveVideo)		pLiveVideo->PostMessageW(WM_SET_FILE_DURATION, 0, (int)frameInfo->timestamp_sec);
//	}
//	else if (callbackType == EASY_TYPE_CODEC_DATA)
//	{
//		if (mediaType == MEDIA_TYPE_SDP)
//		{
//		}
//		else if (mediaType == MEDIA_TYPE_CODEC_INFO)
//		{
//		}
//		else if (mediaType == MEDIA_TYPE_VIDEO)
//		{
//			//wchar_t wszLog[128] = {0};
//			//wsprintf(wszLog, TEXT("播放时间: %u\n"), frameInfo->timestamp_sec);
//			//OutputDebugString(wszLog);
//
//// 			char wszLog[512] = {0};
//// 			sprintf(wszLog, ("bitrate: %d  kbps\n"), frameInfo->bitrate);//swprintf
//// 			OutputDebugStringA(wszLog);
//
//
//			if (NULL!=pLiveVideo)		pLiveVideo->PostMessageW(WM_SET_FILE_PROGRESS, 0, (int)frameInfo->timestamp_sec);
//		}
//		else if (mediaType == MEDIA_TYPE_AUDIO && frameInfo->timestamp_sec>0)
//		{
//			if (NULL!=pLiveVideo)		pLiveVideo->PostMessageW(WM_SET_FILE_PROGRESS, 0, (int)frameInfo->timestamp_sec);
//		}
//		//else if (mediaType == 		
//
//#ifdef _DEBUG1
//		if (mediaType == 0x01)
//		{
//			static int iH264FrameNo = 0;
//			char sztmp[128] = {0};
//			sprintf(sztmp, "C:\\test\\h264\\%d.txt", frameInfo->length);//iH264FrameNo++, frameInfo->length);
//			FILE *f = fopen(sztmp, "wb");
//			if (NULL != f)
//			{
//				fwrite(pbuf, 1, frameInfo->length, f);
//				fclose(f);
//			}
//		}
//#endif
//	}
//	else if (callbackType == EASY_TYPE_DECODE_DATA)
//	{
//		//_TRACE(TRACE_LOG_DEBUG, "解码数据[ch%d]type[%d] channelId[%d] mediaType[%d] [%d x %d] framesize[%d]\n",  pLiveVideo->channelId,
//			//	callbackType, channelId, mediaType, frameInfo->width, frameInfo->height, frameInfo->length);
//	}
//	else if (callbackType == EASY_TYPE_SNAPSHOT)
//	{
//		//_TRACE(TRACE_LOG_DEBUG, "抓拍图片[ch%d] %s. filename:%s\n",  channelId, mediaType==1?"成功":"失败", pbuf);
//		if (mediaType == MEDIA_TYPE_VIDEO)		OutputDebugString(TEXT("抓拍图片成功\n"));
//		else if (mediaType == MEDIA_TYPE_EVENT)		OutputDebugString(TEXT("抓拍图片失败\n"));
//	}
//	else if (callbackType == EASY_TYPE_RECORDING)
//	{
//		if (mediaType == MEDIA_TYPE_VIDEO)		OutputDebugString(TEXT("录像成功\n"));
//		else if (mediaType == MEDIA_TYPE_EVENT)		OutputDebugString(TEXT("录像失败\n"));
//
//		pLiveVideo->PostMessageW(WM_RECORDING_CMPLETE, MEDIA_TYPE_VIDEO == mediaType ? 0 : -1, 0);
//	}
//	else if (callbackType == EASY_TYPE_INSTANT_REPLAY_RECORDING)
//	{
//		if (mediaType == MEDIA_TYPE_VIDEO)		OutputDebugString(TEXT("即时回放录像成功\n"));
//		else if (mediaType == MEDIA_TYPE_EVENT)		OutputDebugString(TEXT("即时回放录像失败\n"));
//	}
//
//	return 0;
//}




HBRUSH CDlgVideo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	//switch (nCtlColor)
	//{
	//case CTLCOLOR_BTN:	//按钮
	//	{
	//		return m_BrushBtn;
	//	}
	//	break;
	//	case CTLCOLOR_EDIT:	//编辑框
	//	{
	//		//pDC->SelectObject(&fontText);
	//		pDC->SetTextColor(DIALOG_BASE_TEXT_COLOR);
	//		return m_BrushEdt;
	//	}
	//	break;
	//case CTLCOLOR_STATIC:	
	//	{
	//		pDC->SetBkColor(DIALOG_BASE_BACKGROUND_COLOR);
	//		pDC->SetTextColor(DIALOG_BASE_TEXT_COLOR);
	//		return m_BrushStatic;
	//	}
	//	break;
	//default:
	//	break;
	//}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


LRESULT CDlgVideo::OnSetFileDuration(WPARAM wParam, LPARAM lParam)
{
	if (NULL != pProgressCtrl)		pProgressCtrl->SetRange(1, (int)lParam);

	if (pProgressCtrl && (!pProgressCtrl->IsWindowVisible()) && ((int)lParam>0))		pProgressCtrl->ShowWindow(SW_SHOW);

	return 0;
}
LRESULT CDlgVideo::OnSetProgress(WPARAM wParam, LPARAM lParam)
{
	if (NULL != pProgressCtrl)		pProgressCtrl->SetPos((int)lParam);

	return 0;
}

LRESULT CDlgVideo::OnSeekFile(WPARAM wParam, LPARAM lParam)
{
	unsigned int uiSeekTime = (unsigned int)lParam;
	//libEasyPlayerPro_SeekFile(playerHandle, m_ChannelId, uiSeekTime);
	if (m_totalDuration>0)
	{
		EasyPlayerPro_Seek(m_hPlayer, uiSeekTime * 1000);
	}
	return 0;
}

LRESULT CDlgVideo::OnPlayComplete(WPARAM wParam, LPARAM lParam)
{
	if (m_ChannelId > 0)
	{
		OnBnClickedButtonPreview();


		if (NULL != pDlgRender && pDlgRender->GetSourceType() == EASY_CHANNEL_SOURCE_TYPE_FILE)
		{
			MessageBox(TEXT("文件播放完成"), TEXT("OK"), MB_OK);
		}

	}
	return 0;
}

LRESULT CDlgVideo::OnShowToolbar(WPARAM wParam, LPARAM lParam)
{
	if (NULL == pEdtURL)		return 0;

	BOOL isVisible = pEdtURL->IsWindowVisible();

	ShowToolbar(! isVisible);

	return 0;
}

LRESULT CDlgVideo::OnOpenFilePlay(WPARAM wParam, LPARAM lParam)
{
	CFileDialog file(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,L"媒体文件(*.*)|*.*||");
	if(file.DoModal() != IDOK)		return 0;

	//获取文件名称
	file.GetFileName();
	//获取文件路径,此处只想说明下file.GetPathName()的返回值类型。
	CString filePath = file.GetPathName();

	char	szURL[MAX_PATH] = {0};
	strcat(szURL, "file://");
	WCharToMByte(filePath.GetString(), szURL+7, sizeof(szURL)/sizeof(szURL[0])-7);

	SetURL(szURL, 0x00, 0x00, 0x01, 0x00, 3, 1, 1);

	return 0;
}


BOOL CDlgVideo::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			if (proConfig.fullScreen == 0x01)
			{
				CWnd *pWnd = ::AfxGetMainWnd();
				if (NULL != pWnd)
				{
					pWnd->PostMessageW(WM_EXIT_FULLSCREEN);
				}
			}

			return TRUE;
		}
		else if (pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgVideo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER_ID_TIME_OSD:
	{
		USES_CONVERSION;
		//unsigned int timestamp = (unsigned int)time(NULL);
		//time_t tt = timestamp;
		//struct tm _time;
		//::localtime_s(&_time, &tt);
		//char szTime[64] = { 0, };
		//strftime(szTime, 32, "%Y年%m月%d日 %H:%M:%S", &_time);

		//CString strTime = (CString)szTime;

		//EasyPlayerPro_SetOSD(m_hPlayer, 1, 0, 0, 255, 0,
		//	700, 28, 30, 0, -18, "隶书", T2A(strTime));

		CString strOSD;
		if (m_sourceType != EASY_CHANNEL_SOURCE_TYPE_FILE && pChkOSD->GetCheck())
		{
			//int   EasyPlayerPro_SetOSD(void *hplayer, int bIsUse, int nMoveType, int R, int G, int B,
			//	int weight, int x, int y, int width, int height, char* fontname, char* tittleContent)
			MediaInfo mediaInfo;
			memset(&mediaInfo, 0x00, sizeof(MediaInfo));
			EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_MEDIA_INFO, &mediaInfo);

			//	int nBitsRate;
			//for Video
			//int nVCodec;
			//char sVCodec[32];
			//char sVCodecDetails[64];
			//int nWidth;
			//int nHeight;
			//int nFrameRate;

			if (pDlgRender->channelStatus.recording)
			{
				int nPieceId = 0;
				int recordTime = 0;
				EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_RECORD_TIME, &recordTime);
				EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_RECORD_PIECE_ID, &nPieceId);

				strOSD.Format(TEXT("%s[%dX%d] fps[%d/%d] Bitrate[%.2fMBps] \n录像切片[%d]录像中：%02d:%02d "), A2T(mediaInfo.sVCodec), mediaInfo.nWidth, mediaInfo.nHeight, mediaInfo.nStatisticsFPS, mediaInfo.nFrameRate, (float)mediaInfo.fStatisticsBitsrate, nPieceId, recordTime / 60, recordTime % 60);
			}
			else {
				strOSD.Format(TEXT("%s[%dX%d] fps[%d/%d] Bitrate[%.2fMBps]"), A2T(mediaInfo.sVCodec), mediaInfo.nWidth, mediaInfo.nHeight, mediaInfo.nStatisticsFPS, mediaInfo.nFrameRate, (float)mediaInfo.fStatisticsBitsrate);
			}
			EasyPlayerPro_SetOSD(m_hPlayer, 1, 1, 0, 255, 0,
				28, 5, 1, 0, 0, "Arial Black", T2A(strOSD));
		}
		else {
			if (pDlgRender->channelStatus.recording)
			{
				int nPieceId = 0;
				int recordTime = 0;
				EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_RECORD_TIME, &recordTime);
				EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_RECORD_PIECE_ID, &nPieceId);

				strOSD.Format(TEXT("录像切片[%d]录像中：%02d:%02d "), nPieceId, recordTime/60, recordTime%60);
				EasyPlayerPro_SetOSD(m_hPlayer, 1, 1, 0, 255, 0,
					28, 5, 1, 0, 0, "Arial Black", T2A(strOSD));
			}
			else {
				EasyPlayerPro_SetOSD(m_hPlayer, 0, 1, 0, 255, 0,
					28, 5, 1, 0, 0, "Arial Black", "");
			}
		}
	}
	break;
	case TIMER_ID_PROGRESS://进度条计时器
	{
#if 1
		if (m_totalDuration <= 0)
		{
			LONGLONG ltotal = 0;
			EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_MEDIA_DURATION, &ltotal);
			if (ltotal>1)
			{
				m_totalDuration = ltotal / 1000;
				int totalSeconds = (int)m_totalDuration;
				int gTotalSeconds = totalSeconds;
				int gTotalMinute = (int)(totalSeconds / 60);
				int nTotalHour = (int)(gTotalMinute / 60);  //时
				int nTotalMinute = (int)(gTotalMinute % 60);//分
				int totalSecond = (int)(totalSeconds % 60); //秒

				m_strPlayFileTime.Format(_T("%02d:%02d:%02d"), nTotalHour, nTotalMinute, totalSecond);
				if (NULL != pProgressCtrl)		
					pProgressCtrl->SetRange(1, (int)m_totalDuration);

				if (pProgressCtrl && (!pProgressCtrl->IsWindowVisible()) && ((int)m_totalDuration>0))
					pProgressCtrl->ShowWindow(SW_SHOW);
			}
		}

		LONGLONG llCurPos = 0;
		LONGLONG llPos = 0;
		EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_MEDIA_POSITION, &llPos);
		llCurPos = llPos / 1000;
		//TRACE("Position == %d\r\n",llCurPos);
		int totalSeconds = (int)llCurPos;
		int gTotalSeconds = totalSeconds;
		int gTotalMinute = (int)(totalSeconds / 60);
		int nTotalHour = (int)(gTotalMinute / 60);  //时
		int nTotalMinute = (int)(gTotalMinute % 60);//分
		int totalSecond = (int)(totalSeconds % 60); //秒
		CString strTemp = _T("");

		if (m_totalDuration>0)
		{
			if (m_totalDuration - llCurPos>1)
			{
				strTemp.Format(_T("%02d:%02d:%02d/%s"), nTotalHour, nTotalMinute, totalSecond, m_strPlayFileTime);
				if (pProgressCtrl)
				{
					pProgressCtrl->SetPos(llCurPos);
				}
			}
			else
			{
				EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_MEDIA_POSITION, &llPos);
				OnBnClickedButtonPreview();

				if (m_bLoopPlay)
				{
					OnBnClickedButtonPreview();
				}
				else
				{

					strTemp = _T("");
					//提示播放完成
					AfxMessageBox(_T("播放完成!"));
				}
			}
		}
		else
			strTemp.Format(_T("%02d:%02d:%02d/../../.."), nTotalHour, nTotalMinute, totalSecond);
		//SetString(2, strTemp);
#endif
	}
	break;
	case TIMER_RECORD_STATUS:
	{
		if (m_hPlayer)
		{
			//EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_RECORD_TIME, &m_lRecordTime);
			//EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_RECORD_PIECE_ID, &m_lRecordSliceUp);
			//int thh, tmm, tss = 0;
			//thh = m_lRecordTime / 3600;
			//tmm = (m_lRecordTime % 3600) / 60;
			//tss = (m_lRecordTime % 60);

			//CString sShowRec = _T("");
			//if (m_lRecordSliceUp > -1)
			//	sShowRec.Format(_T("录制中...... 录制时间：%02d:%02d:%02d  切片ID：%d"), thh, tmm, tss, m_lRecordSliceUp);
			//else
			//	sShowRec.Format(_T("录制中...... 录制时间：%02d:%02d:%02d"), thh, tmm, tss);

			//SetString(4, sShowRec);
		}
	}
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CDlgVideo::OnResizeVideoWnd()
{
	if (m_hPlayer && pDlgRender && pDlgRender->GetSafeHwnd())
	{
		int mode = 0;
		EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_VISUAL_EFFECT, &mode);
		if (EASY_AUDIO_VISUAL_EFFECT_DISABLE != mode)
		{
			pDlgRender->GetClientRect(&m_rtClient);
			int nVideoId = -1;
			EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_VIDEO_STREAM_CUR, &nVideoId);
			if (nVideoId < 0)// 无视频的时候只显示波形/频谱
			{
				EasyPlayerPro_Resize(m_hPlayer, 0, 0, 0, m_rtClient.right, (m_rtClient.bottom - 2));
				EasyPlayerPro_Resize(m_hPlayer, 1, 0, 0, m_rtClient.right, m_rtClient.bottom - 2);
			}		
			else {	// 有视频的时候显示视频和波形/频谱
				EasyPlayerPro_Resize(m_hPlayer, 0, 0, 0, m_rtClient.right, (m_rtClient.bottom - 2) * 3 / 4);
				EasyPlayerPro_Resize(m_hPlayer, 1, 0, (m_rtClient.bottom) * 3 / 4, m_rtClient.right, (m_rtClient.bottom) / 4);
				//EasyPlayerPro_Resize(m_hPlayer, 0, 0, 0, m_rtClient.right, (m_rtClient.bottom - 2));
				//EasyPlayerPro_Resize(m_hPlayer, 1, 0, 0, m_rtClient.right, m_rtClient.bottom - 2);

			}
		}
		else
		{
			if (pDlgRender && pDlgRender->GetSafeHwnd())
			{
				pDlgRender->GetClientRect(&m_rtClient);
				EasyPlayerPro_Resize(m_hPlayer, 0, 0, 0, m_rtClient.right, (m_rtClient.bottom - 2));
				EasyPlayerPro_Resize(m_hPlayer, 1, 0, 0, m_rtClient.right, m_rtClient.bottom - 2);
			}
		}
	}
}


void CDlgVideo::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
#if 1
	if (nType != SIZE_MINIMIZED)
	{
		//if (pDlgRender && pDlgRender->GetSafeHwnd())
		//{
		//	CRect rcClient;
		//	GetClientRect(&rcClient);
		//	pDlgRender->SetParent(this);
		//	pDlgRender->ModifyStyle(WS_POPUP, WS_CHILD);

		//	pDlgRender->MoveWindow(0, 40, rcClient.Width(), rcClient.Height() - 150);
		//}
		OnResizeVideoWnd();
	}
#endif 

}

void CDlgVideo::OnEffectMode(int nInMode)
{
	int mode = 0;
	if (nInMode>-1)
	{
		mode = nInMode;
	}
	else
	{
		EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_VISUAL_EFFECT, &mode);
		mode++; mode %= EASY_AUDIO_VISUAL_EFFECT_MAX_NUM;
	}
	EasyPlayerPro_Setparam(m_hPlayer, EASY_PARAM_VISUAL_EFFECT, &mode);

	if (EASY_AUDIO_VISUAL_EFFECT_DISABLE != mode)
	{
		if (pDlgRender && pDlgRender->GetSafeHwnd())
		{
			pDlgRender->GetClientRect(&m_rtClient);
			int nVideoId = -1;
			EasyPlayerPro_Getparam(m_hPlayer, EASY_PARAM_VIDEO_STREAM_CUR, &nVideoId);
			if (nVideoId < 0)// 无视频的时候只显示波形/频谱
			{
				EasyPlayerPro_Resize(m_hPlayer, 0, 0, 0, m_rtClient.right, (m_rtClient.bottom - 2));
				EasyPlayerPro_Resize(m_hPlayer, 1, 0, 0, m_rtClient.right, m_rtClient.bottom - 2);
			}
			else {	// 有视频的时候显示视频和波形/频谱
				EasyPlayerPro_Resize(m_hPlayer, 0, 0, 0, m_rtClient.right, (m_rtClient.bottom - 2) * 3 / 4);
				EasyPlayerPro_Resize(m_hPlayer, 1, 0, (m_rtClient.bottom) * 3 / 4, m_rtClient.right, (m_rtClient.bottom) / 4);
			}
		}
	}
	else
	{
		if (pDlgRender && pDlgRender->GetSafeHwnd())
		{
			pDlgRender->GetClientRect(&m_rtClient);
			EasyPlayerPro_Resize(m_hPlayer, 0, 0, 0, m_rtClient.right, (m_rtClient.bottom - 2));
			EasyPlayerPro_Resize(m_hPlayer, 1, 0, 0, m_rtClient.right, m_rtClient.bottom - 2);
		}
	}

}
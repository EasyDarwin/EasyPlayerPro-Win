#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "DlgRender.h"
#include "DlgVideo.h"
#include "afxdialogex.h"
#include <io.h>
#include <direct.h>

#include "DlgMediaInfo.h"

// CDlgRender 对话框

IMPLEMENT_DYNAMIC(CDlgRender, CDialogEx)

CDlgRender::CDlgRender(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRender::IDD, pParent)
{
	m_pMainDlg = NULL;
	memset(&channelStatus, 0x00, sizeof(CHANNELSTATUS));
	hMenu		=	NULL;
	mDrag		=	false;
	scaleMultiple=	1;
	memset(&pt_start, 0x00, sizeof(POINT));
	memset(&pt_start_org, 0x00, sizeof(POINT));

	mChannelId	=	0;
}

CDlgRender::~CDlgRender()
{
	ClosePopupMenu();
}

void CDlgRender::SetMainDlg(CDlgVideo* pDlg)
{
	m_pMainDlg = pDlg;
}


void CDlgRender::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRender, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CDlgRender 消息处理程序

BOOL CDlgRender::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetBackgroundColor(RGB(0x92,0x92,0x92));
	// load accelerators
	m_hAcc = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	::RegisterHotKey(GetSafeHwnd(), IDC_CTRL_D, MOD_CONTROL, 'D');//注册热键alt+D（D必须大写） 

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgRender::ClosePopupMenu()
{
	if (NULL != hMenu)
	{
		DestroyMenu(hMenu);
		hMenu = NULL;
	}
}

void	CDlgRender::SetSourceType(EASY_CHANNEL_SOURCE_TYPE_ENUM sourceType)
{
	mSourceType	=	sourceType;
}

void	CDlgRender::ResetChannel()
{
	memset(&channelStatus, 0x00, sizeof(CHANNELSTATUS));
}

void CDlgRender::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	::PostMessage(GetParent()->GetSafeHwnd(), WM_LBUTTONDBLCLK, 0, 0);

	CDialogEx::OnLButtonDblClk(nFlags, point);
}

void CDlgRender::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClosePopupMenu();

	//Player_SetRenderRect(mChannelId, NULL);
	scaleMultiple = 1;
	{
		if (m_pMainDlg->m_hPlayer)
		{
			hMenu = CreatePopupMenu();
			if (NULL != hMenu)
			{
				//AppendMenu(hMenu, MF_STRING, POP_MENU_OPEN_FILE, TEXT("打开文件"));
				
				//静音
				int mute = 0;
				EasyPlayerPro_Getparam(m_pMainDlg->m_hPlayer, EASY_PARAM_ADEV_MUTE, &mute);
				AppendMenu(hMenu, MF_STRING|(mute ?MF_CHECKED:MF_UNCHECKED), POP_MENU_AUDIO, TEXT("静音"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

				//录像
				AppendMenu(hMenu, MF_STRING|(channelStatus.recording==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_RECORDING, TEXT("手动录像"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

				//抓图
				AppendMenu(hMenu, MF_STRING, POP_MENU_SNAPSHOT_JPG, TEXT("抓图(JPG)"));
				AppendMenu(hMenu, MF_STRING, POP_MENU_SNAPSHOT_PNG, TEXT("抓图(PNG)"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

				if (EASY_CHANNEL_SOURCE_TYPE_FILE == mSourceType)
				{
					AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_PAUSE, TEXT("暂停(Ctrl+P)"));
					AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_RESUME, TEXT("恢复(Ctrl+R)"));
				}

				hSubEffectMenu = CreatePopupMenu();
				AppendMenu(hSubEffectMenu, MF_STRING| channelStatus.effectMode== EASY_AUDIO_VISUAL_EFFECT_DISABLE? MF_CHECKED : MF_UNCHECKED, POP_MENU_EFFECT_NONE, TEXT("无"));
				AppendMenu(hSubEffectMenu, MF_STRING | channelStatus.effectMode == EASY_AUDIO_VISUAL_EFFECT_WAVEFORM ? MF_CHECKED : MF_UNCHECKED, POP_MENU_EFFECT_WAVEFORM, TEXT("波形显示"));
				AppendMenu(hSubEffectMenu , MF_STRING | channelStatus.effectMode == EASY_AUDIO_VISUAL_EFFECT_SPECTRUM ? MF_CHECKED : MF_UNCHECKED, POP_MENU_EFFECT_SPECTRUM, TEXT("频谱显示"));
				//建立菜单
				InsertMenu(hMenu, POP_MENU_EFFECT_MODE, MF_BYPOSITION | MF_POPUP, UINT(hSubEffectMenu), L"音频显示");

				//AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_PREVIOUS_FRAME, TEXT("Previous Frame"));
				//AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_NEXT_FRAME, TEXT("Next Frame"));

				if (EASY_CHANNEL_SOURCE_TYPE_FILE == mSourceType)
				{
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					//SPEED_SLOW_X4 = -2,
					//	SPEED_SLOW_X2 = -1,
					//	SPEED_NORMAL = 0,
					//	SPEED_FAST_X2 = 1,
					//	SPEED_FAST_X4 = 2,
					//	SPEED_FAST_X8 = 3,
					//	SPEED_FAST_X16 = 4,
					//	SPEED_FAST_X64 = 5,
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_FAST_X2 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X2, TEXT("快进(x2)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_FAST_X4 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X4, TEXT("快进(x4)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_FAST_X8 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X8, TEXT("快进(x8)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_FAST_X16 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X16, TEXT("快进(x16)"));

					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_NORMAL ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_NORMAL_X1, TEXT("正常(x1)"));
		
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_SLOW_X2 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X2, TEXT("慢放(1/2x)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_SLOW_X4 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X4, TEXT("慢放(1/4x)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_SLOW_X8 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X8, TEXT("慢放(1/8x)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed== SPEED_SLOW_X16 ?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X16, TEXT("慢放(1/16x)"));

					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==POP_MENU_STREAM_SINGLE_FRAME?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SINGLE_FRAME, TEXT("单帧(Ctrl+S)"));
				}

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				//AppendMenu(hMenu, MF_STRING|(channelStatus.videoAnalysis==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_VA_ENABLE, TEXT("Video Analysis Settings"));
				//if (channelStatus.videoAnalysis == 0x01)
				//{
				//	RENDER_MODE_ENUM	renderMode = libVA_GetRenderMode(playerHandle,mChannelId);
				//	AppendMenu(hMenu, MF_STRING|(renderMode==RENDER_MODE_ZONE?MF_CHECKED:MF_UNCHECKED), POP_MENU_VA_WARNING_AREA, TEXT("警戒区"));
				//}


				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_D3D_ROTATE, TEXT("D3D画面旋转"));
				//AppendMenu(hMenu, MF_STRING, POP_MENU_CLEAR_OVERLAY_TEXT, TEXT("清除叠加文字"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING|(channelStatus.bShowToolbar?MF_CHECKED:MF_UNCHECKED), POP_MENU_SHOW_TOOLBAR, TEXT("工具栏"));
			
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING, POP_MENU_MEDIA_INFO, TEXT("媒体信息"));

				if (proConfig.fullScreen == 0x01)
				{
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING, POP_MENU_EXIT_FULLSCREEN, TEXT("退出全屏"));
				}
			
				CPoint	pMousePosition;
				GetCursorPos(&pMousePosition);
				SetForegroundWindow();
				TrackPopupMenu(hMenu, TPM_LEFTALIGN, pMousePosition.x, pMousePosition.y, 0, GetSafeHwnd(), NULL);
			}
		}
		else
		{
			hMenu = CreatePopupMenu();
			if (NULL != hMenu)
			{
				AppendMenu(hMenu, MF_STRING, POP_MENU_OPEN_FILE, TEXT("打开文件(Ctrl+O)"));

				if (proConfig.fullScreen == 0x01)
				{
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING, POP_MENU_EXIT_FULLSCREEN, TEXT("退出全屏"));
				}

				CPoint	pMousePosition;
				GetCursorPos(&pMousePosition);
				SetForegroundWindow();
				TrackPopupMenu(hMenu, TPM_LEFTALIGN, pMousePosition.x, pMousePosition.y, 0, GetSafeHwnd(), NULL);
			}
		}
	}

	CDialogEx::OnRButtonUp(nFlags, point);
}

bool CDlgRender::GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount)
{
	//模块路径
	TCHAR szModulePath[512] = TEXT("");
	GetModuleFileName(NULL, szModulePath, 512);

	//分析文件
	for (INT i = lstrlen(szModulePath);i >= 0;i--)
	{
		if (szModulePath[i] == TEXT('\\'))
		{
			szModulePath[i] = 0;
			break;
		}
	}
	//设置结果
	lstrcpyn(szWorkDirectory, szModulePath, wBufferCount);
	return true;
}

int CDlgRender::EnsureDirExist(CString dir)
{
	int len = 0;
	char temp_dir[MAX_PATH];
	char * pindex = NULL;
	int access_flag = 0;
	USES_CONVERSION;
	const char * p_dir = T2A(dir.GetBuffer(dir.GetLength()));

	if (!_access(p_dir, 0))
	{
		return 1;
	}
	//
	len = strlen(p_dir);
	if (len >= MAX_PATH)
	{
		return 0;
	}

	memset(temp_dir, 0, MAX_PATH);
	memcpy(temp_dir, p_dir, len);

	pindex = temp_dir;
	pindex = strrchr(pindex, gap_char);
	if (pindex >= (temp_dir + len - 1))
	{
		*pindex = 0;
	}

	pindex = temp_dir;
	pindex = strchr(pindex, gap_char);
	if (!pindex)
	{
		return 0;
	}
	pindex++;

	//
	access_flag = 0;
	do
	{
		pindex = strchr(pindex, gap_char);

		if (pindex)
		{
			*pindex = 0;
		}

		access_flag = _access(temp_dir, 0);

		if (access_flag)
		{
#ifdef _WIN32
			if (_mkdir(temp_dir))
#else
			if (mkdir(temp_dir, 0x777))
#endif
			{
				return 0;
			}
		}

		if (pindex)
		{
			*pindex = gap_char;
			pindex++;
		}
	} while (pindex);

	//
	if (_access(p_dir, 0))
	{
		return 0;
	}
	return 1;
}

void CDlgRender::HandleCommand(WORD wId)
{
	WORD	wID = (WORD)wId;
	switch (wID)
	{
	case POP_MENU_OPEN_FILE:
	{
		CWnd *pWnd = GetParent();
		if (NULL != pWnd)
		{
			pWnd->PostMessageW(WM_OPEN_FILE);
		}
	}
	break;
	case POP_MENU_AUDIO:
	{
		if (m_pMainDlg->m_hPlayer)
		{
			channelStatus.audio = (channelStatus.audio == 0x00 ? 0x01 : 0x00);
			if (channelStatus.audio == 0x01)
			{
				//int nVolume = -255;
				//EasyPlayerPro_Getparam(m_pMainDlg->m_hPlayer, EASY_PARAM_AUDIO_VOLUME, &nVolume);
				//if (nVolume > -182)//-182 ~ 73
				//{
				//	nVolume = -182;
				//}
				//EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_AUDIO_VOLUME, &nVolume);
				
				int mute = 1;
				EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_ADEV_MUTE, &mute);
			}
			else
			{
				//EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_AUDIO_VOLUME, &m_pMainDlg->m_nVolume);
				int mute = 0;
				EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_ADEV_MUTE, &mute);
			}
		}
	}
	break;
	case POP_MENU_RECORDING:
	{
		//channelStatus.recording = (channelStatus.recording==0x00?0x01:0x00);
		if (m_pMainDlg->m_hPlayer)
		{
			channelStatus.recording = (channelStatus.recording == 0x00 ? 0x01 : 0x00);

			//char sztmp[36] = {0};
			//time_t tt = time(NULL);
			//struct tm *_time = localtime(&tt);
			//memset(sztmp, 0x00, sizeof(sztmp));
			//strftime(sztmp, 32, "%Y%m%d_%H%M%S", _time);
			//
			//char szFilename[MAX_PATH] = {0};
			//sprintf(szFilename, "ch%d_%s.mpg", mChannelId, sztmp);

			TCHAR sPath[512];
			memset(sPath, 0x00, sizeof(TCHAR) * 512);
			GetWorkDirectory(sPath, 512);

			int nRecordPathLen = _tcslen(sPath);

			if ((sPath[nRecordPathLen - 1] != '/' && sPath[nRecordPathLen - 1] != '\\'))
			{
				sPath[nRecordPathLen] = '\\';
			}

			unsigned int timestamp = (unsigned int)time(NULL);
			time_t tt = timestamp;
			struct tm _time;
			::localtime_s(&_time, &tt);
			char szTime[64] = { 0, };
			strftime(szTime, 32, "\\record_%Y%m%d%H%M%S", &_time);

			CString strTime = (CString)szTime;

			CString sRecordPath = _T("");
			sRecordPath.Format(_T("%s%s"), sPath, _T("Record"));
			bool bSec = EnsureDirExist(sRecordPath);
			sRecordPath += strTime;

			if (channelStatus.recording == 0x01)
			{
				USES_CONVERSION;
				int ret = EasyPlayerPro_Record(m_pMainDlg->m_hPlayer, T2A(sRecordPath),
					proConfig.recordingDuration);
				if (ret < 0)	channelStatus.recording = 0x00;
			}
			else
				EasyPlayerPro_Stoprecord(m_pMainDlg->m_hPlayer);
		}
	}
	break;
	case POP_MENU_SNAPSHOT_PNG:
	{
		TCHAR sPath[512];
		memset(sPath, 0x00, sizeof(TCHAR) * 512);
		GetWorkDirectory(sPath, 512);

		int nPathLen = _tcslen(sPath);

		if ((sPath[nPathLen - 1] != '/' && sPath[nPathLen - 1] != '\\'))
		{
			sPath[nPathLen] = '\\';
		}

		unsigned int timestamp = (unsigned int)time(NULL);
		time_t tt = timestamp;
		struct tm _time;
		::localtime_s(&_time, &tt);
		char szTime[64] = { 0, };
		strftime(szTime, 32, "\\pic_%Y%m%d%H%M%S.png", &_time);

		CString strTime = (CString)szTime;

		CString sScreenPath = _T("");
		sScreenPath.Format(_T("%s%s"), sPath, _T("ScreenShot"));
		bool bSec = EnsureDirExist(sScreenPath);
		sScreenPath += strTime;

		USES_CONVERSION;

		EasyPlayerPro_Snapshot(m_pMainDlg->m_hPlayer, T2A(sScreenPath), 0, 0, 1000);
	}
	break;
	case POP_MENU_SNAPSHOT_JPG:
	{
		TCHAR sPath[512];
		memset(sPath, 0x00, sizeof(TCHAR) * 512);
		GetWorkDirectory(sPath, 512);

		int nPathLen = _tcslen(sPath);

		if ((sPath[nPathLen - 1] != '/' && sPath[nPathLen - 1] != '\\'))
		{
			sPath[nPathLen] = '\\';
		}

		unsigned int timestamp = (unsigned int)time(NULL);
		time_t tt = timestamp;
		struct tm _time;
		::localtime_s(&_time, &tt);
		char szTime[64] = { 0, };
		strftime(szTime, 32, "\\pic_%Y%m%d%H%M%S.jpg", &_time);

		CString strTime = (CString)szTime;

		CString sScreenPath = _T("");
		sScreenPath.Format(_T("%s%s"), sPath, _T("ScreenShot"));
		bool bSec = EnsureDirExist(sScreenPath);
		sScreenPath += strTime;

		USES_CONVERSION;

		EasyPlayerPro_Snapshot(m_pMainDlg->m_hPlayer, T2A(sScreenPath), 0, 0, 1000);
	}
	break;
	case POP_MENU_STREAM_PAUSE:
	{
		EasyPlayerPro_Pause(m_pMainDlg->m_hPlayer);	//暂停
													//channelStatus.playSpeed = PLAY_SPEED_PAUSED;
	}
	break;
	case POP_MENU_STREAM_RESUME:
	{
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
													//channelStatus.playSpeed = PLAY_SPEED_NORMAL;
	}
	break;
	case POP_MENU_EFFECT_NONE:
	{
		//	EASY_AUDIO_VISUAL_EFFECT_DISABLE,
		//	EASY_AUDIO_VISUAL_EFFECT_WAVEFORM,
		//	EASY_AUDIO_VISUAL_EFFECT_SPECTRUM,
		m_pMainDlg->OnEffectMode(EASY_AUDIO_VISUAL_EFFECT_DISABLE);
		channelStatus.effectMode = EASY_AUDIO_VISUAL_EFFECT_DISABLE;
	}
	break;
	case POP_MENU_EFFECT_WAVEFORM:
	{
		m_pMainDlg->OnEffectMode(EASY_AUDIO_VISUAL_EFFECT_WAVEFORM);
		channelStatus.effectMode = EASY_AUDIO_VISUAL_EFFECT_WAVEFORM;
	}
	break;
	case POP_MENU_EFFECT_SPECTRUM:
	{
		m_pMainDlg->OnEffectMode(EASY_AUDIO_VISUAL_EFFECT_SPECTRUM);
		channelStatus.effectMode = EASY_AUDIO_VISUAL_EFFECT_SPECTRUM;
	}
	break;
	case POP_MENU_STREAM_FAST_X2:
	{
		int nRate = 150;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_FAST_X2;
	}
	break;
	case POP_MENU_STREAM_FAST_X4:
	{
		int nRate = 200;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_FAST_X4;
	}
	break;
	case POP_MENU_STREAM_FAST_X8:
	{
		int nRate = 250;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_FAST_X8;
	}
	break;
	case POP_MENU_STREAM_FAST_X16:
	{
		int nRate = 300;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_FAST_X16;
	}
	break;
	case POP_MENU_STREAM_NORMAL_X1:
	{
		int nRate = 100;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_NORMAL;
	}
	break;
	case POP_MENU_STREAM_SLOW_X2:
	{
		int nRate = 75;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_SLOW_X2;
	}
	break;
	case POP_MENU_STREAM_SLOW_X4:
	{
		int nRate = 50;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_SLOW_X4;
	}
	break;
	case POP_MENU_STREAM_SLOW_X8:
	{
		int nRate = 35;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_SLOW_X8;
	}
	break;
	case POP_MENU_STREAM_SLOW_X16:
	{
		int nRate = 25;
		EasyPlayerPro_Play(m_pMainDlg->m_hPlayer);	//恢复
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_PLAY_SPEED, &nRate);
		channelStatus.playSpeed = SPEED_SLOW_X16;
	}
	break;
	case POP_MENU_STREAM_SINGLE_FRAME:
	{
		EasyPlayerPro_StepPlay(m_pMainDlg->m_hPlayer, 1);
	}
	break;
	case POP_MENU_STREAM_D3D_ROTATE: //d3d视频旋转
	{
		int angle = 0;
		EasyPlayerPro_Getparam(m_pMainDlg->m_hPlayer, EASY_PARAM_VDEV_D3D_ROTATE, &angle);
		angle += 90; angle %= 360;
		EasyPlayerPro_Setparam(m_pMainDlg->m_hPlayer, EASY_PARAM_VDEV_D3D_ROTATE, &angle);
	}
	break;
	case POP_MENU_CLEAR_OVERLAY_TEXT:
	{
		EasyPlayerPro_SetOSD(m_pMainDlg->m_hPlayer, 0, 1, 0, 255, 0,
			32, 10, 20, 0, -49, "隶书", "测试叠加文字");
	}
	break;
	case POP_MENU_SHOW_TOOLBAR:
	{
		CWnd *pWnd = GetParent();
		if (NULL != pWnd)
		{
			pWnd->PostMessageW(WM_SHOW_TOOLBAR);
		}
	}
	break;
	case POP_MENU_MEDIA_INFO:
	{
		MediaInfo mediaInfo;
		memset(&mediaInfo, 0x00, sizeof(MediaInfo));
		EasyPlayerPro_Getparam(m_pMainDlg->m_hPlayer, EASY_PARAM_MEDIA_INFO, &mediaInfo);

		CDlgMediaInfo dlgMediaInfo(&mediaInfo);
		dlgMediaInfo.DoModal();
	}
	break;
	case POP_MENU_EXIT_FULLSCREEN:
	{
		CWnd *pWnd = ::AfxGetMainWnd();
		if (NULL != pWnd)
		{
			pWnd->PostMessageW(WM_EXIT_FULLSCREEN);
		}
	}
	break;
	default:
		break;
	}

}

BOOL CDlgRender::OnCommand(WPARAM wParam, LPARAM lParam)
{
	WORD	wID = (WORD)wParam;
	HandleCommand(wID);
	return CDialogEx::OnCommand(wParam, lParam);
}


void CDlgRender::OnLButtonDown(UINT nFlags, CPoint point)
{
	//mDrag = true;

	//startPoint.x = point.x;
	//startPoint.y = point.y;

	//CRect rcClient;
	//GetClientRect(&rcClient);
	//int nLeftPercent = (int)((float)startPoint.x / (float)rcClient.Width()*100.0f);
	//int nTopPercent  = (int)((float)startPoint.y / (float)rcClient.Height()*100.0f);

	//POINT pt;
	//pt.x = nLeftPercent;
	//pt.y = nTopPercent;

	////Player_SetDragStartPoint(mChannelId, pt);

	//if (channelStatus.digitalZoom == 0x01)		//电子放大
	//{
	//	channelStatus.drag = 0x01;

	//	float fXPercent = 0.0f, fYPercent=0.0f;

	//	CRect rcClient;
	//	GetClientRect(&rcClient);
	//	fXPercent = ((float)point.x / (float)rcClient.Width()*100.0f);
	//	fYPercent  = ((float)point.y / (float)rcClient.Height()*100.0f);
	//	libEasyPlayerPro_SetElectronicZoomStartPoint(playerHandle, mChannelId, fXPercent, fYPercent, 0x01);
	//}
	//else if (libVA_GetRenderMode(playerHandle,mChannelId) != RENDER_MODE_VIDEO)
	//{
	//	VA_DETECT_POINT_T	p;
	//	memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
	//	p.x = point.x;
	//	p.y = point.y;
	//	p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
	//	p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

	//	//libVA_AddWarningAreaNode(playerHandle, mChannelId, &p);

	//	libVA_AddCustomZoneNode(playerHandle, mChannelId, channelStatus.zoneId, "", &p, 0x01, 1, 4, 40, 0x00, 
	//		RGB(0xff,0x00,0x00), RGB(0x80,0xff,0x00), RGB(0x00,0x00,0x00), 20, 100, 180);

	//	channelStatus.drag = 0x01;
	//}

	SetFocus();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgRender::OnLButtonUp(UINT nFlags, CPoint point)
{

	//if (mDrag)
	//{
	//	if (channelStatus.digitalZoom == 0x01)
	//	{
	//		libEasyPlayerPro_SetElectronicZoom(playerHandle, mChannelId, 1);
	//		//libEasyPlayerPro_ResetDragPoint(playerHandle, mChannelId);
	//	}
	//	else
	//	{
	//		CRect rcClient;
	//		GetClientRect(&rcClient);

	//		VA_DETECT_POINT_T	p;
	//		memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
	//		p.x = point.x;
	//		p.y = point.y;
	//		p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
	//		p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

	//		libVA_MoveCustomZoneNode(playerHandle, mChannelId, &p, 0x01, 0x00);
	//		//libVA_EndCustomZoneNode(playerHandle, mChannelId, 0x00);

	//		channelStatus.drag = 0x01;
	//	}
	//}
	//mDrag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDlgRender::OnMouseMove(UINT nFlags, CPoint point)
{
	//if (mDrag)
	//{
	//	CRect rcClient;
	//	GetClientRect(&rcClient);

	//	if (channelStatus.digitalZoom == 0x01)		//电子放大
	//	{
	//		float fXPercent = 0.0f, fYPercent=0.0f;

	//		CRect rcClient;
	//		GetClientRect(&rcClient);
	//		fXPercent = ((float)point.x / (float)rcClient.Width()*100.0f);
	//		fYPercent  = ((float)point.y / (float)rcClient.Height()*100.0f);
	//		libEasyPlayerPro_SetElectronicZoomEndPoint(playerHandle, mChannelId, fXPercent, fYPercent);
	//	}
	//	else
	//	{
	//		int nLeftPercent = (int)((float)startPoint.x / (float)rcClient.Width()*100.0f);
	//		int nTopPercent  = (int)((float)startPoint.y / (float)rcClient.Height()*100.0f);
	//		int nRightPercent = (int)((float)point.x / (float)rcClient.Width()*100.0f);
	//		int nBottomPercent  = (int)((float)point.y / (float)rcClient.Height()*100.0f);

	//		VA_DETECT_POINT_T	p;
	//		memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
	//		p.x = point.x;
	//		p.y = point.y;
	//		p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
	//		p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

	//		

	//		//Player_SetDragEndPoint(mChannelId, pt);
	//	}
	//}

	//if (libVA_GetRenderMode(playerHandle,mChannelId) != RENDER_MODE_VIDEO && channelStatus.drag == 0x01)
	//{
	//	CRect rcClient;
	//	GetClientRect(&rcClient);

	//	VA_DETECT_POINT_T	p;
	//	memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
	//	p.x = point.x;
	//	p.y = point.y;
	//	p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
	//	p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

	//	//libVA_UpdateWarningAreaNode(playerHandle, mChannelId, &p);
	//	libVA_MoveCustomZoneNode(playerHandle, mChannelId, &p, 0x00, 0x00);
	//}


	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CDlgRender::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
void CDlgRender::OnMouseWheel(short zDelta, CPoint pt)
{
}

void	CDlgRender::SetRecordingFlag(int flag)
{
	channelStatus.recording = flag;
}


void CDlgRender::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	//if (libVA_GetRenderMode(playerHandle,mChannelId) != RENDER_MODE_VIDEO)
	//{
	//	CRect rcClient;
	//	GetClientRect(&rcClient);
	//	libVA_UpdateWarningAreaPosition(playerHandle, mChannelId, rcClient);

	//	libVA_UpdateCustomZonePosition(playerHandle, mChannelId, rcClient);
	//}

}


BOOL CDlgRender::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
		{
			return TRUE;
		}
		char nChar = pMsg->wParam;
		if (nChar == 'O' && ((GetAsyncKeyState(VK_LCONTROL) & 0x8000)))
		{
			HandleCommand(POP_MENU_OPEN_FILE);
		}
		else if (nChar == 'X' && ((GetAsyncKeyState(VK_LCONTROL) & 0x8000)))
		{
			HandleCommand(POP_MENU_SNAPSHOT_JPG);
		}
		else if (nChar == 'P' && ((GetAsyncKeyState(VK_LCONTROL) & 0x8000)))
		{
			HandleCommand(POP_MENU_STREAM_PAUSE);
		}
		else if (nChar == 'R' && ((GetAsyncKeyState(VK_LCONTROL) & 0x8000)))
		{
			HandleCommand(POP_MENU_STREAM_RESUME);
		}	
		else if (nChar == 'S' && ((GetAsyncKeyState(VK_LCONTROL) & 0x8000)))
		{
			HandleCommand(POP_MENU_STREAM_SINGLE_FRAME);
		}
		
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}



void CDlgRender::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDlgRender::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{																  																  
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nKey1 == MOD_CONTROL && nKey2 == 'D')
	//{
	//	HandleCommand(POP_MENU_OPEN_FILE);
	//}
		
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

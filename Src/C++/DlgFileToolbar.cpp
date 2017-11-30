// DlgFileToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "DlgFileToolbar.h"
#include "afxdialogex.h"


// CDlgFileToolbar dialog

IMPLEMENT_DYNAMIC(CDlgFileToolbar, CDialogEx)

CDlgFileToolbar::CDlgFileToolbar(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgFileToolbar::IDD, pParent)
{
	pSliderProgress		=	NULL;
	pStaticTime			=	NULL;

	m_BrushStatic = ::CreateSolidBrush(RGB(0xab,0xab,0xab));
}

CDlgFileToolbar::~CDlgFileToolbar()
{
	DeleteObject(m_BrushStatic);
}


void CDlgFileToolbar::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFileToolbar, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDlgFileToolbar message handlers


BOOL CDlgFileToolbar::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundColor(RGB(0xab,0xab,0xab));

	__CREATE_WINDOW(pSliderProgress, CSliderCtrl,	IDC_SLIDER_PROGRESS);
	__CREATE_WINDOW(pStaticTime, CStatic,	IDC_STATIC_TIME);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CDlgFileToolbar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_PAINT==message || WM_SIZE==message)
	{
		UpdateComponents();
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}

void	CDlgFileToolbar::UpdateComponents()
{
	CRect	rcClient;
	GetClientRect(&rcClient);
	if (rcClient.IsRectEmpty())			return;

	CRect	rcProgress;
	rcProgress.SetRect(rcClient.left, rcClient.top, rcClient.right-120, rcClient.bottom);
	__MOVE_WINDOW(pSliderProgress, rcProgress);

	CRect	rcTime;
	rcTime.SetRect(rcProgress.right+2, rcProgress.top, rcClient.right, rcProgress.bottom);
	__MOVE_WINDOW(pStaticTime, rcTime);
}


HBRUSH CDlgFileToolbar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:	
		{
			//pDC->SetBkColor(DIALOG_BASE_BACKGROUND_COLOR);
			//pDC->SetTextColor(DIALOG_BASE_TEXT_COLOR);
			return m_BrushStatic;
		}
		break;
	default:
		break;
	}
	return hbr;
}


void	CDlgFileToolbar::SetMaxTime(int duration)
{
	if (NULL == pSliderProgress)		return;

	pSliderProgress->SetRange(1, duration);
}

void	CDlgFileToolbar::SetCurrentTime(int secs)
{
	int max = 0;
	if (NULL != pSliderProgress)
	{
		max = pSliderProgress->GetRangeMax();
		pSliderProgress->SetPos(secs);
	}

	int curr_mins = secs / 60;
	int	curr_secs = secs % 60;
	int curr_hours =curr_mins / 60;
		curr_mins %= 60;

	int max_mins = max / 60;
	int max_secs = max % 60;
	int max_hour = max_mins / 60;
	max_mins %= 60;
	wchar_t wszTime[64] = {0};
	wsprintf(wszTime, TEXT("%02d:%02d:%02d/%02d:%02d:%02d"), curr_hours, curr_mins, curr_secs, max_hour, max_mins, max_secs);

	if (NULL!=pStaticTime)		pStaticTime->SetWindowText(wszTime);
}


void CDlgFileToolbar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( NULL != pScrollBar && NULL != pSliderProgress &&
		pSliderProgress->GetDlgCtrlID() == pScrollBar->GetDlgCtrlID())
	{
		int iPos = pSliderProgress->GetPos();
		
		HWND hWnd = ::GetParent(GetSafeHwnd());
		::PostMessage(hWnd, WM_SEEK_FILE, 0, (LPARAM)iPos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

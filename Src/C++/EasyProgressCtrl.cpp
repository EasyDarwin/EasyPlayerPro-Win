// EasyProgressCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "EasyProgressCtrl.h"


// CEasyProgressCtrl

IMPLEMENT_DYNAMIC(CEasyProgressCtrl, CWnd)

CEasyProgressCtrl::CEasyProgressCtrl()
{
	fontText.CreateFont(15, 0, 0, 0, 0, FALSE, FALSE, 0, 0, 0, 0, 10, 0, TEXT("Arial"));
	mMinVal	=	0;
	mMaxVal	=	0;
	mPos		=	0;

	bDrag	=	false;
}

CEasyProgressCtrl::~CEasyProgressCtrl()
{
	fontText.DeleteObject();
}


BEGIN_MESSAGE_MAP(CEasyProgressCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CEasyProgressCtrl message handlers
void	CEasyProgressCtrl::SetRange(int minVal, int maxVal)
{
	mMinVal	=	minVal;
	mMaxVal	=	maxVal;
}

void	CEasyProgressCtrl::SetPos(int val, bool playing)
{
	if (playing && bDrag)		return;

	if (val > mMaxVal)			return;

	mPos	=	val;

	int secs = val;
	int max = mMaxVal;

	int curr_mins = secs / 60;
	int	curr_secs = secs % 60;
	int curr_hours =curr_mins / 60;
		curr_mins %= 60;

	int max_mins = max / 60;
	int max_secs = max % 60;
	int max_hour = max_mins / 60;
	max_mins %= 60;

	memset(wszProgressLabel, 0x00, sizeof(wszProgressLabel));
	wsprintf(wszProgressLabel, TEXT("%02d:%02d:%02d/%02d:%02d:%02d"), curr_hours, curr_mins, curr_secs, max_hour, max_mins, max_secs);

	Invalidate();
}



void CEasyProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	CRect rcClient;
	GetClientRect(&rcClient);
	if (IsRectEmpty(&rcClient))		return;

	CDC		*m_pMemDC = new CDC();
	m_pMemDC->CreateCompatibleDC(&dc);
	CBitmap	*m_pBmp = new CBitmap();
	m_pBmp->CreateCompatibleBitmap(&dc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
	m_pMemDC->SelectObject(m_pBmp);
	m_pMemDC->SetBkMode(TRANSPARENT);
	m_pMemDC->SetTextColor(RGB(0xf5,0xf5,0xf5));

	//»­±³¾°
	int nColor = 0;
	m_pMemDC->FillSolidRect(&rcClient, RGB(0x55,0x58,0x53));
	mRcRange.SetRect(rcClient.left, rcClient.top, rcClient.right-110, rcClient.bottom);

	CRect	rcSlider;
	rcSlider.SetRect(mRcRange.left, mRcRange.top+5, mRcRange.right, mRcRange.bottom-3);
	m_pMemDC->FillSolidRect(&rcSlider, RGB(0x3f,0x41,0x3d));
	if (mMaxVal > mMinVal && mPos>0 && mPos<=mMaxVal)
	{
		float fPercent = (float)mPos / (float)mMaxVal ;

		CRect	rcPos;
		rcPos.SetRect(rcSlider.left, rcSlider.top, (int)(rcSlider.left+(float)rcSlider.Width() * fPercent), rcSlider.bottom);
		COLORREF	bkcolor = RGB(0x91,0xa5,0x7e);
		int nColor = 0;
		CRect	rcTmp;
		for (int i = rcPos.top; i < rcPos.bottom; i ++)
		{
			rcTmp.SetRect(rcPos.left, i, rcPos.right, i+1);
			m_pMemDC->FillSolidRect(&rcTmp, RGB(bkcolor&0xFF-nColor, (bkcolor>>8&0xFF)-nColor, (bkcolor>>16&0xFF)-nColor));
			nColor ++;
		}
	}

	if ( (int)wcslen(wszProgressLabel) > 0)
	{
		CRect	rcLabel;
		rcLabel.SetRect(mRcRange.right,  rcClient.top, rcClient.right, rcClient.bottom);

		CFont	*pFont = m_pMemDC->SelectObject(&fontText);
		m_pMemDC->DrawText(wszProgressLabel, (int)wcslen(wszProgressLabel), &rcLabel, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		m_pMemDC->SelectObject(pFont);
	}

	dc.BitBlt(rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, m_pMemDC, 0, 0, SRCCOPY);


	if (NULL != m_pBmp)
	{
		m_pBmp->DeleteObject();
		delete m_pBmp;
		m_pBmp = NULL;
	}
	if (NULL != m_pMemDC)
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}
}


void CEasyProgressCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (mMaxVal > 0 && mPos>=0)
	{
		float fPercent = (float)point.x / (float)mRcRange.Width();
		int iPos = (int)((float)mMaxVal * fPercent);

		HWND hWnd = ::GetParent(GetSafeHwnd());
		if (NULL != hWnd)
		{
			::PostMessage(hWnd, WM_SEEK_FILE, 0, (LPARAM)iPos);
		}
	}

	bDrag = false;

	CWnd::OnLButtonUp(nFlags, point);
}


void CEasyProgressCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	bDrag = true;

	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CEasyProgressCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	//return TRUE;

	return CWnd::OnEraseBkgnd(pDC);
}


void CEasyProgressCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (bDrag && mMaxVal > 0 && mPos>0)
	{
		float fPercent = (float)point.x / (float)mRcRange.Width();
		int iPos = (int)((float)mMaxVal * fPercent);
		SetPos(iPos, false);
	}


	CWnd::OnMouseMove(nFlags, point);
}

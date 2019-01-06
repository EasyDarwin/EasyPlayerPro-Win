#include "MyProgressCtrl.h"

#include "stdafx.h"
#include "resource.h"
// CMyProgressCtrl

IMPLEMENT_DYNAMIC(CMyProgressCtrl, CWnd)

CString GetSystemFontName()
{
	return TEXT("Arial");
}

CMyProgressCtrl::CMyProgressCtrl()
{
	fontTitle.CreateFont(15, 0, 0, 0, 0, FALSE, FALSE, 0, 0, 0, 0, 10, 0, GetSystemFontName());
	fontText.CreateFont(15, 0, 0, 0, 0, FALSE, FALSE, 0, 0, 0, 0, 10, 0, GetSystemFontName());
	brushEnabled.CreateSolidBrush(RGB(0x00,0xff,0x00));
	brushDisabled.CreateSolidBrush(RGB(0xa5,0xa5,0xa5));
	m_pDC		=	NULL;
	m_pMemDC	=	NULL;
	m_pBmp		=	NULL;
	m_pMemBMPDC	=	NULL;

	bDragSpeed	=	false;
	nSpeed		=	20;
	m_rcSpeed2.SetRectEmpty();

	m_rcSpeed.SetRectEmpty();
}

CMyProgressCtrl::~CMyProgressCtrl()
{
	if (NULL != m_pBmp)
	{
		m_pBmp->DeleteObject();
		delete m_pBmp;
		m_pBmp = NULL;
	}
	if (NULL != m_pMemBMPDC)
	{
		m_pMemBMPDC->DeleteDC();
		delete m_pMemBMPDC;
		m_pMemBMPDC = NULL;
	}
	if (NULL != m_pMemDC)
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}

	if (NULL != m_pDC)
	{
		m_pDC = NULL;
	}
	fontTitle.DeleteObject();
	fontText.DeleteObject();
	brushEnabled.DeleteObject();
	brushDisabled.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMyProgressCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CStatusPanelCtrl 消息处理程序

BOOL CMyProgressCtrl::Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, char *title, int msg, HWND recvMsgHwnd)
{
	m_MsgHwnd	=	recvMsgHwnd;
	m_Msg		=	msg;

	return CWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID);
}

LRESULT CMyProgressCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_SIZE)
	{
		m_rcSpeed2.SetRectEmpty();
		Invalidate();
	}

	return CWnd::WindowProc(message, wParam, lParam);
}
void CMyProgressCtrl::DrawLine(CDC *pDC, int left, int top, int right, int bottom)
{
	RECT rect;
	SetRect(&rect, left, top, right, bottom);
	DrawLine(pDC, rect);
}
void CMyProgressCtrl::DrawLine(CDC *pDC, RECT rect)
{
	if (NULL == pDC)
		return;

	//left
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.left, rect.bottom);

	//top
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.top);

	//right
	pDC->MoveTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);

	//bottom
	pDC->MoveTo(rect.left, rect.bottom);
	pDC->LineTo(rect.right, rect.bottom);
}




void CMyProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rcClient;
	GetClientRect(&rcClient);
	if (IsRectEmpty(&rcClient))		return;




	if (NULL == m_pDC)		m_pDC = GetDC();
	if (NULL == m_pDC)		return;

	if (NULL == m_pMemDC)
	{
		m_pMemDC = new CDC();
		m_pMemDC->CreateCompatibleDC(m_pDC);
	}
	if (NULL == m_pMemBMPDC)
	{
		m_pMemBMPDC = new CDC();
		m_pMemBMPDC->CreateCompatibleDC(m_pDC);
	}

	if (! EqualRect(&m_rcOld, &rcClient))
	{
		if (NULL != m_pBmp)
		{
			m_pBmp->DeleteObject();
			delete m_pBmp;
			m_pBmp = NULL;
		}
	}
	if (NULL == m_pBmp)
	{
		m_pBmp = new CBitmap();
		m_pBmp->CreateCompatibleBitmap(m_pDC, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
		m_pMemDC->SelectObject(m_pBmp);
		m_pMemDC->SetBkMode(TRANSPARENT);
		m_pMemDC->SetTextColor(RGB(0xf5,0xf5,0xf5));

		CopyRect(&m_rcOld, &rcClient);
	}

	//m_pMemDC->FillSolidRect(&rcClient, RGB(0xd2,0xd2,0xd2));
	//m_pMemDC->FillSolidRect(&rcClient, RGB(0x44,0x44,0x44));
	CFont *pFont = m_pMemDC->SelectObject(&fontText);

	//画背景
	int nColor = 0;
	for (int i = rcClient.left; i < rcClient.right; i ++)
	{
		//m_pMemDC->FillSolidRect(i, rcClient.top + TITLEBAR_HEIGHT, i + 1, rcClient.bottom, RGB(0xbb-nColor,0xbb-nColor,0xbb-nColor));
		//m_pMemDC->FillSolidRect(i, rcClient.top + TITLEBAR_HEIGHT, i + 1, rcClient.bottom, RGB(0xcd-nColor,0xcd-nColor,0xcd-nColor));
		//m_pMemDC->FillSolidRect(i, rcClient.top + TITLEBAR_HEIGHT, i + 1, rcClient.bottom, RGB(0x5e-nColor,0x5e-nColor,0x5e-nColor));
		//m_pMemDC->FillSolidRect(i, rcClient.top, i + 1, rcClient.bottom, RGB(0x60-nColor,0x60-nColor,0x60-nColor));

		//if ( i  %  20 == 0)			nColor ++;
	}

	m_pMemDC->FillSolidRect(&rcClient, RGB(0x55,0x58,0x53));

	//rcClient.right -= 1;
	//rcClient.bottom -= 1;
	//m_pMemDC->Draw3dRect(&rcClient, RGB(0x88,0x88,0x88), RGB(0x6d,0x6d,0x6d));
	//m_pMemDC->Draw3dRect(&rcClient, RGB(0x2a,0x2a,0x2a), RGB(0x2a,0x2a,0x2a));
	//rcClient.right += 1;
	//rcClient.bottom += 1;

	//速度
	m_rcSpeed.SetRect(rcClient.right, rcClient.top, rcClient.right, rcClient.bottom);
	m_pMemDC->FillSolidRect(&m_rcSpeed, RGB(0xaa,0xaa,0xaa));
	m_pMemDC->TextOut(m_rcSpeed.left-10, m_rcSpeed.top-2, TEXT("－"));
	m_pMemDC->TextOut(m_rcSpeed.right, m_rcSpeed.top-2, TEXT("＋"));
	if (m_rcSpeed2.IsRectEmpty())
	{
		if (nSpeed>=99)	nSpeed = 100;
		m_rcSpeed2.SetRect(m_rcSpeed.left, m_rcSpeed.top+2, (int)((m_rcSpeed.left+(float)m_rcSpeed.Width()/(float)100.0f*(nSpeed))), m_rcSpeed.bottom-2);
	}
	if ( ! m_rcSpeed2.IsRectEmpty())
	{
		int nColor = 0;
		CRect	rcTmp;
		for (int i = m_rcSpeed2.left; i < m_rcSpeed2.right; i ++)
		{
			rcTmp.SetRect(i, m_rcSpeed2.top, i + 1, m_rcSpeed2.bottom);
			//m_pMemDC->FillSolidRect(i, rcClient.top + TITLEBAR_HEIGHT, i + 1, rcClient.bottom, RGB(0xbb-nColor,0xbb-nColor,0xbb-nColor));
			//m_pMemDC->FillSolidRect(i, rcClient.top + TITLEBAR_HEIGHT, i + 1, rcClient.bottom, RGB(0xcd-nColor,0xcd-nColor,0xcd-nColor));
			//m_pMemDC->FillSolidRect(i, rcClient.top + TITLEBAR_HEIGHT, i + 1, rcClient.bottom, RGB(0x5e-nColor,0x5e-nColor,0x5e-nColor));
			m_pMemDC->FillSolidRect(&rcTmp, RGB(0xf7-nColor,0x7b-nColor,0x32-nColor));

			//if ( i  %  20 == 0)			nColor ++;
		}

		//m_pMemDC->FillSolidRect(&m_rcSpeed2,  RGB(0xff,0x80,0x00));
		wchar_t wszSpeed[16] = {0};
		wsprintf(wszSpeed, TEXT("%d"), nSpeed);
		m_pMemDC->DrawText(wszSpeed, (int)wcslen(wszSpeed), &m_rcSpeed, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}

	m_pMemDC->SelectObject(pFont);

	m_pDC->BitBlt(rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, m_pMemDC, 0, 0, SRCCOPY);
}



void CMyProgressCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (PtInRect(&m_rcSpeed, point) && bDragSpeed)
	{
		float fPercent = (float)(point.x-m_rcSpeed.left) / (float)(m_rcSpeed.right-m_rcSpeed.left);
		//nSpeed = (int)(fPercent*100.0f)+1;
		nSpeed = (int)(fPercent*100.0f)+1;
		if (nSpeed>=99)	nSpeed = 100;
		//nSpeed = (int)((float)(point.x-rcSpeed.left)/(float)(rcSpeed.right-rcSpeed.left))*100.0f;

		m_rcSpeed2.SetRect(m_rcSpeed.left, m_rcSpeed.top+2, point.x, m_rcSpeed.bottom-2);
		//nSpeed = point.x-rcSpeed.left;
		Invalidate();

		::PostMessage(m_MsgHwnd, WM_PTZ_SPEED_SET, 0, nSpeed);
		
	}

	bDragSpeed = false;

	CWnd::OnLButtonUp(nFlags, point);
}
void CMyProgressCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{

	if (PtInRect(&m_rcSpeed, point))
	{
		bDragSpeed = true;
	}

	CWnd::OnLButtonDown(nFlags, point);
}
BOOL CMyProgressCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	return CWnd::OnEraseBkgnd(pDC);
}
void CMyProgressCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (PtInRect(&m_rcSpeed, point) && bDragSpeed)
	{
		float fPercent = (float)(point.x-m_rcSpeed.left) / (float)(m_rcSpeed.right-m_rcSpeed.left);
		//nSpeed = (int)(fPercent*100.0f)+1;
		nSpeed = (int)(fPercent*100.0f)+1;
		if (nSpeed>=99)	nSpeed = 100;
		//nSpeed = (int)((float)(point.x-rcSpeed.left)/(float)(rcSpeed.right-rcSpeed.left))*100.0f;

		m_rcSpeed2.SetRect(m_rcSpeed.left, m_rcSpeed.top+2, point.x, m_rcSpeed.bottom-2);
		//nSpeed = point.x-rcSpeed.left;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}

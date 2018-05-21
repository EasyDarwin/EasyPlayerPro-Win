// DialogBase.cpp : implementation file
//

#include "stdafx.h"
#include "DialogBase.h"
#include "afxdialogex.h"
//#include "gui_common.h"

// CDialogBase dialog

IMPLEMENT_DYNAMIC(CDialogBase, CDialogEx)

CDialogBase::CDialogBase(UINT nIDTemplate, CWnd* pParent /*=NULL*/, wchar_t *pwszTitle)
	: CDialogEx(nIDTemplate, pParent)
{
	//fontText.CreateFontW(GUI_TEXT_FONT_SIZE, 0, 0, 0, 500, FALSE, FALSE, 0, 0, 0, 0, 0, 0, TEXT("Arial"));
	fontText.CreateFontW(15, 0, 0, 0, 500, FALSE, FALSE, 0, 0, 0, 0, 0, 0, TEXT("Arial"));
	brushTitlebar.CreateSolidBrush(RGB(0x3a,0x3a,0x3a));
	penBorder.CreatePen(PS_SOLID, 3, RGB(0xcc,0x66,0x00));
	penBorderSel.CreatePen(PS_SOLID, 3, RGB(0x41,0x41,0x41));
	m_pDC		=	NULL;
	m_pMemDC	=	NULL;
	m_pBmpDC	=	NULL;
	m_pBmp		=	NULL;

	m_BrushBtn = ::CreateSolidBrush(DIALOG_BASE_BACKGROUND_COLOR);
	m_BrushEdt = ::CreateSolidBrush(RGB(0xef,0xef,0xef));
	m_BrushStatic = ::CreateSolidBrush(DIALOG_BASE_BACKGROUND_COLOR);
	SetRectEmpty(&m_rcButton);
	

	bInit		=	false;
	memset(wszTitle, 0x00, sizeof(wszTitle));
	if (NULL != pwszTitle)
	{
		wcscpy(wszTitle, pwszTitle);
	}

	pStaticTitlebar	=	NULL;
}

CDialogBase::~CDialogBase()
{

	if (NULL != m_pBmp)
	{
		m_pBmp->DeleteObject();
		delete m_pBmp;
		m_pBmp = NULL;
	}
	if (NULL != m_pBmpDC)
	{
		m_pBmpDC->DeleteDC();
		delete m_pBmpDC;
		m_pBmpDC = NULL;
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
	//fontTitle.DeleteObject();
	penBorder.DeleteObject();
	penBorderSel.DeleteObject();
	fontText.DeleteObject();
	brushTitlebar.DeleteObject();

	DeleteObject(m_BrushBtn);
	DeleteObject(m_BrushEdt);
	DeleteObject(m_BrushStatic);

	
}

void CDialogBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogBase, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CDialogBase message handlers


void CDialogBase::DrawBackground()
{
	RECT rcClient;
	GetClientRect(&rcClient);
	if (IsRectEmpty(&rcClient))		return;

	if (hasTitleBar())		//需画标题栏
	{
		CRect	rcTitlebar;
		rcTitlebar.SetRect(rcClient.left, rcClient.top, rcClient.right, rcClient.top+20);
		__MOVE_WINDOW(pStaticTitlebar, rcTitlebar);
	}

	if (bInit)	UpdateComponents(rcClient);

	if (HasButton() && bInit)
	{
		if (NULL == m_pDC)		m_pDC = GetDC();
		if (NULL == m_pDC)		return;

		if (NULL == m_pMemDC)
		{
			m_pMemDC = new CDC();
			m_pMemDC->CreateCompatibleDC(m_pDC);
			m_pMemDC->SetTextColor(RGB(0xfd,0xfd,0xfd));
		}
		if (NULL == m_pBmpDC)
		{
			m_pBmpDC = new CDC();
			m_pBmpDC->CreateCompatibleDC(m_pDC);
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
			m_pMemDC->FillSolidRect(&rcClient, DIALOG_BASE_BACKGROUND_COLOR);

			CopyRect(&m_rcOld, &rcClient);
		}

		m_rcButton.SetRect(rcClient.right-20, rcClient.top, rcClient.right, rcClient.top+20);
		DrawTitlebar(m_pMemDC, m_rcButton);

		m_pDC->BitBlt(rcClient.right-20, rcClient.top, rcClient.right, rcClient.bottom, m_pMemDC, 0, 0, SRCCOPY);
	}

#if 0


	if (NULL == m_pDC)		m_pDC = GetDC();
	if (NULL == m_pDC)		return;

	if (NULL == m_pMemDC)
	{
		m_pMemDC = new CDC();
		m_pMemDC->CreateCompatibleDC(m_pDC);
		m_pMemDC->SetTextColor(RGB(0xfd,0xfd,0xfd));
	}
	if (NULL == m_pBmpDC)
	{
		m_pBmpDC = new CDC();
		m_pBmpDC->CreateCompatibleDC(m_pDC);
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
		m_pMemDC->FillSolidRect(&rcClient, RGB(0x0a,0x0a,0x0a));//RGB(0x36,0x36,0x36));

		CopyRect(&m_rcOld, &rcClient);
	}

	

	CFont *pFont = m_pMemDC->SelectObject(&fontText);

	int nStatus = 0;

	bool bInSession = false;
	//bInSession = avcore.InSession();
	COLORREF bkColor = RGB(0x7c,0x7c,0x7c);
	if (nStatus>0 || !bInSession)
	{
		if (hasTitleBar())		//需画标题栏
		{
			CRect	rcTitlebar;
			rcTitlebar.SetRect(rcClient.left, rcClient.top, rcClient.right, rcClient.top+20);
			m_pMemDC->FillSolidRect(&rcTitlebar, RGB(0x53,0x53,0x53));
			m_pMemDC->DrawText(wszTitle,  &rcTitlebar, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

			CRect	rcBk;
			rcBk.SetRect(rcTitlebar.left, rcTitlebar.bottom, rcTitlebar.right, rcClient.bottom);
			m_pMemDC->FillSolidRect(&rcBk, bkColor);
		}
		else
		{
			m_pMemDC->FillSolidRect(&rcClient, bkColor);
		}
	}

	m_pMemDC->SelectObject(pFont);

	m_pDC->BitBlt(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, m_pMemDC, 0, 0, SRCCOPY);

#endif

	
}

BOOL CDialogBase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBackgroundColor(DIALOG_BASE_BACKGROUND_COLOR);

	InitialComponents();
	bInit = true;

	CreateComponents();
	
	if (NULL != pStaticTitlebar)
	{
		pStaticTitlebar->SetWindowText(wszTitle);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


LRESULT CDialogBase::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_PAINT == message || WM_SIZE==message)
	{
		DrawBackground();
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


BOOL CDialogBase::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	if (bInit)
	{
		DeleteComponents();
	}

	return CDialogEx::DestroyWindow();
}

BOOL CDialogBase::OnEraseBkgnd(CDC* pDC)
{
	//return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


HBRUSH CDialogBase::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何特性
	//HBRUSH	m_BrushBtn;
	//HBRUSH	m_BrushEdt;
	//HBRUSH	m_BrushStatic;
#if 1

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE_BAR)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&fontText);
		pDC->SetTextColor(RGB(0xf3,0xf3,0xf3));//DIALOG_BASE_TEXT_COLOR);
		return brushTitlebar;
	}

	//pDC->SetBkMode(TRANSPARENT);
	switch (nCtlColor)
	{
	case CTLCOLOR_BTN:	//按钮
		{
			return m_BrushBtn;
		}
		break;
		case CTLCOLOR_EDIT:	//编辑框
		{
			//pDC->SelectObject(&fontText);
			pDC->SetTextColor(DIALOG_BASE_TEXT_COLOR);
			return m_BrushEdt;
		}
		break;
	case CTLCOLOR_STATIC:	
		{
			
			pDC->SetBkColor(DIALOG_BASE_BACKGROUND_COLOR);
			pDC->SetTextColor(DIALOG_BASE_TEXT_COLOR);
			return m_BrushStatic;
		}
		break;
	default:
		break;
	}
#endif
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}



void CDialogBase::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (AllowDrag())
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	}

	if (PtInRect(&m_rcButton, point))
	{
		OnShowPanel();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

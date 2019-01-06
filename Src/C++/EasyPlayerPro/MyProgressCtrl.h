#pragma once


class CMyProgressCtrl : public CWnd
{
	DECLARE_DYNAMIC(CPTZCtrl)

public:
	CMyProgressCtrl();
	virtual ~CMyProgressCtrl();

	BOOL Create(DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, char *title, int msg, HWND recvMsgHwnd);

protected:
	DECLARE_MESSAGE_MAP()

	HWND	m_MsgHwnd;
	int		m_Msg;

	CFont	fontTitle;
	CFont	fontText;
	CBrush	brushEnabled;
	CBrush	brushDisabled;
	CDC		*m_pDC;
	CDC		*m_pMemDC;
	CBitmap *m_pBmp;
	RECT	m_rcOld;
	CDC		*m_pMemBMPDC;
	CRect	m_rcSpeed;
	CRect	m_rcSpeed2;
	bool	bDragSpeed;
	int		nSpeed;
	int		nPreset;


	void DrawLine(CDC *pDC, int left, int top, int right, int bottom);
	void DrawLine(CDC *pDC, RECT rect);

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};



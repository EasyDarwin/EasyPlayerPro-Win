#pragma once


// CEasyProgressCtrl

class CEasyProgressCtrl : public CWnd
{
	DECLARE_DYNAMIC(CEasyProgressCtrl)

public:
	CEasyProgressCtrl();
	virtual ~CEasyProgressCtrl();

	void	SetRange(int minVal, int maxVal);
	void	SetPos(int val, bool playing=true);

private:
	CFont	fontText;
	bool		bDrag;
	CRect	mRcRange;
	int		mMinVal, mMaxVal, mPos;
	wchar_t		wszProgressLabel[36];

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};



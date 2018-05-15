#pragma once


// CDialogBase dialog

#define		DIALOG_BASE_BACKGROUND_COLOR		RGB(0x95,0x95,0x95)
#define		DIALOG_BASE_TEXT_COLOR				RGB(0x20,0x20,0x20)

class CDialogBase : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBase)

public:
	CDialogBase(UINT nIDTemplate, CWnd* pParent = NULL, wchar_t *pwszTitle=NULL);   // standard constructor
	virtual ~CDialogBase();


// Dialog Data
	//enum { IDD = IDD_DIALOGBASE };

private:
	virtual void	InitialComponents()	=	0;
	virtual void	CreateComponents()	=	0;
	virtual void	UpdateComponents(CRect rect)	=	0;
	virtual void	DeleteComponents()	=	0;
	virtual bool	AllowDrag()	=	0;
	virtual bool	hasTitleBar()	=	0;
	virtual bool HasButton()	=	0;
	virtual void DrawTitlebar(CDC *pWindowDC, CRect rcTitlebar)	=	0;
	virtual void	OnShowPanel()	=	0;

	bool	bInit;
protected:
	CFont	fontTitle;
	CFont	fontText;
	CBrush	brushTitlebar;
	CPen	penBorder;
	CPen	penBorderSel;
	CDC		*m_pDC;
	CDC		*m_pMemDC;
	CDC		*m_pBmpDC;
	CBitmap *m_pBmp;
	RECT	m_rcOld;

	
	HBRUSH	m_BrushBtn;
	HBRUSH	m_BrushEdt;
	HBRUSH	m_BrushStatic;

	CStatic	*pStaticTitlebar;		//IDC_STATIC_TITLE_BAR
	CRect	m_rcButton;

	wchar_t	wszTitle[128];
	void DrawBackground();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL DestroyWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#pragma once


// CDlgFileToolbar dialog

class CDlgFileToolbar : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFileToolbar)

public:
	CDlgFileToolbar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgFileToolbar();

public:
	void	SetMaxTime(int duration);
	void	SetCurrentTime(int secs);

// Dialog Data
	enum { IDD = IDD_DIALOG_FILE_TOOLBAR };

private:
	CSliderCtrl		*pSliderProgress;		//IDC_SLIDER_PROGRESS
	CStatic			*pStaticTime;				//IDC_STATIC_TIME
	HBRUSH		m_BrushStatic;
	void	UpdateComponents();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};

#pragma once


// CDlgCaption dialog

class CDlgBarCaption : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBarCaption)

public:
	CDlgBarCaption(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgBarCaption();

// Dialog Data
	enum { IDD = IDD_DIALOGBAR_CAPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

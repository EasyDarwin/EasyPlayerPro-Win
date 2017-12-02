#pragma once


// CCaption dialog

class CCaption : public CDialogEx
{
	DECLARE_DYNAMIC(CCaption)

public:
	CCaption(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCaption();

// Dialog Data
	enum { IDD = IDD_CAPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//    CEdit m_CaptionText;
    CString m_strCaption;
};

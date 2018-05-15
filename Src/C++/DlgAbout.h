#pragma once


// CDlgAbout dialog

class CDlgAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAbout)

public:
	CDlgAbout(wchar_t *pVer, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAbout();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };


private:
	wchar_t		*pwszVerPtr;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

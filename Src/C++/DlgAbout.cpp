// DlgAbout.cpp : implementation file
//

#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "DlgAbout.h"
#include "afxdialogex.h"


// CDlgAbout dialog

IMPLEMENT_DYNAMIC(CDlgAbout, CDialogEx)

CDlgAbout::CDlgAbout(wchar_t *pVer, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAbout::IDD, pParent)
{
	pwszVerPtr = pVer;
}

CDlgAbout::~CDlgAbout()
{
}

void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialogEx)
END_MESSAGE_MAP()


// CDlgAbout message handlers


BOOL CDlgAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CWnd *pWnd = GetDlgItem(IDC_STATIC_VER);
	if (NULL != pWnd)
	{
		pWnd->SetWindowTextW(pwszVerPtr);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

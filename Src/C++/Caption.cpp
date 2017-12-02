// Caption.cpp : implementation file
//

#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "Caption.h"
#include "afxdialogex.h"


// CCaption dialog

IMPLEMENT_DYNAMIC(CCaption, CDialogEx)

CCaption::CCaption(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCaption::IDD, pParent)
{

    m_strCaption = _T("");
}

CCaption::~CCaption()
{
}

void CCaption::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    //  DDX_Control(pDX, IDC_EDIT_CAPTION, m_CaptionText);
    DDX_Text(pDX, IDC_EDIT_CAPTION, m_strCaption);
}


BEGIN_MESSAGE_MAP(CCaption, CDialogEx)
END_MESSAGE_MAP()


// CCaption message handlers

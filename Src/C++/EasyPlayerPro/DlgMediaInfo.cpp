// DlgMediaInfo.cpp : implementation file
//

#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "DlgMediaInfo.h"
#include "afxdialogex.h"

#include "gui_common.h"

// CDlgMediaInfo dialog

IMPLEMENT_DYNAMIC(CDlgMediaInfo, CDialogBase)

CDlgMediaInfo::CDlgMediaInfo(MediaInfo *pMediaInfo, CWnd* pParent /*=NULL*/)
	: CDialogBase(CDlgMediaInfo::IDD, pParent)
{
	m_pMediaInfoPtr = pMediaInfo;
}

CDlgMediaInfo::~CDlgMediaInfo()
{
}

void CDlgMediaInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMediaInfo, CDialogBase)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgMediaInfo::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// CDlgMediaInfo message handlers
void	CDlgMediaInfo::InitialComponents()
{
	pEdtVideoCodec		=	NULL;
	pEdtVideoResolution	=	NULL;
	pEdtAudioCodec		=	NULL;
	pEdtAudioSamplerate	=	NULL;
	pEdtAudioBitsPerSample=	NULL;
	pEdtAudioChannels = NULL;
}
void	CDlgMediaInfo::CreateComponents()
{
	__CREATE_WINDOW(pEdtVideoCodec, CEdit, IDC_EDIT_VIDEO_CODEC);
	__CREATE_WINDOW(pEdtVideoResolution, CEdit, IDC_EDIT_VIDEO_RESOLUTION);
	__CREATE_WINDOW(pEdtAudioCodec, CEdit, IDC_EDIT_AUDIO_CODEC);
	__CREATE_WINDOW(pEdtAudioSamplerate, CEdit, IDC_EDIT_AUDIO_SAMPLERATE);
	__CREATE_WINDOW(pEdtAudioBitsPerSample, CEdit, IDC_EDIT_AUDIO_BITSPERSAMPLE);
	__CREATE_WINDOW(pEdtAudioChannels, CEdit, IDC_EDIT_AUDIO_CHANNELS);
	

	char szResolution[24] = {0};
	sprintf(szResolution, "%d x %d", m_pMediaInfoPtr->nWidth, m_pMediaInfoPtr->nHeight);

	SetTextToEdit(pEdtVideoCodec, m_pMediaInfoPtr->sVCodec);
	SetTextToEdit(pEdtVideoResolution, szResolution);

	SetTextToEdit(pEdtAudioCodec, m_pMediaInfoPtr->sACodec);
	SetTextToEdit(pEdtAudioSamplerate, m_pMediaInfoPtr->nSampleRate);
	SetTextToEdit(pEdtAudioBitsPerSample, m_pMediaInfoPtr->nBitsPerSample==0?16: m_pMediaInfoPtr->nBitsPerSample);
	SetTextToEdit(pEdtAudioChannels, m_pMediaInfoPtr->nChannels==1?"单声道":"立体声");
}
void	CDlgMediaInfo::UpdateComponents(CRect rect)
{

}
void	CDlgMediaInfo::DeleteComponents()
{

}
bool	CDlgMediaInfo::AllowDrag()
{
	return true;
}
bool	CDlgMediaInfo::hasTitleBar()
{
	return true;
}
bool CDlgMediaInfo::HasButton()
{
	return true;
}
void CDlgMediaInfo::DrawTitlebar(CDC *pWindowDC, CRect rcTitlebar)
{

}
void	CDlgMediaInfo::OnShowPanel()
{

}

void CDlgMediaInfo::OnBnClickedButtonOk()
{
	OnOK();
}

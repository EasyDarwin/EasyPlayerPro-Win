// DlgMediaInfo.cpp : implementation file
//

#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "DlgMediaInfo.h"
#include "afxdialogex.h"

#include "gui_common.h"

// CDlgMediaInfo dialog

IMPLEMENT_DYNAMIC(CDlgMediaInfo, CDialogBase)

CDlgMediaInfo::CDlgMediaInfo(EASY_MEDIA_INFO_T *pMediaInfo, CWnd* pParent /*=NULL*/)
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
}
void	CDlgMediaInfo::CreateComponents()
{
	__CREATE_WINDOW(pEdtVideoCodec, CEdit, IDC_EDIT_VIDEO_CODEC);
	__CREATE_WINDOW(pEdtVideoResolution, CEdit, IDC_EDIT_VIDEO_RESOLUTION);
	__CREATE_WINDOW(pEdtAudioCodec, CEdit, IDC_EDIT_AUDIO_CODEC);
	__CREATE_WINDOW(pEdtAudioSamplerate, CEdit, IDC_EDIT_AUDIO_SAMPLERATE);
	__CREATE_WINDOW(pEdtAudioBitsPerSample, CEdit, IDC_EDIT_AUDIO_BITSPERSAMPLE);

	char szVideoCodec[16] = {0};
	if (m_pMediaInfoPtr->videoCodec == VIDEO_CODEC_H264)			strcpy(szVideoCodec, "H264");
	else if (m_pMediaInfoPtr->videoCodec == VIDEO_CODEC_H265)		strcpy(szVideoCodec, "H265");
	else if (m_pMediaInfoPtr->videoCodec == VIDEO_CODEC_MJPEG)		strcpy(szVideoCodec, "MJPEG");
	else if (m_pMediaInfoPtr->videoCodec == VIDEO_CODEC_MPEG4)		strcpy(szVideoCodec, "MPEG4");
	char szResolution[24] = {0};
	sprintf(szResolution, "%d x %d", m_pMediaInfoPtr->videoWidth, m_pMediaInfoPtr->videoHeight);


	char szAudioCodec[16] = {0};
	if (m_pMediaInfoPtr->audioCodec == AUDIO_CODEC_MP4A)			strcpy(szAudioCodec, "AAC");
	else if (m_pMediaInfoPtr->audioCodec == AUDIO_CODEC_PCMU)		strcpy(szAudioCodec, "G711-ulaw");
	else if (m_pMediaInfoPtr->audioCodec == AUDIO_CODEC_PCMA)		strcpy(szAudioCodec, "G711-alaw");
	else if (m_pMediaInfoPtr->audioCodec == AUDIO_CODEC_G726)		strcpy(szAudioCodec, "G726");
	else if (m_pMediaInfoPtr->audioCodec == AUDIO_CODEC_MP3)		strcpy(szAudioCodec, "MP3");




	SetTextToEdit(pEdtVideoCodec, szVideoCodec);
	SetTextToEdit(pEdtVideoResolution, szResolution);

	SetTextToEdit(pEdtAudioCodec, szAudioCodec);
	SetTextToEdit(pEdtAudioSamplerate, m_pMediaInfoPtr->audioSampleRate);
	SetTextToEdit(pEdtAudioBitsPerSample, m_pMediaInfoPtr->audioBitsPerSample);
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

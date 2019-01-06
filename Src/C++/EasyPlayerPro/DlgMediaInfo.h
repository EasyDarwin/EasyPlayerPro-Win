#pragma once


#include "DialogBase.h"
#include "../libEasyPlayerPro/EasyDefine.h"
// CDlgMediaInfo dialog

class CDlgMediaInfo : public CDialogBase
{
	DECLARE_DYNAMIC(CDlgMediaInfo)

public:
	CDlgMediaInfo(MediaInfo *pMediaInfo, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMediaInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_MEDIA_INFO };

private:
	virtual void	InitialComponents();
	virtual void	CreateComponents();
	virtual void	UpdateComponents(CRect rect);
	virtual void	DeleteComponents();
	virtual bool	AllowDrag();
	virtual bool	hasTitleBar();
	virtual bool HasButton();
	virtual void DrawTitlebar(CDC *pWindowDC, CRect rcTitlebar);
	virtual void	OnShowPanel();


	CEdit		*pEdtVideoCodec;				//IDC_EDIT_VIDEO_CODEC
	CEdit		*pEdtVideoResolution;			//IDC_EDIT_VIDEO_RESOLUTION

	CEdit		*pEdtAudioCodec;				//IDC_EDIT_AUDIO_CODEC
	CEdit		*pEdtAudioSamplerate;			//IDC_EDIT_AUDIO_SAMPLERATE
	CEdit		*pEdtAudioBitsPerSample;		//IDC_EDIT_AUDIO_BITSPERSAMPLE
	CEdit		*pEdtAudioChannels;		//IDC_EDIT_AUDIO_BITSPERSAMPLE


	MediaInfo	*m_pMediaInfoPtr;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOk();
};

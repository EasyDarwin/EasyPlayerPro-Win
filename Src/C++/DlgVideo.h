#pragma once

#include "DlgRender.h"
#include "DlgFileToolbar.h"
// CDlgVideo 对话框

#define		DIALOG_BASE_BACKGROUND_COLOR		RGB(0x75,0x75,0x75)
#define		DIALOG_BASE_TEXT_COLOR				RGB(0x20,0x20,0x20)

#define		WM_RECORDING_CMPLETE		(WM_USER+10001)


class CDlgVideo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVideo)

public:
	CDlgVideo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVideo();


	void	OpenHikNvrRealStream();
	void	OpenHIKNVR_Playback();
	void	PlayStreamFile();


	void	SetWindowId(int _windowId);
	void	SetShownToScale(int shownToScale);
	void	SetMultiplex(unsigned char multiplex);
	void	SetURL(char *url, int scale, int osd, int tcp, int multiple, int cache, int showToolbar, int autoplay);
	void	OnMouseWheel(short zDelta, CPoint pt);

	bool	bDrag;
	int		shownToScale;

	int		m_WindowId;
	int		m_ChannelId;
	unsigned char	sourceMultiplex;	//源复用
	CDlgRender	*pDlgRender;
	CEdit	*pEdtURL;		//IDC_EDIT_RTSP_URL
	CButton	*pChkOSD;		//IDC_CHECK_OSD
	CButton *pChkTCP;		//IDC_CHECK_TCP
	CSliderCtrl	*pSliderCache;	//IDC_SLIDER_CACHE
	CButton	*pBtnPreview;	//IDC_BUTTON_PREVIEW
	CDlgFileToolbar		*pDlgFileToolbar;
	void	InitialComponents();
	void	CreateComponents();
	void	UpdateComponents();
	void	DeleteComponents();

	HBRUSH	m_BrushBtn;
	HBRUSH	m_BrushEdt;
	HBRUSH	m_BrushStatic;

// 对话框数据
	enum { IDD = IDD_DIALOG_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnRecordingComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFileDuration(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSeekFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPlayComplete(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonPreview();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedCheckOsd();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

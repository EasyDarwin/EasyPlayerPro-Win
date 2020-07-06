#pragma once

#include "DlgRender.h"
#include "EasyProgressCtrl.h"
// CDlgVideo 对话框

#define		DIALOG_BASE_BACKGROUND_COLOR		RGB(0x75,0x75,0x75)
#define		DIALOG_BASE_TEXT_COLOR				RGB(0x20,0x20,0x20)

#define		WM_RECORDING_CMPLETE		(WM_USER+10001)

#define gap_char ('\\')

#define TIMER_ID_FIRST_DIALOG  1
#define TIMER_ID_PROGRESS      2
#define TIMER_RECORD_STATUS    3
#define TIMER_ID_TIME_OSD      4

class CLivePlayerDlg;

class CDlgVideo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVideo)

public:
	CDlgVideo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVideo();
	void	SetMainDlg(CLivePlayerDlg* pDlg);
	void	SetWindowId(int _windowId);
	void	SetShownToScale(int shownToScale);
	void	SetMultiplex(unsigned char multiplex);
	void	SetURL(char *url, int scale, int osd, int tcp, int multiple, int cache, int showToolbar, int autoplay);
	void	OnMouseWheel(short zDelta, CPoint pt);
	void	ShowToolbar(bool bShow);
	void    SetVolume(int nValue);

	bool	bDrag;
	int		shownToScale;
	CLivePlayerDlg* m_pMainDlg;
	int		m_WindowId;
	int		m_ChannelId;
	unsigned char	sourceMultiplex;	//源复用
	CDlgRender	*pDlgRender;
	CEdit	*pEdtURL;		//IDC_EDIT_RTSP_URL
	CButton	*pChkOSD;		//IDC_CHECK_OSD
	CButton *pChkTCP;		//IDC_CHECK_TCP
	CSliderCtrl	*pSliderCache;	//IDC_SLIDER_CACHE
	CButton	*pBtnPreview;	//IDC_BUTTON_PREVIEW
	CEasyProgressCtrl	*pProgressCtrl;	//
	void	InitialComponents();
	void	CreateComponents();
	void	UpdateComponents();
	void	DeleteComponents();

	HBRUSH	m_BrushBtn;
	HBRUSH	m_BrushEdt;
	HBRUSH	m_BrushStatic;

	int m_nVideoWidth;
	int m_nVideoHeight;

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
	afx_msg LRESULT OnShowToolbar(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOpenFilePlay(WPARAM wParam, LPARAM lParam);

public:
	//播放器逻辑变量
	Easy_PlayerPro_Handle m_hPlayer;
	EASY_CHANNEL_SOURCE_TYPE_ENUM	m_sourceType;

	LONGLONG m_totalDuration;
	CString  m_strPlayFileTime;
	BOOL  m_bPlayPause;
	RECT  m_rtClient;
	int   m_lRecordTime;
	long  m_lRecordSliceUp;//录像切片ID
	BOOL  m_bRecording;
	BOOL  m_bOpening;
	//全屏
	BOOL  m_bFullScreen;
	CWnd* m_pWndSave;
	WINDOWPLACEMENT m_wpmSave;
	WINDOWPLACEMENT m_mainSave;
	//播放速度调节
	int   m_speedRate;
	int   m_nVolume;
	BOOL  m_bLoopPlay;
public:
	void OnResizeVideoWnd();
	void OnEffectMode(int nInMode);

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
	//afx_msg LRESULT OnDBL(WPARAM, LPARAM);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	static int _stdcall EasyPlayerProCallBack(EASY_CALLBACK_TYPE_ENUM callbackType, void *userPtr, int mediaType, char *pbuf, EASY_FRAME_INFO *frameInfo);
};

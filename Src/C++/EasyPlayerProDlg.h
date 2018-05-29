#pragma once

#include "DlgVideo.h"

#define	_SURV_MAX_WINDOW_NUM		16

typedef struct __VIDEO_NODE_T
{
	bool		fullscreen;
	int			maximizedId;
	int			selectedId;
	int			channels;
	CDlgVideo	*pDlgVideo;
}VIDEO_NODE_T;

// CLivePlayerDlg 对话框
class CLivePlayerDlg : public CDialogEx
{
// 构造
public:
	CLivePlayerDlg(CWnd* pParent = NULL);	// 标准构造函数


public:
	CComboBox		*pComboxSplitScreen;
	CComboBox		*pComboxRenderFormat;	//IDC_COMBO_RENDER_FORMAT
	VIDEO_NODE_T	*pVideoWindow;		//视频窗口
	CButton			*pChkShownToScale;	//按比例显示
	CButton			*pChkMultiplex;		//源复用	IDC_CHECKMULTIPLEX
	CButton			*pChkFullScreen;	//IDC_CHECK_FULLSCREEN
	CStatic			*pStaticVolume;			//IDC_STATIC_VOLUME
	CSliderCtrl		*pSliderCtrlVolume;	//IDC_SLIDER_VOLUME
	CStatic			*pStaticCopyright;	//IDC_STATIC_COPYRIGHT

	void	InitialComponents();
	void	CreateComponents();
	void	UpdateComponents();
	void	DeleteComponents();
	void	UpdateVideoPosition(LPRECT lpRect);
	void	FullScreen();
	HBRUSH	m_BrushStatic;
	CRect m_rcVideoSingle;
	BOOL M_bMaxWnd;

	void GetApplicationVersion(wchar_t *pVersion);

// 对话框数据
	enum { IDD = IDD_PLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	LRESULT OnWindowMaximized(WPARAM wParam, LPARAM lParam);
	LRESULT OnExitFullScreen(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL DestroyWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnCbnSelchangeComboSplitScreen();
	afx_msg void OnCbnSelchangeComboRenderFormat();
	afx_msg void OnBnClickedCheckShowntoscale();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedCheckmultiplex();
	afx_msg void OnBnClickedCheckFullscreen();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

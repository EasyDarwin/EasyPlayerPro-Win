#pragma once

#include "../libEasyPlayerPro/include/EasyDefine.h"
#include "../libEasyPlayerPro/include/EasyPlayerProAPI.h"

typedef struct __CHANNEL_STATUS
{
	int			audio;
	int			recording;
	int			decodeKeyframeOnly;
	int			effectMode;
	int			instantReplaySave;
	int			playSpeed;				//播放速度

	int			flip;
	int			digitalZoom;
	//int			videoAnalysis;
	//int			warningMode;
	int			drag;

	int			zoneId;

	bool		bShowToolbar;
}CHANNELSTATUS;
// CDlgRender 对话框

class CDlgVideo;

class CDlgRender : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRender)

public:
	CDlgRender(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRender();

	void	ResetChannel();

	void	SetMainDlg(CDlgVideo* pDlg);
	void	SetChannelId(int _channelId)	{mChannelId = _channelId;}
	void	OnMouseWheel(short zDelta, CPoint pt);
	void	SetRecordingFlag(int flag);
	void	SetSourceType(EASY_CHANNEL_SOURCE_TYPE_ENUM sourceType);
	EASY_CHANNEL_SOURCE_TYPE_ENUM	GetSourceType()	{return mSourceType;}
	void	ShowToolbar(bool bShow)	{channelStatus.bShowToolbar = bShow;}
	bool	GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount);
	int		EnsureDirExist(CString dir);
	void HandleCommand(WORD wId);

	CDlgVideo* m_pMainDlg;
	int		mChannelId;
	CHANNELSTATUS	channelStatus;
	HMENU	hMenu;
	HMENU	hSubEffectMenu;
	void	ClosePopupMenu();
	EASY_CHANNEL_SOURCE_TYPE_ENUM	mSourceType;

	bool	mDrag;
	POINT	startPoint;
	int		scaleMultiple;	//缩放倍数
	POINT	pt_start;
	POINT	pt_start_org;

	float base_left_percent;
	float base_right_percent;
	float fWidthPercent;
	float base_top_percent;
	float base_bottom_percent;
	float fHeightPercent;
	HACCEL m_hAcc;

// 对话框数据
	enum { IDD = IDD_DIALOG_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};

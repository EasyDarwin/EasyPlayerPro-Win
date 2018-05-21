#pragma once

// EasyPlayerProActiveXPropPage.h : CEasyPlayerProActiveXPropPage 属性页类的声明。


// CEasyPlayerProActiveXPropPage : 有关实现的信息，请参阅 EasyPlayerProActiveXPropPage.cpp。

class CEasyPlayerProActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEasyPlayerProActiveXPropPage)
	DECLARE_OLECREATE_EX(CEasyPlayerProActiveXPropPage)

// 构造函数
public:
	CEasyPlayerProActiveXPropPage();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_EASYPLAYERPROACTIVEX };

// 实现
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 消息映射
protected:
	DECLARE_MESSAGE_MAP()
};


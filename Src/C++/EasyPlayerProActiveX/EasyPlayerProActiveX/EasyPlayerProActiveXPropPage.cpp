// EasyPlayerProActiveXPropPage.cpp : CEasyPlayerProActiveXPropPage 属性页类的实现。

#include "stdafx.h"
#include "EasyPlayerProActiveX.h"
#include "EasyPlayerProActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEasyPlayerProActiveXPropPage, COlePropertyPage)



// 消息映射

BEGIN_MESSAGE_MAP(CEasyPlayerProActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// 初始化类工厂和 guid

IMPLEMENT_OLECREATE_EX(CEasyPlayerProActiveXPropPage, "EASYPLAYERPROA.EasyPlayerProAPropPage.1",
	0x7e6e2fe0, 0xde0e, 0x4191, 0x84, 0x32, 0xfa, 0x80, 0xef, 0x21, 0x52, 0x72)



// CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPageFactory::UpdateRegistry -
// 添加或移除 CEasyPlayerProActiveXPropPage 的系统注册表项

BOOL CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EASYPLAYERPROACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPage - 构造函数

CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPage() :
	COlePropertyPage(IDD, IDS_EASYPLAYERPROACTIVEX_PPG_CAPTION)
{
}



// CEasyPlayerProActiveXPropPage::DoDataExchange - 在页和属性间移动数据

void CEasyPlayerProActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CEasyPlayerProActiveXPropPage 消息处理程序

#ifndef __GUI_COMMON_H__
#define __GUI_COMMON_H__


#include <winsock2.h>


#define	GUI_TITLE_FONT_SIZE				16
#define	GUI_TEXT_FONT_SIZE				15

#define PANEL_BK_COLOR				RGB(0x6b,0x6b,0x6b)//RGB(0x48,0x48,0x48)		//面板背景色
#define PANEL_MENU_ITEM_BK_COLOR	RGB(0xc0,0xc0,0xc0)//RGB(0x8b,0x8b,0x8b)//RGB(0x32,0x50,0x32)//RGB(0x79,0x79,0xff)		//面板菜单背景色
#define PANEL_MENU_ITEM_HIGHLIGHT	RGB(0xa7,0xa7,0xa7)//RGB(0x30,0x96,0x30)//RGB(0x17,0x9b,0x28)//RGB(0x26,0x9f,0x3f)//RGB(0x87,0x9d,0x85)//RGB(0xd8,0xff,0xb0)//RGB(0xa8,0xa8,0xa8)			//面板菜单背景色高亮
#define EVENT_CTRL_PANEL_BK_COLOR	RGB(0x8e,0x8e,0x8e)
#define EVENT_CTRL_ITEM_HIGHLIGHT	RGB(0x5a,0x5a,0x5a)

#define	TREE_CTRL_BK_COLOR			RGB(0xb2,0xb2,0xb2)


bool MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize);
bool WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize);

void	SetTextToEdit(CEdit *pEdt, char *value);
void	SetTextToEdit(CEdit *pEdt, int value);
void	GetTextToInt(CEdit *pEdt, int *value);
void	GetTextToChar(CEdit *pEdt, char *value, int valueSize);

#endif

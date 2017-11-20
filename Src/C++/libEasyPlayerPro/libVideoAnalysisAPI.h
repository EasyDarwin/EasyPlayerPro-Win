#ifndef __LIB_VIDEO_ANALYSIS_API_H__
#define __LIB_VIDEO_ANALYSIS_API_H__

#include "libEasyPlayerProAPI.h"
#ifdef _DEBUG1
#include "../D3DRender/VADef.h"
#else
#include "VADef.h"
#endif
	//==============================================================================
	//==============================================================================
	//==========以下为视频分析操作==================================================
	//==============================================================================
	//==============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

	//设置渲染模式  当mode设置为RENDER_MODE_ZONEANDRULE时, 显示分辨率自动缩放为 SCALE_RESOLUTION_WIDTH x SCALE_RESOLUTION_HEIGHT
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetRenderMode(PLAYER_HANDLE handle, int channelId, RENDER_MODE_ENUM mode);
	//获取渲染模式
	LIB_EASYPLAYER_PRO_API RENDER_MODE_ENUM LIB_APICALL	libVA_GetRenderMode(PLAYER_HANDLE handle, int channelId);


	//设置警戒区和屏蔽区  1为警戒区 0为屏蔽区
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningType(PLAYER_HANDLE handle, int channelId, VA_WARN_TYPE_ENUM type);
	//设置全屏警戒
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetFullWarning(int channelId);

	//设置警戒区等级
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningGrade(PLAYER_HANDLE handle, int channelId, VA_WARN_GRADE_ENUM grade);

	//显示所有警戒区域
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_ShowAllWarningArea(PLAYER_HANDLE handle, int channelId, unsigned char show);

	//添加警戒区域节点
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_AddWarningAreaNode(PLAYER_HANDLE handle, int channelId, VA_DETECT_POINT_T *p);
	//更新警戒区域节点
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_UpdateWarningAreaNode(PLAYER_HANDLE handle, int channelId, VA_DETECT_POINT_T *p);
	//结束新增警戒区域节点
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_EndWarningAreaNode(PLAYER_HANDLE handle, int channelId);

	//删除区域和线, //mode为SetWarningMode中的mode,即为检测区、检测线、方向检测区、车道
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_DeleteWarningAreaAndLine(PLAYER_HANDLE handle, int channelId, int mode, int delete_all, int areaOrLineId);

	//根据新增时的百分比, 对照当前的rect,更新位置点
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_UpdateWarningAreaPosition(PLAYER_HANDLE handle, int channelId, LPRECT lpRect);

	//获取警戒区列表
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_GetWarningAreaList(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T **list);
	//设置警戒区列表
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningAreaList(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T *list, int num);
	//设置警戒线方向
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningLineDirection(PLAYER_HANDLE handle, int channelId, VA_DIRECTION_ENUM _direction);
	//根据警戒线id 修改警戒线方向
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningLineDirectionById(PLAYER_HANDLE handle, int channelId, int lineId, VA_DIRECTION_ENUM _direction);
	//获取警戒线列表
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_GetWarningLineList(PLAYER_HANDLE handle, int channelId, VA_DETECT_LINE_LIST_T **list);
	//设置警戒线列表
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningLineList(PLAYER_HANDLE handle, int channelId, VA_DETECT_LINE_LIST_T *list, int num);



	//添加自定义区域
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_AddCustomZoneNode(PLAYER_HANDLE handle, int channelId, int id, char *name, 
															VA_DETECT_POINT_T *p, unsigned char hasArrow, unsigned char fill, int minPointNum,int maxPointNum, 
															unsigned char checkOverlap, 
															COLORREF zoneColor, COLORREF borderColor, COLORREF textColor, 
															int maxZoneNum, int alphaNormal, int alphaSelected);
	//移动自定义区域节点
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_MoveCustomZoneNode(PLAYER_HANDLE handle, int channelId, VA_DETECT_POINT_T *p, 
															unsigned char keyRelease/*LButtonUp事件时该值为1*/, unsigned char checkOverlap);
	//结束绘制当前自定义区域
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_EndCustomZoneNode(PLAYER_HANDLE handle, int channelId, unsigned char checkOverlap);	//结束绘制当前区域

	//删除自定义区域
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_DeleteCustomZone(PLAYER_HANDLE handle, int channelId, 
																unsigned char deleteAll, char *name, int zoneId, unsigned char updateId);	//删除区域

	//显示指定ID的自定义区域或显示全部区域
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_ShowCustomZoneById(PLAYER_HANDLE handle, int channelId, int id);				//显示全部  or 显示指定ID的区域

	//根据新增时的百分比, 对照当前的rect,更新位置点
	LIB_EASYPLAYER_PRO_API void LIB_APICALL	libVA_UpdateCustomZonePosition(PLAYER_HANDLE handle, int channelId, LPRECT lpRect);

	//获取所有自定义区域
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_GetCusromZone(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T **list, int *num);

	//设置自定义区域列表
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetCustomZone(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T *list, int num);

#ifdef __cplusplus
}
#endif


#endif

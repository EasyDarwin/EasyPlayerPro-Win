#ifndef __SYS_COMMON_H__
#define __SYS_COMMON_H__


#include <winsock2.h>

typedef struct __SYS_PARAM_T
{
	unsigned char	showVideoTitlebar;	//显示视频窗口标题栏

	unsigned int	renderFormat;
	int				frameCache;		//视频帧缓存
	int				queueSize;		//缓队队列
	unsigned char	renderMetadata;
	int				patrolTime;		//轮巡间隔时间

	int				record_filesize;	//文件大小
	int				record_times;		//文件时长
	char			szRecordingPath[MAX_PATH];
	char			szSnapshotPath[MAX_PATH];
}SYS_PARAM_T;


int		InitialSysParams();
SYS_PARAM_T *GetSysParams();
int		SaveSysParams();

#endif

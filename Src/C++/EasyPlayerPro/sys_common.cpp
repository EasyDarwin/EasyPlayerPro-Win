#include "stdafx.h"
#include "sys_common.h"
#include <stdio.h>
#include <string.h>

static SYS_PARAM_T		sysParams;



int		InitialSysParams()
{
	memset(&sysParams, 0x00, sizeof(SYS_PARAM_T));

	sysParams.showVideoTitlebar = 0x01;

	sysParams.queueSize = 1024 * 1024 * 2;
	sysParams.renderFormat = 26;	//GDI
	sysParams.frameCache = 3;
	sysParams.renderMetadata = 0x01;
	sysParams.patrolTime	=	10;

	sysParams.record_filesize  =	256;

	sysParams.renderFormat = 26;	//GDI

	return 0;
}

SYS_PARAM_T *GetSysParams()
{
	return &sysParams;
}


int		SaveSysParams()
{

	return 0;
}

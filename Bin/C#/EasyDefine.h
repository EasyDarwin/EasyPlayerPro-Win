/* 标准头文件 */
#ifndef __EASYDEFINE_H__
#define __EASYDEFINE_H__

#if defined(WIN32)
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#define  usleep(us)  Sleep((us)/1000)
#else
// todo..
#endif

//通道源类型 (指定源类型)
typedef enum __EASY_CHANNEL_SOURCE_TYPE_ENUM
{
	EASY_CHANNEL_SOURCE_TYPE_RTSP = 0,		//源为RTSP(内置)
	EASY_CHANNEL_SOURCE_TYPE_RTMP,				//源为RTMP(内置)
	EASY_CHANNEL_SOURCE_TYPE_HLS,				//源为HLS(内置)
	EASY_CHANNEL_SOURCE_TYPE_FILE,				//源为本地文件(内置)
	EASY_CHANNEL_SOURCE_TYPE_ENCODE_DATA,		//源为外部的编码数据
	EASY_CHANNEL_SOURCE_TYPE_DECODE_DATA,		//源为外部的解码数据
}EASY_CHANNEL_SOURCE_TYPE_ENUM;

//水印结构信息
// //枚举标识台标LOGO所在的位置
typedef enum tagWATER_MARK_POS
{
	POS_LEFT_TOP = 1,
	POS_RIGHT_TOP,
	POS_LEFT_BOTTOM,
	POS_RIGHT_BOTTOM

}WATER_MARK_POS;

typedef enum tagWATERMARK_ENTRY_TYPE
{
	WATERMARK_TYPE_COVER			   = 0,
	WATERMARK_TYPE_OVERLYING		   = 1,
	WATERMARK_TYPE_OVERLYING_COVER	   = 2,
	WATERMARK_TYPE_ROLL_TO_LEFT		   = 3,
	WATERMARK_TYPE_JUMP_UP_DOWN		   = 4,
	WATERMARK_TYPE_ROLL_AND_JUMP	   = 5,
	WATERMARK_TYPE_TROTTING_HORSE_LAMP = 6

}WATERMARK_ENTRY_TYPE;

typedef enum __AUTH_ERR_CODE_ENUM
{
	AUTH_INVALID_KEY = -1,			/* 无效Key */
	AUTH_TIME_ERR = -2,			/* 时间错误 */
	AUTH_PROCESS_NAME_LEN_ERR = -3,			/* 进程名称长度不匹配 */
	AUTH_PROCESS_NAME_ERR = -4,			/* 进程名称不匹配 */
	AUTH_VALIDITY_PERIOD_ERR = -5,			/* 有效期校验不一致 */
	AUTH_PLATFORM_ERR = -6,			/* 平台不匹配 */
	AUTH_COMPANY_ID_LEN_ERR = -7,			/* 授权使用商不匹配 */
	AUTH_SUCCESS = 0,			/* 激活成功 */

}AUTH_ERR_CODE_ENUM;

typedef enum tagSPEED_RATE
{
	SPEED_SLOW_X16 = -4,
	SPEED_SLOW_X8 = -3,
	SPEED_SLOW_X4 = -2,
	SPEED_SLOW_X2 = -1,
	SPEED_NORMAL = 0,
	SPEED_FAST_X2 = 1,
	SPEED_FAST_X4 = 2,
	SPEED_FAST_X8 = 3,
	SPEED_FAST_X16 = 4,
	SPEED_FAST_X64 = 5,
}SPEED_RATE;

// //字幕信息
typedef struct tagVideoTittleInfo
{
	int nState;//字幕状态：	nState==1运行；nState==0暂停；nState==-1销毁
	//设置字体等信息
	int nTittleWidth;
	int nTittleHeight;
	int nFontWeight;//权重 FW_NORMAL FW_BOLD、、、
	char strFontType[64];//字体 "华文新魏");//"华文隶书");"隶书"
	char strTittleContent[512];//字幕内容
	// 字幕颜色
	int nColorR;
	int nColorG;
	int nColorB;
	POINT ptStartPosition;//字幕绘制开始点
	int   nMoveType;//0--固定位置，1--从左往右，2--从右往左，
	BOOL bResetTittleInfo;
}VideoTittleInfo;

typedef struct tagWaterMarkInfo
{
	BOOL bIsUseWaterMark;//是否使用水印
	WATER_MARK_POS eWaterMarkPos;//台标位置：1==leftttop 2==righttop 3==leftbottom 4==rightbottom
	int nLeftTopX;//水印左上角位置x
	int nLeftTopY;//水印左上角位置y
	int nWidth;//宽
	int nHeight;//高
	char strWMFilePath[512];//水印图片路径
	WATERMARK_ENTRY_TYPE eWatermarkStyle;//水印的风格
	BOOL bResetWaterMark;

}WaterMarkInfo;

typedef struct tagMediaInfo
{
	//for stream
	int nBitsRate;
	//for Video
	int nVCodec;
	char sVCodec[32];
	char sVCodecDetails[64];
	int nWidth;
	int nHeight;
	int nFrameRate;
	int video_bit_rate;
	int video_total_bit_rate;
	//for Audio
	int nACodec;
	char sACodec[32];
	char sACodecDetails[64];
	int nSampleRate;
	int nChannels;
	int nBitsPerSample;
	int audio_bit_rate;
	//统计
	int nStatisticsFPS;
	float fStatisticsBitsrate;

}MediaInfo;

//媒体信息
typedef struct __EASY_MEDIA_INFO_T
{
	unsigned int videoCodec;			//视频编码类型
	unsigned int videoFps;				//视频帧率
	int			 videoWidth;
	int			 videoHeight;
	int		 videoBitrate;

	unsigned int audioCodec;			//音频编码类型
	unsigned int audioSampleRate;		//音频采样率
	unsigned int audioChannel;			//音频通道数
	unsigned int audioBitsPerSample;	//音频采样精度

	unsigned int metadataCodec;			//Metadata类型

	unsigned int vpsLength;				//视频vps帧长度
	unsigned int spsLength;				//视频sps帧长度
	unsigned int ppsLength;				//视频pps帧长度
	unsigned int seiLength;				//视频sei帧长度
	unsigned char	 vps[255];			//视频vps帧内容
	unsigned char	 sps[255];			//视频sps帧内容
	unsigned char	 pps[128];			//视频sps帧内容
	unsigned char	 sei[128];			//视频sei帧内容
}EASY_MEDIA_INFO_T;



#endif



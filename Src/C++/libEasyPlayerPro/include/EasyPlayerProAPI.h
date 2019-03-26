
/*
	Copyright (c) 2013-2017 EasyDarwin.ORG.  All rights reserved.
	Github: https://github.com/EasyDarwin
	WEChat: EasyDarwin
	Website: http://www.easydarwin.org
*/
#ifndef __EasyPlayerProAPI_H__
#define __EasyPlayerProAPI_H__


//++ typedefine start
#ifndef EASY_HANDLE
#define EASY_HANDLE void*
#endif//EASY_HANDLE

#ifndef Easy_PlayerPro_Handle
#define Easy_PlayerPro_Handle void*
#endif//Easy_PlayerPro_Handle

#ifndef EASY_VERYLONG
#define EASY_VERYLONG __int64
#endif//EASY_VERYLONG
//-- typedefine end


// adev render type
typedef enum tagEASY_AUDIO_RENDER_TYPE
{
	//waveout
	EASY_AUDIO_RENDER_TYPE_WAVEOUT = 0,
}EASY_AUDIO_RENDER_TYPE;

// vdev render type
typedef enum tagEASY_VIDEO_RENDER_TYPE
{
	EASY_VIDEO_RENDER_TYPE_GDI = 0,
	EASY_VIDEO_RENDER_TYPE_D3D,
//	EASY_VIDEO_RENDER_TYPE_OPENGL,
	EASY_VIDEO_RENDER_TYPE_MAX_NUM,
}EASY_VIDEO_RENDER_TYPE;

// render mode
typedef enum tagEASY_VIDEO_SCALE_MODE
{
	//拉伸充满显示区域
	EASY_VIDEO_MODE_STRETCHED,
	//按比例缩放到显示区域
	EASY_VIDEO_MODE_LETTERBOX,
	EASY_VIDEO_MODE_MAX_NUM,
}EASY_VIDEO_SCALE_MODE;

// link mode
typedef enum tagEASY_STREAM_LINK_MODE
{
	//按比例缩放到显示区域
	EASY_STREAM_LINK_UDP = 0,
	//拉伸充满显示区域
	EASY_STREAM_LINK_TCP,
	EASY_STREAM_LINK_MODE_NUM,
}EASY_STREAM_LINK_MODE;

// audio visual effect
typedef enum tagEASY_AUDIO_VISUAL_EFFECT_MODE
{
	EASY_AUDIO_VISUAL_EFFECT_DISABLE,
	EASY_AUDIO_VISUAL_EFFECT_WAVEFORM,
	EASY_AUDIO_VISUAL_EFFECT_SPECTRUM,
	EASY_AUDIO_VISUAL_EFFECT_MAX_NUM,
}EASY_AUDIO_VISUAL_EFFECT_MODE;

// hwaccel type 视频渲染硬件加速类型
typedef enum tagEASY_VIDEO_HARDWARE_ACCEL_TYPE
{
	EASY_VIDEO_HWACCEL_TYPE_NONE,
	EASY_VIDEO_HWACCEL_TYPE_DXVA2,
	EASY_VIDEO_HWACCEL_TYPE_MAX_NUM,
}EASY_VIDEO_HARDWARE_ACCEL_TYPE;

// param
typedef enum tagEASY_PARAM_ID
{
	//++ public
	// duration & position
	EASY_PARAM_MEDIA_DURATION = 0x1000,
	EASY_PARAM_MEDIA_POSITION,

	// media detail info
	EASY_PARAM_MEDIA_INFO,
	EASY_PARAM_VIDEO_WIDTH,
	EASY_PARAM_VIDEO_HEIGHT,

	// video display mode
	EASY_PARAM_VIDEO_MODE,

	// audio volume control
	EASY_PARAM_AUDIO_VOLUME,

	// playback speed control
	EASY_PARAM_PLAY_SPEED,
	EASY_PARAM_PLAY_SPEED_TYPE,

	// video decode thread count
	EASY_PARAM_DECODE_THREAD_COUNT,

	// visual effect mode
	EASY_PARAM_VISUAL_EFFECT,

	// audio/video sync diff
	EASY_PARAM_AVSYNC_TIME_DIFF,

	// player event callback
	EASY_PARAM_PLAYER_CALLBACK,

	// audio/video stream
	EASY_PARAM_AUDIO_STREAM_TOTAL,
	EASY_PARAM_VIDEO_STREAM_TOTAL,
	EASY_PARAM_SUBTITLE_STREAM_TOTAL,
	EASY_PARAM_AUDIO_STREAM_CUR,
	EASY_PARAM_VIDEO_STREAM_CUR,
	EASY_PARAM_SUBTITLE_STREAM_CUR,

	//++ for media record 
	EASY_PARAM_RECORD_TIME,
	EASY_PARAM_RECORD_PIECE_ID,
	//-- for media record
	//-- public

	//++ for audio render type
	EASY_PARAM_ADEV_RENDER_TYPE = 0x2000,
	EASY_PARAM_ADEV_GET_CONTEXT,
	EASY_PARAM_ADEV_MUTE,
	//-- for audio render type

	//++ for vdev
	EASY_PARAM_VDEV_RENDER_TYPE = 0x3000,
	EASY_PARAM_VDEV_FRAME_RATE,
	EASY_PARAM_VDEV_GET_CONTEXT,
	EASY_PARAM_VDEV_POST_SURFACE,
	EASY_PARAM_VDEV_GET_D3DDEV,
	EASY_PARAM_VDEV_D3D_ROTATE,
	//-- for vdev

	//++ for render
	EASY_PARAM_RENDER_UPDATE    = 0x4000,
	EASY_PARAM_RENDER_START_PTS,
	//-- for render

}EASY_PARAM_ID;

#ifdef __cplusplus
extern "C"
{
#endif

	// EasyPlayerPro接口函数声明
	int EasyPlayerPro_Authorize(char *license);
	Easy_PlayerPro_Handle EasyPlayerPro_Create();
	void EasyPlayerPro_Release(Easy_PlayerPro_Handle player);

	// 	EasyPlayerPro_Open     打开一个媒体流或者媒体文件进行播放，同时返回一个 player 对象指针
	// 		fileUrl				- 文件路径（可以是网络流媒体的 URL）
	// 		hWnd				- Win32 的窗口句柄/其他平台渲染显示设备句柄
	//		render_mode			- 视频渲染模式，详见EASY_VIDEO_RENDER_TYPE
	//		video_mode			- 视频显示模式，详见EASY_VIDEO_SCALE_MODE
	//		link_mode			- 流连接模式，目前只对RTSP流有效，设置rtp over tcp/udp,	详见EASY_STREAM_LINK_MODE
	//		speed				- 播放速度，0-100慢放，100以上快放
	//		valume				- 播放音量，-255 - +255
	// 		返回值				- Easy_PlayerPro_Handle 指针类型，指向 easyplayerpro 对象句柄
	Easy_PlayerPro_Handle EasyPlayerPro_Open(Easy_PlayerPro_Handle player,
		char *fileUrl, EASY_HANDLE hWnd,
		EASY_VIDEO_RENDER_TYPE render_type,
		EASY_VIDEO_SCALE_MODE  video_mode,
		EASY_STREAM_LINK_MODE  link_mode,
		int					   speed,
		int					   valume);

	// 	EasyPlayerPro_Close    关闭播放
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	void  EasyPlayerPro_Close(Easy_PlayerPro_Handle player);

	// 	EasyPlayerPro_Play     开始播放，注意：媒体流或者文件打开后不需要调用此函数即开始播放，
	// 							此函数在暂停、单步播放的时候调用，返回正常播放逻辑
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	void  EasyPlayerPro_Play(Easy_PlayerPro_Handle player);

	// 	EasyPlayerPro_StepPlay 单步播放，一次播放一帧，调用EasyPlayerPro_Play返回正常播放
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	//		type				- 单步播放类型，1-往前 2-向后
	void  EasyPlayerPro_StepPlay(Easy_PlayerPro_Handle player, int type);


	// 	EasyPlayerPro_Pause		暂停播放，调用EasyPlayerPro_Play返回正常播放
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	void  EasyPlayerPro_Pause(Easy_PlayerPro_Handle player);


	// 	EasyPlayerPro_Seek     跳转到指定位置
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		seek				- 指定位置，以毫秒为单位
	void  EasyPlayerPro_Seek(Easy_PlayerPro_Handle player, EASY_VERYLONG seek);


	// 	EasyPlayerPro_Resize   设置显示区域，有两种显示区域，视频显示区和视觉效果显示区
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		type				- 指定区域类型  0 - video rect, 1 - audio visual effect rect
	// 		x,y,width,height	- 指定显示矩形区域
	void  EasyPlayerPro_Resize (Easy_PlayerPro_Handle player, int type, int x, int y, int width, int height); 


	// 	EasyPlayerPro_Snapshot 视频播放截图
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		filePath			- 图片存放路径，以.xxx结束（xxx 目前只支持 jpeg 格式）
	// 		width, height       - 指定图片宽高，如果 <= 0 则默认使用视频宽高
	// 		waittime			- 是否等待截图完成 0 - 不等待，>0 等待超时 ms 为单位
	int   EasyPlayerPro_Snapshot(Easy_PlayerPro_Handle player, char *filePath, int width, int height, int waitTime);


	// 	EasyPlayerPro_Record   视频播放录像
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		filePath			- 图片存放路径，以.xxx结束（xxx 目前只支持 mp4 格式）
	// 		duration			- 指定图片宽高，如果 <= 0 则默认使用视频宽高
	int   EasyPlayerPro_Record (Easy_PlayerPro_Handle player, char *filePath, int duration );


	// 	EasyPlayerPro_Stoprecord 视频播放停止录像
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	int   EasyPlayerPro_Stoprecord(Easy_PlayerPro_Handle player);

	// 	EasyPlayerPro_SetLogo  设置台标/LOGO
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		bIsUse				- 是否使用水印 1=启用 0=不启用
	// 		ePos				- 台标位置：1==leftttop 2==righttop 3==leftbottom 4==rightbottom
	// 		eStyle				-  水印的风格，见WATERMARK_ENTRY_TYPE声明
	// 		x					- 水印左上角位置x坐标
	// 		y					- 水印左上角位置y坐标
	// 		width				- 宽
	// 		height				- 高
	// 		logopath			- 水印图片路径
	int   EasyPlayerPro_SetLogo (void* hplayer, int bIsUse, int ePos, int eStyle, 
		int x, int y, int width, int height, char* logopath);

	// 	EasyPlayerPro_SetOSD  设置叠加字幕
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		bIsUse				- 是否使用水印 1=启用 0=不启用 -1=删除
	// 		nMoveType			- 移动类型：0--固定位置，1--从左往右，2--从右往左，
	//		R,G,B				- 字体颜色对应三个分量红绿蓝0-255
	// 		x					- 字幕显示左上角位置x坐标
	// 		y					- 字幕显示左上角位置y坐标
	// 		weight				- 字体权重，见如下声明
											// /* Font Weights */
											// #define FW_DONTCARE         0
											// #define FW_THIN             100
											// #define FW_EXTRALIGHT       200
											// #define FW_LIGHT            300
											// #define FW_NORMAL           400
											// #define FW_MEDIUM           500
											// #define FW_SEMIBOLD         600
											// #define FW_BOLD             700
											// #define FW_EXTRABOLD        800
											// #define FW_HEAVY            900
											// #define FW_ULTRALIGHT       FW_EXTRALIGHT
											// #define FW_REGULAR          FW_NORMAL
											// #define FW_DEMIBOLD         FW_SEMIBOLD
											// #define FW_ULTRABOLD        FW_EXTRABOLD
											// #define FW_BLACK            FW_HEA
	// 		width				- 宽
	// 		height				- 高
	// 		fontname			- 字体名称，如“宋体”“楷体”“隶书”“华文行楷”......
	//		tittleContent		- OSD显示内容
	int   EasyPlayerPro_SetOSD (void *hplayer, int bIsUse, int nMoveType, int R, int G, int B,
		int weight, int x, int y, int width, int height, char* fontname, char* tittleContent);

	// 	EasyPlayerPro_Setparam 设置参数
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		param_id			- 参数ID，见EASY_PARAM_ID定义
	// 		param				- 参数指针
	void  EasyPlayerPro_Setparam(Easy_PlayerPro_Handle player, EASY_PARAM_ID param_id, EASY_HANDLE param);

	// 	EasyPlayerPro_Setparam 获取参数
	// 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
	// 		param_id			- 参数ID，见EASY_PARAM_ID定义
	// 		param				- 参数指针
	void  EasyPlayerPro_Getparam(Easy_PlayerPro_Handle player, EASY_PARAM_ID param_id, EASY_HANDLE param);


#ifdef __cplusplus
}
#endif

#endif


// 参数说明
/*
EASY_PARAM_MEDIA_DURATION 和 EASY_PARAM_MEDIA_POSITION
用于获取多媒体文件的总长度和当前播放位置（毫秒为单位）
LONGLONG total = 1, pos = 0;
EasyPlayerPro_Getparam(g_hplayer, EASY_PARAM_MEDIA_DURATION, &total);
EasyPlayerPro_Getparam(g_hplayer, EASY_PARAM_MEDIA_POSITION, &pos  );

EASY_PARAM_VIDEO_WIDTH 和 EASY_PARAM_VIDEO_HEIGHT
用于获取多媒体文件的视频宽度和高度（像素为单位）
int vw = 0, vh = 0;
EasyPlayerPro_Getparam(g_hplayer, PARAM_VIDEO_WIDTH , &vw);
EasyPlayerPro_Getparam(g_hplayer, PARAM_VIDEO_HEIGHT, &vh);

EASY_PARAM_VIDEO_MODE
用于获取和设置视频显示方式，有两种方式可选：
    1. EASY_VIDEO_MODE_LETTERBOX - 按比例缩放到显示区域
    2. EASY_VIDEO_MODE_STRETCHED - 拉伸到显示区域
（注：视频显示区域由 EasyPlayerPro_Resize 进行设定）
int mode = 0;
EasyPlayerPro_Getparam(g_hplayer, EASY_PARAM_VIDEO_MODE, &mode);
mode = VIDEO_MODE_STRETCHED;
EasyPlayerPro_Setparam(g_hplayer, EASY_PARAM_VIDEO_MODE, &mode);

EASY_PARAM_AUDIO_VOLUME
用于设置播放音量，不同于系统音量，player 内部具有一个 -30dB 到 +12dB 的软件音量控制单元
音量范围：[-182, 73]，-182 对应 -30dB，73 对应 +12dB
特殊值  ：0 对应 0dB 增益，-255 对应静音，+255 对应最大增益
int volume = -0;
EasyPlayerPro_Setparam(g_hplayer, EASY_PARAM_AUDIO_VOLUME, &volume);

EASY_PARAM_PLAY_SPEED
用于设置播放速度，player 支持变速播放
int speed = 150;
EasyPlayerPro_Setparam(g_hplayer, EASY_PARAM_PLAY_SPEED, &speed);
参数 speed 为百分比速度，150 表示以 150% 进行播放
速度没有上限和下限，设置为 0 没有意义，内部会处理为 1%
播放速度的实际上限，由处理器的处理能力决定，超过处理器能力，播放会出现卡顿现象

EASY_PARAM_DECODE_THREAD_COUNT
用于设置视频解码线程数，可榨干 cpu 资源
int count = 6;
EasyPlayerPro_Setparam(g_hplayer, EASY_PARAM_DECODE_THREAD_COUNT, &count);
设置为 0 为将自动获取设备的 CPU 核心个数来计算和设置解码线程个数
设置为 1 为单线解码，设置为 >= 2 的值为多线程解码
并不是设置后一定就能运用上多线程解码，还要看对应的 decoder 是否支持多线程解码
一般情况下设置为 4 - 10 左右的值就能充分榨取 cpu 资源，保证播放的流畅性了

EASY_PARAM_VISUAL_EFFECT
用于指定视觉效果的类型，player 支持视觉效果，主要是对音频进行视觉效果的呈现
int mode = 0;
EasyPlayerPro_Getparam(g_hplayer, EASY_PARAM_VISUAL_EFFECT, &mode);
mode = EASY_AUDIO_VISUAL_EFFECT_WAVEFORM;
EasyPlayerPro_Setparam(g_hplayer, EASY_PARAM_VISUAL_EFFECT, &mode);
目前总共有三种视觉效果：
    1. VISUAL_EFFECT_DISABLE  - 关闭
    2. VISUAL_EFFECT_WAVEFORM - 波形
    3. VISUAL_EFFECT_SPECTRUM - 频谱
（注：视觉效果区域由 EasyPlayerPro_Resize 进行设定）

EASY_PARAM_AVSYNC_TIME_DIFF
用于设置 audio 和 video 的时间同步差值（毫秒为单位）
int diff = 100;
EasyPlayerPro_Setparam(g_hplayer, EASY_PARAM_AVSYNC_TIME_DIFF, &diff);
Eg: 设置为 100 后，音频将比视频快 100ms，设置为 -100 则慢 100ms

EASY_PARAM_PLAYER_CALLBACK
用于设置播放器事件回调函数，回调函数的原型定义如下：
typedef void (*EASY_PLAYERPRO_CALLBACK)(__int32 msg, __int64 param);
回调时的参数定义如下：
    msg   - PLAY_PROGRESS 播放进行中，PLAY_COMPLETED 播放完成
    param - 当前播放进度，以毫秒为单位

EASY_PARAM_VDEV_RENDER_TYPE
用于设置视频渲染方式，目前有 EASY_VIDEO_RENDER_TYPE_GDI 和 EASY_VIDEO_RENDER_TYPE_D3D 两种可选
int mode = 0;
EasyPlayerPro_Getparam(g_hplayer, PARAM_VDEV_RENDER_TYPE, &mode);
mode = EASY_VIDEO_RENDER_TYPE_D3D;
EasyPlayerPro_Setparam(g_hplayer, PARAM_VDEV_RENDER_TYPE, &mode);

EASY_PARAM_AUDIO_STREAM_TOTAL
EASY_PARAM_VIDEO_STREAM_TOTAL
EASY_PARAM_SUBTITLE_STREAM_TOTAL
以上三个是只读的(Get)，分别用于获取 audio, video, subtitle 的流总数
int streamCount = 0;
EasyPlayerPro_Getparam(g_hplayer, EASY_PARAM_AUDIO_STREAM_TOTAL, &streamCount);

EASY_PARAM_AUDIO_STREAM_CUR
EASY_PARAM_VIDEO_STREAM_CUR
EASY_PARAM_SUBTITLE_STREAM_CUR
以上三个参数，分别用于获取（Get）或设置（Set）当前播放的 audio, video, subtitle 流编号

EASY_PARAM_RECORD_TIME
EASY_PARAM_RECORD_PIECE_ID
以上两个参数是只读的(Get)，分别用于获取录像的时间和当前切片的ID
float recordTime = 0;
EasyPlayerPro_Getparam(g_hplayer, EASY_PARAM_RECORD_TIME, &recordTime);
int recordPieceId = 0;
EasyPlayerPro_Getparam(g_hplayer, EASY_PARAM_RECORD_PIECE_ID, &recordPieceId);


所有的参数，都是可以 get 的，但并不是所有的参数都可以 set，因为有些参数是只读的。

*/
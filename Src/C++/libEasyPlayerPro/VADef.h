#ifndef __VADEF_H__
#define __VADEF_H__

#include <stdlib.h>
#include <string.h>



//智能分析检测
#ifdef _DEBUG
#define		MAX_DETECT_POINT_NUM			100		//
#define		MAX_DETECT_ZONE_NUM				100
#define		MAX_DETECT_LINE_NUM				16
#define		MAX_DETECT_DIRECT_ZONE_NUM		4
#else
#define		MAX_DETECT_POINT_NUM			100		//
#define		MAX_DETECT_ZONE_NUM				100
#define		MAX_DETECT_LINE_NUM				16
#define		MAX_DETECT_DIRECT_ZONE_NUM		4
#endif



//渲染模式
typedef enum __RENDER_MODE_ENUM
{
	RENDER_MODE_VIDEO			=	0x00,						//渲染视频
	RENDER_MODE_ZONE			=	0x00000001,					//检测区
	RENDER_MODE_LINE			=	0x00000002,					//检测线
	RENDER_MODE_DIRECT_ZONE		=	0x00000004,					//方向检测区
	RENDER_MODE_LANE			=	0x00000008					//车道

}RENDER_MODE_ENUM;

//警戒类型
typedef enum __VA_WARN_TYPE_ENUM
{
	VA_WARN_TYPE_OFF		=	0x00,
	VA_WARN_TYPE_ON			=	0x01
}VA_WARN_TYPE_ENUM;

//警戒等级
typedef enum __VA_WARN_GRADE_ENUM
{
	VA_WARN_GRADE_HIGH	=	0x01,
	VA_WARN_GRADE_MIDDLE,
	VA_WARN_GRADE_LOW
}VA_WARN_GRADE_ENUM;


typedef struct __VA_DETECT_POINT_T
{
	int			id;
	char		name[36];
	int			x;
	int			y;
	float		xPercent;
	float		yPercent;
}VA_DETECT_POINT_T;

//检测区
typedef struct __VA_DETECT_ZONE_T
{
	int			id;
	char		name[36];
	VA_WARN_TYPE_ENUM	warnType;			//警戒类型
	VA_WARN_GRADE_ENUM	warnGrade;			//警戒等级

	unsigned char	show;					//是否显示
	unsigned char	hasArrow;				//是否有箭头
	unsigned char	fill;					//是否需要填充颜色
	unsigned char	selected;				//是否被选中
	unsigned char	complete;				//区域绘制完成
	unsigned char	movePoint;				//移动顶点
	unsigned char	moveArrow;				//移动箭头方向
	unsigned char	moveZone;				//移动区域
	COLORREF		borderColor;
	COLORREF		textColor;
	COLORREF		color;
	int			alpha_normal;				//正常透明度
	int			alpha_selected;				//被选中时透明度

	int			min_point_num;				//最小顶点数
	int			max_point_num;				//被限制的最大顶点数, 不能大于MAX_DETECT_POINT_NUM
	int			point_num;
	VA_DETECT_POINT_T	point[MAX_DETECT_POINT_NUM];

	VA_DETECT_POINT_T	ptCenter;			//箭头中心点
	VA_DETECT_POINT_T	ptArrow;			//箭头位置
	VA_DETECT_POINT_T	ptMove;
}VA_DETECT_ZONE_T;


typedef enum __VA_DIRECTION_ENUM
{
	VA_DIRECTION_LEFT2RIGHT		=	0x00,		//从左到右
	VA_DIRECTION_RIGHT2LEFT,					//从右到左
	VA_DIRECTION_TWO_WAY						//双向
}VA_DIRECTION_ENUM;

//检测线
typedef struct __VA_DETECT_LINE_T
{
	int			id;
	char		name[36];
	int			selected;
	int			complete;				//
	VA_DIRECTION_ENUM	direction;			//警戒线方向，0为从左到右（包括水平线），1为从右到左，2为双向
	int			point_num;
	VA_DETECT_POINT_T	point[2];
}VA_DETECT_LINE_T;

//检测区列表
typedef struct __VA_DETECT_ZONE_LIST_T
{
	VA_DETECT_ZONE_T			zone;
	__VA_DETECT_ZONE_LIST_T	*next;
}VA_DETECT_ZONE_LIST_T;

//检测线列表
typedef struct __VA_DETECT_LINE_LIST_T
{
	VA_DETECT_LINE_T			line;
	__VA_DETECT_LINE_LIST_T	*next;
}VA_DETECT_LINE_LIST_T;


#endif

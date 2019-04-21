EasyPlayerPro 配置说明

主界面
![EasyPlayerPro Windows播放器](http://www.easydarwin.org/github/images/easyplayerpro/easyplayerpro_win.png)

配置文件： 
EasyPlayerPro.xml


- SplitWindow:  分割窗口:   4, 8, 9, 16
- Scale:        1：按比例显示   0:铺满窗口
- Multiple:		复用源	1:复用  0:不复用
- FullScreen:	全屏显示	1:全屏  0:非全屏
- RecordingFileSize:  录像文件大小
当该值大于0时,则使用该参数作为录像标准,即后面的录像时长无效;
- RecordingDuration: 录像文件时长(秒)
当前面的录像文件大小为0时，该参数有效;
- AutoSegmentation: 自动分割录像文件	当录像文件达到指定大小或时长时，是否自动切换文件;
				1: 自动切换   0:不切换

- Channel
	URL:		源地址
 1.rtsp://admin:admin@192.168.1.100
 2.rtmp://
 3.http://
 4.file://D:\1.mp4
- OSD:		显示统计信息
- Protocol:	1(TCP)   0(UDP)
- Cache:	缓存帧(1-10)
	ShowToolbar:	显示工具栏
	AutoPlay:	自动播放( 当 URL 不为空时有效)
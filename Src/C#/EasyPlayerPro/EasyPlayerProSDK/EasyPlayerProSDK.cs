using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace EasyPlayerProSDK
{
    public class PlayerSDK
    {
        /// <summary>
        /// 流回调
        /// </summary>
        /// <param name="callbackType">回调数据类型.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="userPtr">用户自定义指针.</param>
        /// <param name="mediaType">媒体类型.</param>
        /// <param name="pBuf">数据指针.</param>
        /// <param name="_frameInfo">帧数据结构体.</param>
        /// <returns>System.Int32.</returns>
        public delegate int EasyPlayerProCallBack(EASY_CALLBACK_TYPE_ENUM callbackType, int channelId, IntPtr userPtr, MEDIA_TYPE mediaType, IntPtr pBuf, ref EASY_FRAME_INFO _frameInfo);

        /// <summary>
        /// 创建一个PLAYER_HANDLE句柄, 在后面的所有调用中, 填上创建的句柄, 结束调用libEasyPlayerPro_Release.
        /// </summary>
        /// <param name="playerHandle">PLAYER_HANDLE句柄.</param>
        /// <param name="supportMaxChannel">按需指定最大通道数, 最大不能超过宏定义MAX_CHANNEL_NUM.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_Create@8")]
        public static extern int LibEasyPlayerPro_Create(ref IntPtr playerHandle, int supportMaxChannel);

        /// <summary>
        /// 反初始化 PlayerSDK 内部参数
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_Release@4")]
        public static extern int LibEasyPlayerPro_Release(ref IntPtr playerHandle);

        /// <summary>
        /// 使用libEasyPlayerPro_Activate 激活SDK,  只需在初始时调用一次
        /// </summary>
        /// <param name="license">激活码 可在pvale.com中获取测试激活码, 或者邮件联系support@easydarwin.org</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_Activate@4")]
        public static extern int LibEasyPlayerPro_Activate(string license);

        /// <summary>
        /// 使用libEasyPlayerPro_Initialize初始化,  在后面的所有调用中, PLAYER_HANDLE为NULL, 结束调用libEasyPlayerPro_Deinitialize
        /// </summary>
        /// <param name="supportMaxChannel">按需指定最大通道数, 最大不能超过宏定义MAX_CHANNEL_NUM</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_Initialize@4")]
        public static extern int LibEasyPlayerPro_Initialize(int supportMaxChannel);

        /// <summary>
        /// 反初始化 PlayerSDK 内部参数
        /// </summary>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_Deinitialize@0")]
        public static extern int LibEasyPlayerPro_Deinitialize();

        /// <summary>
        /// 打开一路码流,返回一个可用的通道 ID
        /// </summary>
        /// <param name="playerHandle">PLAYER_HANDLE句柄.</param>
        /// <param name="channelType">通道源类型.</param>
        /// <param name="streamURI">有效的源地址.</param>
        /// <param name="mediaType">媒体类型【媒体类型 MEDIA_TYPE_VIDEO | MEDIA_TYPE_AUDIO | MEDIA_TYPE_EVENT)】 暂保留.</param>
        /// <param name="callback">回调函数.</param>
        /// <param name="userPtr">用户自定义指针.</param>
        /// <param name="reconnection">是否重连【1表示无限次重连,0表示不重连,大于1表示指定次数重连(需小于1000)】默认1.</param>
        /// <param name="queueSize">缓冲队列大小, 需大于1024*512.默认1024 * 512 * 2</param>
        /// <param name="rtpOverTcp">true 为tcp,否则为udp.默认1</param>
        /// <param name="multiplex">true:复用源,即打开同一个url时，到前端的连接只有一个;false:不复用, 打开多少个url,就有多少个连接*默认true
        /// <returns>可用的通道 ID.</returns>
        public static int LibEasyPlayerPro_OpenStream(IntPtr playerHandle, EASY_CHANNEL_SOURCE_TYPE_ENUM channelType, string streamURI, MEDIA_TYPE mediaType,
                                            EasyPlayerProCallBack callback, IntPtr userPtr, uint reconnection = 1, uint queueSize = 1024 * 512 * 2, bool overTcp = true, bool multiplex = true)
        {
            int ret = LibEasyPlayerPro_OpenStream(playerHandle, channelType, streamURI, overTcp ? (byte)1 : (byte)0, mediaType, callback, userPtr, reconnection, 0, queueSize, multiplex ? (uint)1 : (uint)0);
            return ret;
        }


        /// <summary>
        /// 打开一路码流,返回一个可用的通道 ID
        /// </summary>
        /// <param name="playerHandle">PLAYER_HANDLE句柄.</param>
        /// <param name="channelType">通道源类型.</param>
        /// <param name="streamURI">有效的源地址.</param>
        /// <param name="rtpOverTcp">仅针对rtsp有效, 1为tcp,否则为udp.</param>
        /// <param name="mediaType">媒体类型【媒体类型 MEDIA_TYPE_VIDEO | MEDIA_TYPE_AUDIO | MEDIA_TYPE_EVENT)】 暂保留.</param>
        /// <param name="callback">回调函数.</param>
        /// <param name="userPtr">用户自定义指针.</param>
        /// <param name="reconnection">是否重连【1表示无限次重连,0表示不重连,大于1表示指定次数重连(需小于1000)】.</param>
        /// <param name="heartbeatType">心跳类型: 填0.</param>
        /// <param name="queueSize">缓冲队列大小, 需大于1024*512.</param>
        /// <param name="multiplex">0x01:复用源,即打开同一个url时，到前端的连接只有一个;0x00:不复用, 打开多少个url,就有多少个连接*
        /// <returns>可用的通道 ID.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_OpenStream@44")]
        private static extern int LibEasyPlayerPro_OpenStream(IntPtr playerHandle, EASY_CHANNEL_SOURCE_TYPE_ENUM channelType, string streamURI, byte rtpOverTcp, MEDIA_TYPE mediaType,
                                            EasyPlayerProCallBack callback, IntPtr userPtr, uint reconnection, uint heartbeatType, uint queueSize, uint multiplex);

        /// <summary>
        /// 关闭流
        /// </summary>
        /// <param name="playerHandle">PLAYER_HANDLE句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_CloseStream@8")]
        public static extern int LibEasyPlayerPro_CloseStream(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 开始播放
        /// 对同一个流,最大播放个数不能大于5个, 如果只调用 libEasyPlayerPro_OpenStream 而不调用 libEasyPlayerPro_StartPlayStream 则无此限制
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="hWnd">窗口句柄.</param>
        /// <param name="renderFormat">显示格式.</param>
        /// <param name="decodeType">解码类型-暂无效【0:软解 1:硬解】.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_StartPlayStream@20")]
        public static extern int LibEasyPlayerPro_StartPlayStream(IntPtr playHandle, int channelID, IntPtr hWnd, RENDER_FORMAT renderFormat, byte decodeType = 0);

        /// <summary>
        /// 停止播放
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_StopPlayStream@8")]
        public static extern int LibEasyPlayerPro_StopPlayStream(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 设置是否显示统计信息,包括编码格式、分辨率、码率、当前缓存帧数等
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="showInfo">是否显示OSD</param>
        /// <returns></returns>
        public static int LibEasyPlayerPro_ShowStatisticalInfo(IntPtr playerHandle, int channelId, bool showInfo = false)
        {
            int ret = LibEasyPlayerPro_ShowStatisticalInfo(playerHandle, channelId, showInfo ? (byte)1 : (byte)0);
            return ret;
        }

        /// <summary>
        /// 设置是否显示统计信息,包括编码格式、分辨率、码率、当前缓存帧数等
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="showInfo">1:显示，0:不显示</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_ShowStatisticalInfo@12")]
        private static extern int LibEasyPlayerPro_ShowStatisticalInfo(IntPtr playerHandle, int channelId, byte showInfo);

        /// <summary>
        /// 设置播放缓冲帧数
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="cache">缓存大小  1 - 10【越小实时性越好，越大越流畅】</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetPlayFrameCache@12")]
        public static extern int LibEasyPlayerPro_SetPlayFrameCache(IntPtr playerHandle, int channelId, int cache);

        /// <summary>
        /// 获取指定通道的播放缓冲帧数
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns>缓冲帧数</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_GetPlayFrameCache@8")]
        public static extern int LibEasyPlayerPro_GetPlayFrameCache(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 获取指定通道的媒体信息
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="pMediaInfo">返回的媒体信息</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_GetStreamInfo@12")]
        public static extern int LibEasyPlayerPro_GetStreamInfo(IntPtr playerHandle, int channelId, ref EASY_MEDIA_INFO_T pMediaInfo);

        /// <summary>
        /// 清空帧队列, 从下一个收到的关键帧开始播放
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_ResetFrameQueue@8")]
        public static extern int LibEasyPlayerPro_ResetFrameQueue(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 设置是否仅解码显示关键帧
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="decodeKeyframeOnly"></param>
        /// <returns></returns>
        public static int LibEasyPlayerPro_SetDecodeType(IntPtr playerHandle, int channelId, bool decodeKeyframeOnly)
        {
            int ret = LibEasyPlayerPro_SetDecodeType(playerHandle, channelId, decodeKeyframeOnly ? (byte)1 : (byte)0);
            return ret;
        }

        /// <summary>
        /// 设置是否仅解码显示关键帧
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="decodeKeyframeOnly">1:是，0:否</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetDecodeType@12")]
        public static extern int LibEasyPlayerPro_SetDecodeType(IntPtr playerHandle, int channelId, byte decodeKeyframeOnly);

        /// <summary>
        /// 视频翻转(仅在显示格式为 RGB24 时有效)
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="flip">是都翻转，默认不翻转</param>
        /// <returns></returns>
        public static int LibEasyPlayerPro_SetVideoFlip(IntPtr playerHandle, int channelId, bool flip = false)
        {
            return LibEasyPlayerPro_SetVideoFlip(playerHandle, channelId, flip ? (byte)1 : (byte)0);
        }

        /// <summary>
        /// 视频翻转(仅在显示格式为 RGB24 时有效)
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="flip">1:是，0:否</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetVideoFlip@12")]
        public static extern int LibEasyPlayerPro_SetVideoFlip(IntPtr playerHandle, int channelId, byte flip);

        /// <summary>
        /// 设置叠加文字
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="text">叠加文字</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetOverlayText@12")]
        public static extern int LibEasyPlayerPro_SetOverlayText(IntPtr playerHandle, int channelId, string text);

        /// <summary>
        /// 清空叠加文字
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_ClearOverlayText@8")]
        public static extern int LibEasyPlayerPro_ClearOverlayText(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 设置当前视频从指定的坐标开始显示; 用于放大局部细节
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="lPrect">分辨率坐标点</param>
        /// <returns></returns>
        public static int LibEasyPlayerPro_SetRenderRect(IntPtr playerHandle, int channelId, Rect lPrect)
        {
            LPRECT rect = new LPRECT { left = (int)lPrect.X, top = (int)lPrect.Y, bottom = (int)lPrect.Height, right = (int)lPrect.Width };

            IntPtr ptr = Marshal.AllocHGlobal(Marshal.SizeOf(rect));
            Marshal.StructureToPtr(rect, ptr, true);
            int ret = LibEasyPlayerPro_SetRenderRect(playerHandle, channelId, ptr);
            Marshal.FreeHGlobal(ptr);
            return ret;
        }

        /// <summary>
        /// 设置当前视频从指定的坐标开始显示; 用于放大局部细节
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="lPrect">分辨率坐标点</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetRenderRect@12")]
        private static extern int LibEasyPlayerPro_SetRenderRect(IntPtr playerHandle, int channelId, IntPtr lPrect);

        /// <summary>
        /// 按比例显示视频或铺满窗口; 当按比例显示时, 参数bkColor有效;
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="scaleDisplay">是否按比例显示</param>
        /// <param name="bkColor">背景色</param>
        /// <returns></returns>
        public static int LibEasyPlayerPro_SetScaleDisplay(IntPtr playerHandle, int channelId, bool scaleDisplay, Color bkColor)
        {
            var bgColor = ColorTranslator.ToWin32(bkColor);
            int ret = LibEasyPlayerPro_SetScaleDisplay(playerHandle, channelId, scaleDisplay ? (byte)1 : (byte)0, bgColor);
            return ret;
        }

        /// <summary>
        /// 按比例显示视频或铺满窗口; 当按比例显示时, 参数bkColor有效;
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="scaleDisplay">0x00:铺满窗口 0x01:按比例显示</param>
        /// <param name="bkColor">背景色</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetScaleDisplay@16")]
        private static extern int LibEasyPlayerPro_SetScaleDisplay(IntPtr playerHandle, int channelId, byte scaleDisplay, int bkColor);

        /// <summary>
        /// 设置速度值,仅针对文件有效, 正常，暂停，1x,2x,4x,8x,1/2,1/4,1/8
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="speed">播放速度</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetPlaySpeed@12")]
        public static extern int LibEasyPlayerPro_SetPlaySpeed(IntPtr playerHandle, int channelId, PLAY_SPEED_ENUM speed);

        /// <summary>
        /// 获取速度值.
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_GetPlaySpeed@8")]
        public static extern int LibEasyPlayerPro_GetPlaySpeed(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 开始手动录像  如果指定了录像文件大小,则录像时长无效，如filesize为0, 则duration有效
        /// 如果preRecording设置为1, 则相应的文件大小或文件时长均会增加预录的大小或时长, 例: 指定filesize为100MB,同时preRecording设置为1, 则实际录像文件大小为100MB+预录大小
        /// 预录大小和时长，库内部指定为10秒,但相应内存均由libEasyPlayerPro_OpenStream中的queueSize指定, 即:内存给的足够大，最大预录时长为10秒, 内存给的小,预录时长则不足10秒
        /// 注:   当开启即时回放时，不允许手动录像, 即会返回-3
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="folderPath">folderPath</param>
        /// <param name="fileName">fileName</param>
        /// <param name="filesize">录像文件大小 MB</param>
        /// <param name="duration">录像时长(second)</param>
        /// <param name="preRecording">0x01:预录  0x00:不预录</param>
        /// <returns></returns>
        public static int LibEasyPlayerPro_StartRecording(IntPtr playerHandle, int channelId, uint filesize, int duration, bool preRecording = false, string folderPath = null, string fileName = null)
        {
            string path = folderPath ?? System.AppDomain.CurrentDomain.BaseDirectory + "record\\";

            if (!System.IO.Directory.Exists(path))
                System.IO.Directory.CreateDirectory(path);
            fileName = fileName ?? DateTime.Now.ToString("yyyyMMdd-HHmmss") + ".mpg";
            return LibEasyPlayerPro_StartRecording(playerHandle, channelId, path, fileName, filesize, duration, preRecording ? (byte)1 : (byte)0);
        }


        /// <summary>
        /// 开始手动录像  如果指定了录像文件大小,则录像时长无效，如filesize为0, 则duration有效
        /// 如果preRecording设置为1, 则相应的文件大小或文件时长均会增加预录的大小或时长, 例: 指定filesize为100MB,同时preRecording设置为1, 则实际录像文件大小为100MB+预录大小
        /// 预录大小和时长，库内部指定为10秒,但相应内存均由libEasyPlayerPro_OpenStream中的queueSize指定, 即:内存给的足够大，最大预录时长为10秒, 内存给的小,预录时长则不足10秒
        /// 注:   当开启即时回放时，不允许手动录像, 即会返回-3
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="folderPath">folderPath</param>
        /// <param name="fileName">fileName</param>
        /// <param name="filesize">录像文件大小 MB</param>
        /// <param name="duration">录像时长(second)</param>
        /// <param name="preRecording">0x01:预录  0x00:不预录</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_StartRecording@28")]
        private static extern int LibEasyPlayerPro_StartRecording(IntPtr playerHandle, int channelId, string folderPath, string fileName, uint filesize, int duration, byte preRecording);

        /// <summary>
        /// 停止本地录像
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_StopRecording@8")]
        public static extern int LibEasyPlayerPro_StopRecording(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 抓图【只有在异步抓图模式下，才能使用队列,队列内存为31104000bytes(大约为32MB)】
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="imageFormat">0:bmp 1:jpg</param>
        /// <param name="filename">filename</param>
        /// <param name="sync">0:异步: 1:同步</param>
        /// <param name="useQueue">1:使用队列 0:不使用队列</param>
        /// <returns></returns>
        public static int LibEasyPlayerPro_SnapshotToFile(IntPtr playerHandle, int channelId, ImageFormat imageFormat, string filename = null, bool sync = false, bool useQueue = false)
        {
            filename = filename ?? DateTime.Now.ToString("yyyyMMdd-HHmmss");
            int ret = LibEasyPlayerPro_SnapshotToFile(playerHandle, channelId, (byte)imageFormat, filename, sync ? (byte)1 : (byte)0, useQueue ? (byte)1 : (byte)0);
            return ret;
        }


        /// <summary>
        /// 抓图【只有在异步抓图模式下，才能使用队列,队列内存为31104000bytes(大约为32MB)】
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <param name="imageFormat">0:bmp 1:jpg</param>
        /// <param name="filename">filename</param>
        /// <param name="sync">0:异步: 1:同步</param>
        /// <param name="useQueue">1:使用队列 0:不使用队列</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SnapshotToFile@24")]
        private static extern int LibEasyPlayerPro_SnapshotToFile(IntPtr playerHandle, int channelId, byte imageFormat, string filename, byte sync, byte useQueue);

        /// <summary>
        /// 播放声音.
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_StartPlaySound@8")]
        public static extern int LibEasyPlayerPro_StartPlaySound(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 停止播放声音.
        /// </summary>
        /// <param name="playerHandle">播放句柄.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "_libEasyPlayerPro_StopPlaySound@8")]
        public static extern int LibEasyPlayerPro_StopPlaySound(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 获取声音播放状态: 是否在播放中
        /// </summary>
        /// <param name="playHandle">播放句柄.</param>
        /// <param name="channelId">通道ID.</param>
        /// <returns>0:播放中, !0:非播放中.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SoundPlaying@8")]
        public static extern int LibEasyPlayerPro_SoundPlaying(IntPtr playerHandle, int channelId);

        /// <summary>
        /// 获取音频设备列表.
        /// </summary>
        /// <param name="handle">播放句柄.</param>
        /// <param name="devicelist">设备列表.</param>
        /// <param name="deviceNum">设备个数.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_GetAudioOutputDeviceList@12")]
        public static extern int LibEasyPlayerPro_GetAudioOutputDeviceList(IntPtr handle, ref MIXER_DEVICE_INFO_T devicelist, ref int deviceNum);

        /// <summary>
        /// 设置当前音频设备ID.
        /// </summary>
        /// <param name="handle">The handle.</param>
        /// <param name="deviceId">设备ID.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetAudioOutputDeviceId@8")]
        public static extern int LibEasyPlayerPro_SetAudioOutputDeviceId(IntPtr handle, int deviceId);

        /// <summary>
        /// 设置当前音频设备Name.
        /// </summary>
        /// <param name="handle">The handle.</param>
        /// <param name="deviceName">设备名称.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetAudioOutputDeviceName@8")]
        public static extern int LibEasyPlayerPro_SetAudioOutputDeviceName(IntPtr handle, string deviceName);

        /// <summary>
        /// 设置音量
        /// </summary>
        /// <param name="handle">The handle.</param>
        /// <param name="volume">音量 ( 0 ~ 100 ).</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetAudioVolume@8")]
        public static extern int LibEasyPlayerPro_SetAudioVolume(IntPtr handle, int volume);

        /// <summary>
        /// 获取音量.
        /// </summary>
        /// <param name="handle">The handle.</param>
        /// <returns>System.Int32.</returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_GetAudioVolume@4")]
        public static extern int LibEasyPlayerPro_GetAudioVolume(IntPtr handle);

        /// <summary>
        /// 设置放大起始点
        /// </summary>
        /// <param name="handle"></param>
        /// <param name="channelId"></param>
        /// <param name="fXPercent">为鼠标单击的点相对于窗口的百分比</param>
        /// <param name="fYPercent">为鼠标单击的点相对于窗口的百分比</param>
        /// <param name="showBox">是否显示所画的框</param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetElectronicZoomStartPoint@20")]
        public static extern int libEasyPlayerPro_SetElectronicZoomStartPoint(IntPtr handle, int channelId, float fXPercent, float fYPercent, bool showBox);

        /// <summary>
        /// 设置放大结束点
        /// </summary>
        /// <param name="handle"></param>
        /// <param name="channelId"></param>
        /// <param name="fXPercent"></param>
        /// <param name="fYPercent"></param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetElectronicZoomEndPoint@16")]
        public static extern int libEasyPlayerPro_SetElectronicZoomEndPoint(IntPtr handle, int channelId, float fXPercent, float fYPercent);

        /// <summary>
        /// 设置是否放大
        /// </summary>
        /// <param name="handle"></param>
        /// <param name="channelId"></param>
        /// <param name="zoomIn"></param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_SetElectronicZoom@12")]
        public static extern int libEasyPlayerPro_SetElectronicZoom(IntPtr handle, int channelId, int zoomIn/*1:放大  0:不放大*/);

        /// <summary>
        /// 电子放大重置
        /// </summary>
        /// <param name="handle"></param>
        /// <param name="channelId"></param>
        /// <returns></returns>
        [DllImport(@"Lib\libEasyPlayerPro.dll", CallingConvention = CallingConvention.StdCall, EntryPoint = "_libEasyPlayerPro_ResetElectronicZoom@8")]
        public static extern int libEasyPlayerPro_ResetElectronicZoom(IntPtr handle, int channelId);

    }

    /// <summary>
    /// 截图格式
    /// </summary>
    public enum ImageFormat : byte
    {
        bmp = 0,
        jpg = 1
    }

    public enum RENDER_FORMAT : uint
    {
        RENDER_FORMAT_YV12 = 842094169,
        RENDER_FORMAT_YUY2 = 844715353,
        RENDER_FORMAT_UYVY = 1498831189,
        RENDER_FORMAT_A8R8G8B8 = 21,
        RENDER_FORMAT_X8R8G8B8 = 22,
        RENDER_FORMAT_RGB565 = 23,
        RENDER_FORMAT_RGB555 = 25,

        RENDER_FORMAT_RGB24_GDI = 26
    }

    /// <summary>
    /// //通道源类型 (指定源类型)
    /// </summary>
    public enum EASY_CHANNEL_SOURCE_TYPE_ENUM
    {
        EASY_CHANNEL_SOURCE_TYPE_RTSP = 0,          //源为RTSP(内置)
        EASY_CHANNEL_SOURCE_TYPE_RTMP,              //源为RTMP(内置)
        EASY_CHANNEL_SOURCE_TYPE_HLS,               //源为HLS(内置)
        EASY_CHANNEL_SOURCE_TYPE_FILE,              //源为本地文件(内置)
        EASY_CHANNEL_SOURCE_TYPE_ENCODE_DATA,       //源为外部的编码数据
        EASY_CHANNEL_SOURCE_TYPE_DECODE_DATA,       //源为外部的解码数据
    }

    public enum EASY_CALLBACK_TYPE_ENUM
    {
        EASY_TYPE_CONNECTING = 100,         //当前通道连接中
        EASY_TYPE_CONNECTED,                            //当前通道已连接
        EASY_TYPE_RECONNECT,                            //当前通道连接已断开,正在重连
        EASY_TYPE_DISCONNECT,                           //当前通道连接已中止(内部连接线程已退出),指定了连接次数的情况下会回调该值

        EASY_TYPE_CODEC_DATA,                           //编码数据
        EASY_TYPE_DECODE_DATA,                          //解码数据
        EASY_TYPE_SNAPSHOT,                             //抓拍
        EASY_TYPE_RECORDING,                            //录像
        EASY_TYPE_INSTANT_REPLAY_RECORDING,             //即时回放录像完成

        EASY_TYPE_START_PLAY_AUDIO,                     //开始播放声音
        EASY_TYPE_STOP_PLAY_AUDIO,                      //停止播放声音
        EASY_TYPE_CAPTURE_AUDIO_DATA,                   //本地采集的音频数据

    }

    /// <summary>
    /// 媒体类型
    /// </summary>
    [Flags]
    public enum MEDIA_TYPE
    {
        MEDIA_TYPE_VIDEO = 0x00000001,
        MEDIA_TYPE_AUDIO = 0x00000002,
        MEDIA_TYPE_EVENT = 0x00000004,
        MEDIA_TYPE_RTP = 0x00000008,
        MEDIA_TYPE_SDP = 0x00000010,
        MEDIA_TYPE_CODEC_INFO = 0x00000020
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct EASY_FRAME_INFO
    {
        public uint codec;                  /* 音视频格式 */

        public uint type;                   /* 视频帧类型 */
        public byte fps;                    /* 视频帧率 */
        public ushort width;               /* 视频宽 */
        public ushort height;              /* 视频高 */

        public uint reserved1;         /* 保留参数1 */
        public uint reserved2;         /* 保留参数2 */

        public uint sample_rate;       /* 音频采样率 */
        public uint channels;          /* 音频声道数 */
        public uint bits_per_sample;        /* 音频采样精度 */

        public uint length;                /* 音视频帧大小 */
        public uint timestamp_usec;        /* 时间戳,微妙 */
        public uint timestamp_sec;          /* 时间戳 秒 */

        public float bitrate;                       /* 比特率 */
        public float losspacket;                    /* 丢包率 */
    }

    /// <summary>
    /// 媒体信息
    /// </summary>
    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct EASY_MEDIA_INFO_T
    {
        public uint videoCodec;            //视频编码类型
        public uint videoFps;              //视频帧率
        public int videoWidth;
        public int videoHeight;
        public float videoBitrate;

        public uint audioCodec;            //音频编码类型
        public uint audioSampleRate;       //音频采样率
        public uint audioChannel;          //音频通道数
        public uint audioBitsPerSample;    //音频采样精度

        public uint metadataCodec;         //Metadata类型

        public uint vpsLength;             //视频vps帧长度
        public uint spsLength;             //视频sps帧长度
        public uint ppsLength;             //视频pps帧长度
        public uint seiLength;             //视频sei帧长度

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 255)]
        public byte[] vps;                 //视频vps帧内容

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 255)]
        public byte[] sps;         //视频sps帧内容
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] pps;         //视频sps帧内容
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] sei;         //视频sei帧内容
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct LPRECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    }

    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct MIXER_DEVICE_INFO_T
    {
        public int id;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string name;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        public string versior;
    }

    // 播放速度
    public enum PLAY_SPEED_ENUM
    {
        PLAY_SPEED_UNKNOWN = -1,
        PLAY_SPEED_NORMAL = 0x00,       // 正常播放
        PLAY_SPEED_PAUSED,                  // 暂停
        PLAY_SPEED_SLOW_X2,                 // 1/2
        PLAY_SPEED_SLOW_X4,                 // 1/4
        PLAY_SPEED_SLOW_X8,                 // 1/8
        PLAY_SPEED_FAST_X2,                 // x2
        PLAY_SPEED_FAST_X4,                 // x4
        PLAY_SPEED_FAST_X8,                 // x8
        PLAY_SPEED_REWIND_X2,               // -2x
        PLAY_SPEED_REWIND_X4,               // -4x
        PLAY_SPEED_REWIND_X8,               // -8x	

        PLAY_SPEED_SINGLE_FRAME,            //单帧播放,手动单击
    }
}

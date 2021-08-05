using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
//using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
//using System.Threading.Tasks;
using System.Windows.Forms;

namespace PlayerSDK
{
    public partial class EasyPlayerPro : Form
    {
        // adev render type
        public enum EASY_AUDIO_RENDER_TYPE
        {
            //waveout
            EASY_AUDIO_RENDER_TYPE_WAVEOUT = 0,
        };

        // vdev render type
        public enum EASY_VIDEO_RENDER_TYPE
        {
            EASY_VIDEO_RENDER_TYPE_GDI = 0,
            EASY_VIDEO_RENDER_TYPE_D3D,
            //	EASY_VIDEO_RENDER_TYPE_OPENGL,
            EASY_VIDEO_RENDER_TYPE_MAX_NUM,
        };

        // render mode
        public enum EASY_VIDEO_SCALE_MODE
        {
            //拉伸充满显示区域
            EASY_VIDEO_MODE_STRETCHED,
            //按比例缩放到显示区域
            EASY_VIDEO_MODE_LETTERBOX,
            EASY_VIDEO_MODE_MAX_NUM,
        };

        // link mode
        public enum EASY_STREAM_LINK_MODE
        {
            //按比例缩放到显示区域
            EASY_STREAM_LINK_UDP = 0,
            //拉伸充满显示区域
            EASY_STREAM_LINK_TCP,
            EASY_STREAM_LINK_MODE_NUM,
        };

        // audio visual effect
        public enum EASY_AUDIO_VISUAL_EFFECT_MODE
        {
            EASY_AUDIO_VISUAL_EFFECT_DISABLE,
            EASY_AUDIO_VISUAL_EFFECT_WAVEFORM,
            EASY_AUDIO_VISUAL_EFFECT_SPECTRUM,
            EASY_AUDIO_VISUAL_EFFECT_MAX_NUM,
        };

        // hwaccel type 视频渲染硬件加速类型
        public enum EASY_VIDEO_HARDWARE_ACCEL_TYPE
        {
            EASY_VIDEO_HWACCEL_TYPE_NONE,
            EASY_VIDEO_HWACCEL_TYPE_DXVA2,
            EASY_VIDEO_HWACCEL_TYPE_MAX_NUM,
        };

        public enum EASY_PARAM_ID
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
            // player event/audio/video callback userdata
            EASY_PARAM_PLAYER_USERDATA,

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

            //++ for adev
            EASY_PARAM_ADEV_RENDER_TYPE = 0x2000,
            EASY_PARAM_ADEV_GET_CONTEXT,
            EASY_PARAM_ADEV_SET_MUTE,
            //-- for adev

            //++ for vdev
            EASY_PARAM_VDEV_RENDER_TYPE = 0x3000,
            EASY_PARAM_VDEV_FRAME_RATE,
            EASY_PARAM_VDEV_GET_CONTEXT,
            EASY_PARAM_VDEV_POST_SURFACE,
            EASY_PARAM_VDEV_GET_D3DDEV,
            EASY_PARAM_VDEV_D3D_ROTATE,
            //-- for vdev

            //++ for render
            EASY_PARAM_RENDER_UPDATE = 0x4000,
            EASY_PARAM_RENDER_START_PTS,
            //-- for render
        };

        // EasyPlayerPro接口函数声明
        //
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Authorize", CallingConvention = CallingConvention.Cdecl)]
        static extern int EasyPlayerPro_Authorize(string license);

        //初始化创建播放器实例(该接口可多次调用创建多个实例)
        // 		返回值				- Easy_PlayerPro_Handle 指针类型，指向 easyplayerpro 对象句柄
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Create", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr EasyPlayerPro_Create();

        //销毁播放器实例
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Release", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Release(IntPtr player);

        //打开播放视频
        // 	EasyPlayerPro_Open     打开一个媒体流或者媒体文件进行播放，同时返回一个 player 对象指针
        // 		fileUrl				- 文件路径（可以是网络流媒体的 URL）
        // 		hWnd				- Win32 的窗口句柄/其他平台渲染显示设备句柄
        //		render_mode			- 视频渲染模式，详见EASY_VIDEO_RENDER_TYPE
        //		video_mode			- 视频显示模式，详见EASY_VIDEO_SCALE_MODE
        //		link_mode			- 流连接模式，目前只对RTSP流有效，设置rtp over tcp/udp,	详见EASY_STREAM_LINK_MODE
        //		speed				- 播放速度，0-100慢放，100以上快放
        //		valume				- 播放音量，-255 - +255
        // 		返回值				- Easy_PlayerPro_Handle 指针类型，指向 easyplayerpro 对象句柄
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Open", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr EasyPlayerPro_Open(IntPtr player, string file, IntPtr hwnd, EASY_VIDEO_RENDER_TYPE render_type, EASY_VIDEO_SCALE_MODE video_mode, EASY_STREAM_LINK_MODE link_mode, int speed, int valume, int probesize, int max_analyze_duration);

        //关闭视频
        // 	EasyPlayerPro_Close    关闭播放
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Close", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Close(IntPtr player);

        //播放视频
        // 	EasyPlayerPro_Play     开始播放，注意：媒体流或者文件打开后不需要调用此函数即开始播放，
        // 							此函数在暂停、单步播放的时候调用，返回正常播放逻辑
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Play", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Play(IntPtr player);

        //单帧播放视频
        // 	EasyPlayerPro_StepPlay 单步播放，一次播放一帧，调用EasyPlayerPro_Play返回正常播放
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        //		type				- 单步播放类型，1-往前 2-向后
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_StepPlay", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_StepPlay(IntPtr player, int type);

        //暂停视频
        // 	EasyPlayerPro_Pause		暂停播放，调用EasyPlayerPro_Play返回正常播放
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Pause", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Pause(IntPtr player);

        //挑转播放进度
        // 	EasyPlayerPro_Seek     跳转到指定位置播放
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        // 		seek				- 指定位置，以毫秒为单位
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Seek", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Seek(IntPtr player, System.Int64 ms);

        //设置窗口显示区域
        // 	EasyPlayerPro_Resize   设置显示区域，有两种显示区域，视频显示区和视觉效果显示区
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        // 		type				- 指定区域类型  0 - video rect, 1 - audio visual effect rect
        // 		x,y,width,height	- 指定显示矩形区域
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Resize", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Resize(IntPtr player, int type, int x, int y, int w, int h);

        //截图
        // 	EasyPlayerPro_Snapshot 视频播放截图
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        // 		filePath			- 图片存放路径，以.xxx结束（xxx 目前只支持 jpeg 格式）
        // 		width, height       - 指定图片宽高，如果 <= 0 则默认使用视频宽高
        // 		waittime			- 是否等待截图完成 0 - 不等待，>0 等待超时 ms 为单位
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Snapshot", CallingConvention = CallingConvention.Cdecl)]
        static extern int EasyPlayerPro_Snapshot(IntPtr player, string file, int w, int h, int wait);

        // 	EasyPlayerPro_Record   视频播放录像
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        // 		filePath			- 图片存放路径，以.xxx结束（xxx 目前只支持 mp4 格式）
        // 		duration			- 指定图片宽高，如果 <= 0 则默认使用视频宽高
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Record", CallingConvention = CallingConvention.Cdecl)]
        static extern int EasyPlayerPro_Record(IntPtr player, string filePath, int duration);

        // 	EasyPlayerPro_Stoprecord   视频播放停止录像
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Stoprecord", CallingConvention = CallingConvention.Cdecl)]
        static extern int EasyPlayerPro_Stoprecord(IntPtr player);


        //设置参数
        // 	EasyPlayerPro_Setparam 设置参数
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        // 		param_id			- 参数ID，见EASY_PARAM_ID定义
        // 		param				- 参数指针
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Setparam", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Setparam(IntPtr player, EASY_PARAM_ID id, ref IntPtr param);

        //获取参数
        // 	EasyPlayerPro_Setparam 获取参数
        // 		player				- 指向 EasyPlayerPro_Open 返回的 player 对象
        // 		param_id			- 参数ID，见EASY_PARAM_ID定义
        // 		param				- 参数指针
        [DllImport("libEasyplayerpro.dll", EntryPoint = "EasyPlayerPro_Getparam", CallingConvention = CallingConvention.Cdecl)]
        static extern void EasyPlayerPro_Getparam(IntPtr player, EASY_PARAM_ID id, ref Int64 param);

        private IntPtr mPlayer = IntPtr.Zero;
        private string ACTIVE_KEY = "EasyPlayer is Free!";

        int totalTime = 0;
        int alreadyTime = 0;
        bool bInit = false;
        bool bPlaying = false;

        public EasyPlayerPro()
        {
            InitializeComponent();


            //D:\我的文档\Tencent Files\2267892331\FileRecv\Test.mp4
            //http://192.168.1.100:8001/64B00FC82C984996B0907E55618E62AA_CBBEE301CDEC4927973EB80BCE2B5892/20170816110924/64B00FC82C984996B0907E55618E62AA_CBBEE301CDEC4927973EB80BCE2B5892.m3u8
            //mPlayer = player_open(@"http://192.168.1.100:8001/64B00FC82C984996B0907E55618E62AA_CBBEE301CDEC4927973EB80BCE2B5892/20170816110924/64B00FC82C984996B0907E55618E62AA_CBBEE301CDEC4927973EB80BCE2B5892.m3u8", skinPanel1.Handle);

            //button5.Text = "123456";
            //skinLabel1.Text = test;
            //skinLabel1.Text = "125";

            //int v = Convert.ToInt32( test);
            //skinHScrollBar1.Maximum = v;
        }

        private void PalyerForm_Load(object sender, EventArgs e)
        {
            this.skinComboBox1.SelectedItem = "100";

            int nRet = EasyPlayerPro_Authorize(ACTIVE_KEY);
            if (nRet <= 0)
            {
                 MessageBox.Show("激活码不合法或已过期！", "提示", MessageBoxButtons.OK);
           }
            string strTitle = "EasyPlayerPro    " + "授权剩余时间：" + nRet + " 天";
            this.Text = strTitle;
            mPlayer = EasyPlayerPro_Create();
            bInit = true;
            //RealProCallBack = new PlayerSDK.EasyPlayerProCallBack(RealProSourceCallBack);
        }

        private void PalyerForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (bPlaying)
                EasyPlayerPro_Close(mPlayer);
            if (bInit)
                EasyPlayerPro_Release(mPlayer);
            mPlayer = IntPtr.Zero;
            bInit = false;
        }

        private void PlayerForm_FormClosed(object sender, FormClosedEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            EasyPlayerPro_Play(mPlayer);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            EasyPlayerPro_Close(mPlayer);
            bPlaying = false;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            EasyPlayerPro_Pause(mPlayer);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            EasyPlayerPro_StepPlay(mPlayer,1);
        }
       

        private void button5_Click(object sender, EventArgs e)
        {
            if (!bPlaying)
            {
                // EASY_VIDEO_RENDER_TYPE render_type, EASY_VIDEO_SCALE_MODE video_mode, EASY_STREAM_LINK_MODE link_mode,int speed, int valume
                mPlayer = EasyPlayerPro_Open(mPlayer,this.textURL.Text, panel1.Handle, EASY_VIDEO_RENDER_TYPE.EASY_VIDEO_RENDER_TYPE_GDI,
                   EASY_VIDEO_SCALE_MODE.EASY_VIDEO_MODE_LETTERBOX, EASY_STREAM_LINK_MODE.EASY_STREAM_LINK_TCP, 
                   Convert.ToInt32(skinComboBox1.Text), 0,1024*1024, 1000000);
                timer1.Enabled = true;
                timer2.Enabled = true;
                bPlaying = true;
            }
            else
            {
                MessageBox.Show("先关闭视频！");
            }
            
        }

        private void textBox1_DoubleClick(object sender, EventArgs e)
        {
            IntPtr param = new IntPtr();
            //param = (IntPtr)EFFECT_TYPE.VISUAL_EFFECT_WAVEFORM;

            //player_getparam(mPlayer, (uint)SET_GET_TYPE.PARAM_MEDIA_DURATION , ref param);

            //player_getparam(mPlayer, (uint)SET_GET_TYPE.PARAM_MEDIA_POSITION, ref param);

            //player_getparam(mPlayer, (uint)SET_GET_TYPE.PARAM_VIDEO_WIDTH, ref param);

            //player_getparam(mPlayer, (uint)SET_GET_TYPE.PARAM_VIDEO_HEIGHT, ref param);

            //player_getparam(mPlayer, (uint)SET_GET_TYPE.PARAM_VIDEO_MODE, ref param);//(无效)

            //player_setparam(mPlayer, (uint)SET_GET_TYPE.PARAM_VIDEO_MODE,ref param);

            //player_setparam(mPlayer, (uint)SET_GET_TYPE.PARAM_AUDIO_VOLUME, ref param);//(没有实际测试)

            //player_setparam(mPlayer, (uint)SET_GET_TYPE.PARAM_PLAY_SPEED, ref param);//(没有音频不能快进)

            //player_setparam(mPlayer, (uint)SET_GET_TYPE.PARAM_DECODE_THREAD_COUNT, ref param);//(实际测试有问题)

            //player_getparam(mPlayer, (uint)SET_GET_TYPE.PARAM_VISUAL_EFFECT, ref param);//(无效)

            //player_setparam(mPlayer, (uint)SET_GET_TYPE.PARAM_VISUAL_EFFECT, ref param);//(没有实际测试)

            //player_seek(mPlayer,(long)10000);

            //player_setrect(mPlayer, 0, 0, 0, 100, 100);
        }  

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(mPlayer != IntPtr.Zero)
            {
                Int64 param = 0;
                if (totalTime <= 0)
                {
                    Int64 ltotal = 0;
                    EasyPlayerPro_Getparam(mPlayer, EASY_PARAM_ID.EASY_PARAM_MEDIA_DURATION, ref param);
                    ltotal = param;
                    if (ltotal > 1)
                    {
                        totalTime = (int)(Int64)ltotal / 1000;
                        //int totalSeconds = (int)totalTime;
                        //int gTotalSeconds = totalSeconds;
                        //int gTotalMinute = (int)(totalSeconds / 60);
                        //int nTotalHour = (int)(gTotalMinute / 60);  //时
                        //int nTotalMinute = (int)(gTotalMinute % 60);//分
                        //int totalSecond = (int)(totalSeconds % 60); //秒
                        skinTrackBar1.Maximum = (int)totalTime;
                    }
                }

                EasyPlayerPro_Getparam(mPlayer, EASY_PARAM_ID.EASY_PARAM_MEDIA_POSITION, ref param);
                alreadyTime = (int)(Int64)param / 1000;

                if (totalTime > 0)
                {

                    if (totalTime - alreadyTime <= 1)
                    {
                        timer1.Enabled = false;
                        timer2.Enabled = false;
                        lblTime.Text = "时长：00分:00秒/00分:00秒";
                        skinTrackBar1.Value = 0;
                        EasyPlayerPro_Close(mPlayer);
                        mPlayer = IntPtr.Zero;
                    }
                    else
                    {
                        lblTime.Text = string.Format("时长：{0:00}分:{1:00}秒/{2:00}分:{3:00}秒", alreadyTime / 60, (alreadyTime) % 60, totalTime / 60, (totalTime) % 60);
                    }
                }
                else
                {
                    lblTime.Text = string.Format("时长：{0:00}分:{1:00}秒/../..", alreadyTime / 60, (alreadyTime) % 60);
                }
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if(skinTrackBar1.Maximum>0 && alreadyTime>=0 && alreadyTime< skinTrackBar1.Maximum)
            {
                skinTrackBar1.Value = alreadyTime;
            }
        }

        private void skinTrackBar1_Scroll(object sender, EventArgs e)
        {
            timer2.Enabled = false;
        }

        private void skinTrackBar1_MouseCaptureChanged(object sender, EventArgs e)
        {
            EasyPlayerPro_Seek(mPlayer, skinTrackBar1.Value*1000);
            timer2.Enabled = true;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            IntPtr param = new IntPtr();
            param = (IntPtr)Convert.ToInt32(skinComboBox1.Text);
            EasyPlayerPro_Setparam(mPlayer, EASY_PARAM_ID.EASY_PARAM_PLAY_SPEED, ref param);
        }

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int SetWindowPos(IntPtr hWnd, int hWndInsertAfter, int x, int y, int Width, int Height, int flags);

        [DllImport("user32.dll", SetLastError = true)]
        static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        private void button7_Click(object sender, EventArgs e)
        {
            //this.Hide();
            //skinPanel2.Left = 0;
            //skinPanel2.Top = 0;
            //skinPanel2.Width = Screen.PrimaryScreen.Bounds.Width;
            //skinPanel2.Height = Screen.PrimaryScreen.Bounds.Height;
            //EasyPlayerPro_Resize(mPlayer, 0, 0, 0, Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.WorkingArea.Height);
            //SetParent(skinPanel2.Handle, IntPtr.Zero);
            //SetWindowPos(skinPanel2.Handle, -1, 0, 0, 0, 0, 1 | 2);
        }

        private void button8_Click(object sender, EventArgs e)
        {

            //this.skinPanel2.Location = new System.Drawing.Point(33, 22);
            //this.skinPanel2.Size = new System.Drawing.Size(1266, 883);
            //this.panel1.Location = new System.Drawing.Point(1, 1);
            //this.panel1.Size = new System.Drawing.Size(1264, 827);
            //EasyPlayerPro_Resize(mPlayer, 0, 0, 0, 1264, 827);
            //SetParent(skinPanel2.Handle, skinPanel2.Parent.Handle);
            //this.Show();
        }

        private void skinComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}

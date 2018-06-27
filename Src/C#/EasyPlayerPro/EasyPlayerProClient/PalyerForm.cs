using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using EasyPlayerProSDK;
using System.Threading;
using System.Runtime.InteropServices;
using System.Windows;

namespace EasyPlayerProClient
{
    public partial class PalyerForm : Form
    {
        private PlayerSDK.EasyPlayerProCallBack RealProCallBack = null;
        private IntPtr palyerHandle = IntPtr.Zero;
        private int channelID = -1;
        private bool isInit = false;
        private bool isElectronicZooming = false;
        private RENDER_FORMAT renderFormat = RENDER_FORMAT.RENDER_FORMAT_RGB24_GDI;
        private string ACTIVE_KEY = "64687538665969576B5A7341676A4662704D35397065354659584E35554778686557567955484A764C6D56345A56634D5671442F70654E4659584E355247467964326C755647566862556C7A5647686C516D567A644541794D4445345A57467A65513D3D";


        bool isDarew = false;

        public PalyerForm()
        {
            InitializeComponent();
            int ret = PlayerSDK.LibEasyPlayerPro_Activate(ACTIVE_KEY);
            if (ret != 0)
            {
                //Active Error!
            }
        }

        private int RealProSourceCallBack(EASY_CALLBACK_TYPE_ENUM callbackType, int channelId, IntPtr userPtr, MEDIA_TYPE mediaType, IntPtr pBuf, ref EASY_FRAME_INFO _frameInfo)
        {
            return 0;
        }

        private void Btn_Play_Click(object sender, EventArgs e)
        {
            var isPlay = (sender as Button).Text == "播放";
            if (isPlay)
            {
                int ret = -1;
                var streamURI = string.IsNullOrEmpty(StreamURI.Text) ? "rtsp://admin:a1234567@192.168.90.32:554/h264/ch1/main/av_stream" : StreamURI.Text;
                EASY_CHANNEL_SOURCE_TYPE_ENUM sourceType = GetSourceTypeByStreamURI(streamURI);
                bool overtcpType = tcpCheck.CheckState == CheckState.Checked;

                int queueSize = sourceType == EASY_CHANNEL_SOURCE_TYPE_ENUM.EASY_CHANNEL_SOURCE_TYPE_HLS ? 1024 * 1024 * 5 : 1024 * 1024 * 2;
                channelID = PlayerSDK.LibEasyPlayerPro_OpenStream(palyerHandle, sourceType, streamURI, MEDIA_TYPE.MEDIA_TYPE_VIDEO | MEDIA_TYPE.MEDIA_TYPE_AUDIO | MEDIA_TYPE.MEDIA_TYPE_EVENT, RealProCallBack, IntPtr.Zero, overTcp: overtcpType, queueSize: (uint)queueSize);

                ret = PlayerSDK.LibEasyPlayerPro_StartPlayStream(palyerHandle, channelID, this.playerPanel.Handle, renderFormat);
                //PlayerSDK.LibEasyPlayerPro_SetPlayFrameCache(palyerHandle, channelID, 6);
                if (ret == 0)
                {
                    PlayerSDK.LibEasyPlayerPro_StartPlaySound(palyerHandle, channelID);
                    this.Btn_Play.Text = "停止";
                }
            }
            else
            {
                int ret = PlayerSDK.LibEasyPlayerPro_StopPlayStream(palyerHandle, channelID);
                if (ret == 0)
                {
                    this.Btn_Play.Text = "播放";
                    channelID = -1;
                    this.playerPanel.Refresh();
                }
            }
        }

        private void StatisticTML_Click(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            int ret = -1;
            var checkState = (sender as ToolStripMenuItem).CheckState;
            if (checkState == CheckState.Unchecked)
            {
                ret = PlayerSDK.LibEasyPlayerPro_ShowStatisticalInfo(palyerHandle, channelID, true);
                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            }
            else
            {
                ret = PlayerSDK.LibEasyPlayerPro_ShowStatisticalInfo(palyerHandle, channelID, false);
                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
        }

        private void 清空帧队列ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int ret = -1;
            ret = PlayerSDK.LibEasyPlayerPro_ResetFrameQueue(palyerHandle, channelID);
        }

        private void 解码显示关键帧ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            int ret = -1;
            var checkState = (sender as ToolStripMenuItem).CheckState;
            if (checkState == CheckState.Unchecked)
            {
                ret = PlayerSDK.LibEasyPlayerPro_SetDecodeType(palyerHandle, channelID, true);
                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            }
            else
            {
                ret = PlayerSDK.LibEasyPlayerPro_SetDecodeType(palyerHandle, channelID, false);
                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
        }

        private void 视频翻转ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            int ret = -1;
            var checkState = (sender as ToolStripMenuItem).CheckState;
            if (checkState == CheckState.Unchecked)
            {
                ret = PlayerSDK.LibEasyPlayerPro_SetVideoFlip(palyerHandle, channelID, true);
                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            }
            else
            {
                ret = PlayerSDK.LibEasyPlayerPro_SetVideoFlip(palyerHandle, channelID, false);
                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
        }

        private void 叠加文字ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            int ret = -1;
            var checkState = (sender as ToolStripMenuItem).CheckState;
            if (checkState == CheckState.Unchecked)
            {
                ret = PlayerSDK.LibEasyPlayerPro_SetOverlayText(palyerHandle, channelID, DateTime.Now.ToString());
                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            }
            else
            {
                ret = PlayerSDK.LibEasyPlayerPro_ClearOverlayText(palyerHandle, channelID);
                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
        }

        private void 获取媒体信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int ret = -1;
            EASY_MEDIA_INFO_T _struct = new EASY_MEDIA_INFO_T();
            ret = PlayerSDK.LibEasyPlayerPro_GetStreamInfo(palyerHandle, channelID, ref _struct);
            PlayerSDK.LibEasyPlayerPro_SetOverlayText(palyerHandle, channelID, string.Format("videoWidth:{0},videoHeight:{1}", _struct.videoWidth, _struct.videoHeight));
            Thread.Sleep(1000);
            PlayerSDK.LibEasyPlayerPro_ClearOverlayText(palyerHandle, channelID);
        }

        private void 区域放大ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;
            Rect rect = new Rect { };
            int ret = -1;
            var checkState = (sender as ToolStripMenuItem).CheckState;
            if (checkState == CheckState.Unchecked)
            {
                rect = new Rect { X = 100, Y = 100, Width = playerPanel.Width / 2, Height = playerPanel.Height / 2 };

                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            }
            else
            {
                rect = new Rect { X = 100, Y = 100, Width = playerPanel.Width - 100, Height = playerPanel.Height - 100, };

                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
            ret = PlayerSDK.LibEasyPlayerPro_SetRenderRect(palyerHandle, channelID, rect);
            return;
        }

        private void 切换显示模式ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            int ret = -1;
            var checkState = (sender as ToolStripMenuItem).CheckState;
            if (checkState == CheckState.Unchecked)
            {
                ret = PlayerSDK.LibEasyPlayerPro_SetScaleDisplay(palyerHandle, channelID, true, Color.AliceBlue);
                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            }
            else
            {
                ret = PlayerSDK.LibEasyPlayerPro_SetScaleDisplay(palyerHandle, channelID, false, Color.AliceBlue);
                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
        }

        private void 录制D盘AAA文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            int ret = -1;
            var checkState = (sender as ToolStripMenuItem).CheckState;
            if (checkState == CheckState.Unchecked)
            {
                ret = PlayerSDK.LibEasyPlayerPro_StartRecording(palyerHandle, channelID, 10, 10);
                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            }
            else
            {
                ret = PlayerSDK.LibEasyPlayerPro_StopRecording(palyerHandle, channelID);
                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
        }

        private void 抓图ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int ret = -1;
            ret = PlayerSDK.LibEasyPlayerPro_SnapshotToFile(palyerHandle, channelID, ImageFormat.bmp);
        }

        private void 获取播放速度ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int ret = -1;
            ret = PlayerSDK.LibEasyPlayerPro_GetPlaySpeed(palyerHandle, channelID);
            PlayerSDK.LibEasyPlayerPro_SetOverlayText(palyerHandle, channelID, string.Format("播放倍率:{0}", ((PLAY_SPEED_ENUM)ret).ToString()));
            Thread.Sleep(1000);
            PlayerSDK.LibEasyPlayerPro_ClearOverlayText(palyerHandle, channelID);
        }

        private void 设置播放速度ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int ret = -1;
            var value = (PLAY_SPEED_ENUM)Enum.Parse(typeof(PLAY_SPEED_ENUM), ((ToolStripMenuItem)sender).Text);
            ret = PlayerSDK.LibEasyPlayerPro_SetPlaySpeed(palyerHandle, channelID, value);
        }

        private void 音频设备列表ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MIXER_DEVICE_INFO_T deviceInfo = new MIXER_DEVICE_INFO_T();
            int deviceCount = -1;
            int ret = -1;
            ret = PlayerSDK.LibEasyPlayerPro_GetAudioOutputDeviceList(palyerHandle, ref deviceInfo, ref deviceCount);

            PlayerSDK.LibEasyPlayerPro_SetOverlayText(palyerHandle, channelID, string.Format("声音设备个数:{0}", deviceCount));
            Thread.Sleep(2000);
            PlayerSDK.LibEasyPlayerPro_ClearOverlayText(palyerHandle, channelID);
        }

        private void 设置当前音频设备IDToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int ret = -1;
            MIXER_DEVICE_INFO_T deviceInfo = new MIXER_DEVICE_INFO_T();
            int deviceCount = -1;
            ret = PlayerSDK.LibEasyPlayerPro_SetAudioOutputDeviceId(palyerHandle, DateTime.Now.Minute);
            ret = PlayerSDK.LibEasyPlayerPro_SetAudioOutputDeviceName(palyerHandle, DateTime.Now.ToString());
            ret = PlayerSDK.LibEasyPlayerPro_GetAudioOutputDeviceList(palyerHandle, ref deviceInfo, ref deviceCount);
        }

        /// <summary>
        /// 电子放大
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            var checkState = (sender as ToolStripMenuItem).CheckState;

            isElectronicZooming = checkState == CheckState.Unchecked;
            if (isElectronicZooming)
                (sender as ToolStripMenuItem).CheckState = CheckState.Checked;
            else
            {
                PlayerSDK.libEasyPlayerPro_ResetElectronicZoom(palyerHandle, channelID);
                (sender as ToolStripMenuItem).CheckState = CheckState.Unchecked;
            }
        }

        private void 设置音量ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int ret = -1;
            ret = PlayerSDK.LibEasyPlayerPro_SetAudioVolume(palyerHandle, DateTime.Now.Minute + 20);
            var volume = PlayerSDK.LibEasyPlayerPro_GetAudioVolume(palyerHandle);

            PlayerSDK.LibEasyPlayerPro_SetOverlayText(palyerHandle, channelID, string.Format("设置音量为:{0}", volume));
            Thread.Sleep(2000);
            PlayerSDK.LibEasyPlayerPro_ClearOverlayText(palyerHandle, channelID);
        }

        private void PalyerForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (isInit)
                PlayerSDK.LibEasyPlayerPro_Release(ref palyerHandle);
        }

        private void PalyerForm_Load(object sender, EventArgs e)
        {
            if (PlayerSDK.LibEasyPlayerPro_Create(ref palyerHandle, 128) == 0)
                isInit = true;
            RealProCallBack = new PlayerSDK.EasyPlayerProCallBack(RealProSourceCallBack);

            this.DecodeType.SelectedItem = "GDI";
            this.RightToLeft = RightToLeft.Inherit;

            this.playerPanel.MouseDown += new MouseEventHandler(frmMain_MouseDown);
            this.playerPanel.MouseMove += new MouseEventHandler(frmMain_MouseMove);
            this.playerPanel.MouseUp += new MouseEventHandler(frmMain_MouseUp);
        }

        private void DecodeType_SelectedIndexChanged(object sender, EventArgs e)
        {
            var text = (sender as ComboBox).Text;
            switch (text.ToUpper())
            {
                case "GDI":
                    renderFormat = RENDER_FORMAT.RENDER_FORMAT_RGB24_GDI; break;
                case "RGB565":
                    renderFormat = RENDER_FORMAT.RENDER_FORMAT_RGB565; break;
                case "YV12":
                    renderFormat = RENDER_FORMAT.RENDER_FORMAT_YV12; break;
                case "YUY2":
                    renderFormat = RENDER_FORMAT.RENDER_FORMAT_YUY2; break;
                default:
                    break;
            }
        }

        private void volumn_CB_CheckedChanged(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            int ret = -1;
            var checkState = (sender as CheckBox).Checked;
            if (checkState)
            {
                ret = PlayerSDK.LibEasyPlayerPro_StartPlaySound(palyerHandle, channelID);
                (sender as CheckBox).CheckState = CheckState.Checked;
            }
            else
            {
                ret = PlayerSDK.LibEasyPlayerPro_StopPlaySound(palyerHandle, channelID);
                (sender as CheckBox).CheckState = CheckState.Unchecked;
            }
        }

        private void CachetrackBar_ValueChanged(object sender, EventArgs e)
        {
            if (channelID <= 0)
                return;

            var cache = (sender as TrackBar).Value;
            int ret = PlayerSDK.LibEasyPlayerPro_SetPlayFrameCache(palyerHandle, channelID, cache);
        }

        private void frmMain_MouseUp(object sender, MouseEventArgs e)
        {
            isDarew = false;

            var ret = PlayerSDK.libEasyPlayerPro_SetElectronicZoom(palyerHandle, channelID, 1);

        }

        private void frmMain_MouseMove(object sender, MouseEventArgs e)
        {
            if (!isDarew) return;
            var playerPanel = this.playerPanel;
            System.Drawing.Point formPoint = playerPanel.PointToClient(Control.MousePosition);
            var xPrecent = (float)(formPoint.X / (double)playerPanel.Width) * 100;
            var yPrecent = (float)(formPoint.Y / (double)playerPanel.Height) * 100;
            var ret = PlayerSDK.libEasyPlayerPro_SetElectronicZoomEndPoint(palyerHandle, channelID, xPrecent, yPrecent);
        }

        private void frmMain_MouseDown(object sender, MouseEventArgs e)
        {
            if (!isElectronicZooming || channelID <= 0)
                return;

            isDarew = true;
            var playerPanel = this.playerPanel;
            System.Drawing.Point formPoint = playerPanel.PointToClient(Control.MousePosition);
            var xPrecent = (float)(formPoint.X / (double)playerPanel.Width) * 100;
            var yPrecent = (float)(formPoint.Y / (double)playerPanel.Height) * 100;

            var ret = PlayerSDK.libEasyPlayerPro_SetElectronicZoomStartPoint(palyerHandle, channelID, xPrecent, yPrecent, true);
        }

        #region PrivateHelper

        private EASY_CHANNEL_SOURCE_TYPE_ENUM GetSourceTypeByStreamURI(string streamUri)
        {
            string _streamUri = streamUri.ToLower();
            if (_streamUri.IndexOf("rtsp") == 0)
                return EASY_CHANNEL_SOURCE_TYPE_ENUM.EASY_CHANNEL_SOURCE_TYPE_RTSP;
            if (_streamUri.IndexOf("rtmp") == 0)
                return EASY_CHANNEL_SOURCE_TYPE_ENUM.EASY_CHANNEL_SOURCE_TYPE_RTMP;
            if (_streamUri.IndexOf("http") == 0)
                return EASY_CHANNEL_SOURCE_TYPE_ENUM.EASY_CHANNEL_SOURCE_TYPE_HLS;
            if (_streamUri.IndexOf("file") == 0)
                return EASY_CHANNEL_SOURCE_TYPE_ENUM.EASY_CHANNEL_SOURCE_TYPE_FILE;

            return EASY_CHANNEL_SOURCE_TYPE_ENUM.EASY_CHANNEL_SOURCE_TYPE_RTSP;
        }
        #endregion
    }
}

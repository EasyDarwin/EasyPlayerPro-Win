namespace EasyPlayerProClient
{
    partial class PalyerForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(PalyerForm));
            this.playerPanel = new System.Windows.Forms.Panel();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.StatisticTML = new System.Windows.Forms.ToolStripMenuItem();
            this.清空帧队列ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.解码显示关键帧ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.视频翻转ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取媒体信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.叠加文字ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.区域放大ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.切换显示模式ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.录制D盘AAA文件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.抓图ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.设置播放速度ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.正常ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem6 = new System.Windows.Forms.ToolStripMenuItem();
            this.pLAYSPEEDNORMALToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取播放速度ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.声音ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.音频设备列表ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.设置当前音频设备IDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.设置音量ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Btn_Play = new System.Windows.Forms.Button();
            this.Label = new System.Windows.Forms.Label();
            this.StreamURI = new System.Windows.Forms.TextBox();
            this.tcpCheck = new System.Windows.Forms.CheckBox();
            this.DecodeType = new System.Windows.Forms.ComboBox();
            this.CachetrackBar = new System.Windows.Forms.TrackBar();
            this.volumn_CB = new System.Windows.Forms.CheckBox();
            this.contextMenuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.CachetrackBar)).BeginInit();
            this.SuspendLayout();
            // 
            // playerPanel
            // 
            this.playerPanel.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.playerPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.playerPanel.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("playerPanel.BackgroundImage")));
            this.playerPanel.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.playerPanel.ContextMenuStrip = this.contextMenuStrip1;
            this.playerPanel.Location = new System.Drawing.Point(3, 3);
            this.playerPanel.Name = "playerPanel";
            this.playerPanel.Size = new System.Drawing.Size(927, 558);
            this.playerPanel.TabIndex = 0;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.StatisticTML,
            this.清空帧队列ToolStripMenuItem,
            this.解码显示关键帧ToolStripMenuItem,
            this.视频翻转ToolStripMenuItem,
            this.获取媒体信息ToolStripMenuItem,
            this.叠加文字ToolStripMenuItem,
            this.toolStripMenuItem1,
            this.区域放大ToolStripMenuItem,
            this.切换显示模式ToolStripMenuItem,
            this.录制D盘AAA文件ToolStripMenuItem,
            this.抓图ToolStripMenuItem,
            this.设置播放速度ToolStripMenuItem,
            this.获取播放速度ToolStripMenuItem,
            this.声音ToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(178, 312);
            // 
            // StatisticTML
            // 
            this.StatisticTML.Name = "StatisticTML";
            this.StatisticTML.Size = new System.Drawing.Size(177, 22);
            this.StatisticTML.Text = "统计信息";
            this.StatisticTML.Click += new System.EventHandler(this.StatisticTML_Click);
            // 
            // 清空帧队列ToolStripMenuItem
            // 
            this.清空帧队列ToolStripMenuItem.Name = "清空帧队列ToolStripMenuItem";
            this.清空帧队列ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.清空帧队列ToolStripMenuItem.Text = "清空帧队列";
            this.清空帧队列ToolStripMenuItem.Click += new System.EventHandler(this.清空帧队列ToolStripMenuItem_Click);
            // 
            // 解码显示关键帧ToolStripMenuItem
            // 
            this.解码显示关键帧ToolStripMenuItem.Name = "解码显示关键帧ToolStripMenuItem";
            this.解码显示关键帧ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.解码显示关键帧ToolStripMenuItem.Text = "解码显示关键帧";
            this.解码显示关键帧ToolStripMenuItem.Click += new System.EventHandler(this.解码显示关键帧ToolStripMenuItem_Click);
            // 
            // 视频翻转ToolStripMenuItem
            // 
            this.视频翻转ToolStripMenuItem.Name = "视频翻转ToolStripMenuItem";
            this.视频翻转ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.视频翻转ToolStripMenuItem.Text = "视频翻转";
            this.视频翻转ToolStripMenuItem.Click += new System.EventHandler(this.视频翻转ToolStripMenuItem_Click);
            // 
            // 获取媒体信息ToolStripMenuItem
            // 
            this.获取媒体信息ToolStripMenuItem.Name = "获取媒体信息ToolStripMenuItem";
            this.获取媒体信息ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.获取媒体信息ToolStripMenuItem.Text = "获取媒体信息";
            this.获取媒体信息ToolStripMenuItem.Click += new System.EventHandler(this.获取媒体信息ToolStripMenuItem_Click);
            // 
            // 叠加文字ToolStripMenuItem
            // 
            this.叠加文字ToolStripMenuItem.Name = "叠加文字ToolStripMenuItem";
            this.叠加文字ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.叠加文字ToolStripMenuItem.Text = "叠加文字";
            this.叠加文字ToolStripMenuItem.Click += new System.EventHandler(this.叠加文字ToolStripMenuItem_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(177, 22);
            this.toolStripMenuItem1.Text = "电子放大";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // 区域放大ToolStripMenuItem
            // 
            this.区域放大ToolStripMenuItem.Name = "区域放大ToolStripMenuItem";
            this.区域放大ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.区域放大ToolStripMenuItem.Text = "区域放大";
            this.区域放大ToolStripMenuItem.Visible = false;
            this.区域放大ToolStripMenuItem.Click += new System.EventHandler(this.区域放大ToolStripMenuItem_Click);
            // 
            // 切换显示模式ToolStripMenuItem
            // 
            this.切换显示模式ToolStripMenuItem.Name = "切换显示模式ToolStripMenuItem";
            this.切换显示模式ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.切换显示模式ToolStripMenuItem.Text = "比例显示";
            this.切换显示模式ToolStripMenuItem.Click += new System.EventHandler(this.切换显示模式ToolStripMenuItem_Click);
            // 
            // 录制D盘AAA文件ToolStripMenuItem
            // 
            this.录制D盘AAA文件ToolStripMenuItem.Name = "录制D盘AAA文件ToolStripMenuItem";
            this.录制D盘AAA文件ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.录制D盘AAA文件ToolStripMenuItem.Text = "录制[D盘AAA文件]";
            this.录制D盘AAA文件ToolStripMenuItem.Click += new System.EventHandler(this.录制D盘AAA文件ToolStripMenuItem_Click);
            // 
            // 抓图ToolStripMenuItem
            // 
            this.抓图ToolStripMenuItem.Name = "抓图ToolStripMenuItem";
            this.抓图ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.抓图ToolStripMenuItem.Text = "抓图";
            this.抓图ToolStripMenuItem.Click += new System.EventHandler(this.抓图ToolStripMenuItem_Click);
            // 
            // 设置播放速度ToolStripMenuItem
            // 
            this.设置播放速度ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.正常ToolStripMenuItem,
            this.toolStripMenuItem5,
            this.toolStripMenuItem6,
            this.pLAYSPEEDNORMALToolStripMenuItem});
            this.设置播放速度ToolStripMenuItem.Name = "设置播放速度ToolStripMenuItem";
            this.设置播放速度ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.设置播放速度ToolStripMenuItem.Text = "设置播放速度";
            this.设置播放速度ToolStripMenuItem.Click += new System.EventHandler(this.设置播放速度ToolStripMenuItem_Click);
            // 
            // 正常ToolStripMenuItem
            // 
            this.正常ToolStripMenuItem.Name = "正常ToolStripMenuItem";
            this.正常ToolStripMenuItem.Size = new System.Drawing.Size(206, 22);
            this.正常ToolStripMenuItem.Text = "PLAY_SPEED_PAUSED";
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(206, 22);
            this.toolStripMenuItem5.Text = "PLAY_SPEED_SLOW_X4";
            // 
            // toolStripMenuItem6
            // 
            this.toolStripMenuItem6.Name = "toolStripMenuItem6";
            this.toolStripMenuItem6.Size = new System.Drawing.Size(206, 22);
            this.toolStripMenuItem6.Text = "PLAY_SPEED_FAST_X4";
            // 
            // pLAYSPEEDNORMALToolStripMenuItem
            // 
            this.pLAYSPEEDNORMALToolStripMenuItem.Name = "pLAYSPEEDNORMALToolStripMenuItem";
            this.pLAYSPEEDNORMALToolStripMenuItem.Size = new System.Drawing.Size(206, 22);
            this.pLAYSPEEDNORMALToolStripMenuItem.Text = "PLAY_SPEED_NORMAL";
            // 
            // 获取播放速度ToolStripMenuItem
            // 
            this.获取播放速度ToolStripMenuItem.Name = "获取播放速度ToolStripMenuItem";
            this.获取播放速度ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.获取播放速度ToolStripMenuItem.Text = "获取播放速度";
            this.获取播放速度ToolStripMenuItem.Click += new System.EventHandler(this.获取播放速度ToolStripMenuItem_Click);
            // 
            // 声音ToolStripMenuItem
            // 
            this.声音ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.音频设备列表ToolStripMenuItem,
            this.设置当前音频设备IDToolStripMenuItem,
            this.设置音量ToolStripMenuItem});
            this.声音ToolStripMenuItem.Name = "声音ToolStripMenuItem";
            this.声音ToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.声音ToolStripMenuItem.Text = "声音";
            // 
            // 音频设备列表ToolStripMenuItem
            // 
            this.音频设备列表ToolStripMenuItem.Name = "音频设备列表ToolStripMenuItem";
            this.音频设备列表ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.音频设备列表ToolStripMenuItem.Text = "音频设备列表";
            this.音频设备列表ToolStripMenuItem.Click += new System.EventHandler(this.音频设备列表ToolStripMenuItem_Click);
            // 
            // 设置当前音频设备IDToolStripMenuItem
            // 
            this.设置当前音频设备IDToolStripMenuItem.Name = "设置当前音频设备IDToolStripMenuItem";
            this.设置当前音频设备IDToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.设置当前音频设备IDToolStripMenuItem.Text = "设置当前音频设备";
            this.设置当前音频设备IDToolStripMenuItem.Click += new System.EventHandler(this.设置当前音频设备IDToolStripMenuItem_Click);
            // 
            // 设置音量ToolStripMenuItem
            // 
            this.设置音量ToolStripMenuItem.Name = "设置音量ToolStripMenuItem";
            this.设置音量ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.设置音量ToolStripMenuItem.Text = "设置音量";
            this.设置音量ToolStripMenuItem.Click += new System.EventHandler(this.设置音量ToolStripMenuItem_Click);
            // 
            // Btn_Play
            // 
            this.Btn_Play.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.Btn_Play.Location = new System.Drawing.Point(838, 567);
            this.Btn_Play.Name = "Btn_Play";
            this.Btn_Play.Size = new System.Drawing.Size(82, 31);
            this.Btn_Play.TabIndex = 8;
            this.Btn_Play.Text = "播放";
            this.Btn_Play.UseVisualStyleBackColor = true;
            this.Btn_Play.Click += new System.EventHandler(this.Btn_Play_Click);
            // 
            // Label
            // 
            this.Label.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.Label.AutoSize = true;
            this.Label.Location = new System.Drawing.Point(6, 576);
            this.Label.Name = "Label";
            this.Label.Size = new System.Drawing.Size(65, 12);
            this.Label.TabIndex = 7;
            this.Label.Text = "播放地址：";
            // 
            // StreamURI
            // 
            this.StreamURI.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.StreamURI.Location = new System.Drawing.Point(77, 572);
            this.StreamURI.Name = "StreamURI";
            this.StreamURI.Size = new System.Drawing.Size(314, 21);
            this.StreamURI.TabIndex = 6;
            this.StreamURI.Text = "http://live.hkstv.hk.lxdns.com/live/hks/playlist.m3u8";
            // 
            // tcpCheck
            // 
            this.tcpCheck.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.tcpCheck.AutoSize = true;
            this.tcpCheck.Location = new System.Drawing.Point(416, 575);
            this.tcpCheck.Name = "tcpCheck";
            this.tcpCheck.Size = new System.Drawing.Size(42, 16);
            this.tcpCheck.TabIndex = 9;
            this.tcpCheck.Text = "TCP";
            this.tcpCheck.UseVisualStyleBackColor = true;
            // 
            // DecodeType
            // 
            this.DecodeType.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.DecodeType.AutoCompleteCustomSource.AddRange(new string[] {
            "AA",
            "BB",
            "CC"});
            this.DecodeType.FormattingEnabled = true;
            this.DecodeType.Items.AddRange(new object[] {
            "YUY2",
            "YV12",
            "RGB565",
            "GDI"});
            this.DecodeType.Location = new System.Drawing.Point(553, 573);
            this.DecodeType.Name = "DecodeType";
            this.DecodeType.Size = new System.Drawing.Size(121, 20);
            this.DecodeType.TabIndex = 10;
            this.DecodeType.SelectedIndexChanged += new System.EventHandler(this.DecodeType_SelectedIndexChanged);
            // 
            // CachetrackBar
            // 
            this.CachetrackBar.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CachetrackBar.Location = new System.Drawing.Point(680, 567);
            this.CachetrackBar.Maximum = 30;
            this.CachetrackBar.Name = "CachetrackBar";
            this.CachetrackBar.Size = new System.Drawing.Size(132, 45);
            this.CachetrackBar.TabIndex = 11;
            this.CachetrackBar.Value = 3;
            this.CachetrackBar.ValueChanged += new System.EventHandler(this.CachetrackBar_ValueChanged);
            // 
            // volumn_CB
            // 
            this.volumn_CB.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.volumn_CB.AutoSize = true;
            this.volumn_CB.Checked = true;
            this.volumn_CB.CheckState = System.Windows.Forms.CheckState.Checked;
            this.volumn_CB.Location = new System.Drawing.Point(464, 575);
            this.volumn_CB.Name = "volumn_CB";
            this.volumn_CB.Size = new System.Drawing.Size(48, 16);
            this.volumn_CB.TabIndex = 12;
            this.volumn_CB.Text = "声音";
            this.volumn_CB.UseVisualStyleBackColor = true;
            this.volumn_CB.CheckedChanged += new System.EventHandler(this.volumn_CB_CheckedChanged);
            // 
            // PalyerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(932, 598);
            this.Controls.Add(this.volumn_CB);
            this.Controls.Add(this.CachetrackBar);
            this.Controls.Add(this.DecodeType);
            this.Controls.Add(this.tcpCheck);
            this.Controls.Add(this.Btn_Play);
            this.Controls.Add(this.Label);
            this.Controls.Add(this.StreamURI);
            this.Controls.Add(this.playerPanel);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MinimumSize = new System.Drawing.Size(948, 637);
            this.Name = "PalyerForm";
            this.Text = "EasyPlayerPro 播放器";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PalyerForm_FormClosing);
            this.Load += new System.EventHandler(this.PalyerForm_Load);
            this.contextMenuStrip1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.CachetrackBar)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel playerPanel;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem StatisticTML;
        private System.Windows.Forms.ToolStripMenuItem 清空帧队列ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 解码显示关键帧ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 视频翻转ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取媒体信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 叠加文字ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 区域放大ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 切换显示模式ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 录制D盘AAA文件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 抓图ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 设置播放速度ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 正常ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem5;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem6;
        private System.Windows.Forms.ToolStripMenuItem pLAYSPEEDNORMALToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取播放速度ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 声音ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 音频设备列表ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 设置当前音频设备IDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 设置音量ToolStripMenuItem;
        private System.Windows.Forms.Button Btn_Play;
        private System.Windows.Forms.Label Label;
        private System.Windows.Forms.TextBox StreamURI;
        private System.Windows.Forms.CheckBox tcpCheck;
        private System.Windows.Forms.ComboBox DecodeType;
        private System.Windows.Forms.TrackBar CachetrackBar;
        private System.Windows.Forms.CheckBox volumn_CB;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
    }
}


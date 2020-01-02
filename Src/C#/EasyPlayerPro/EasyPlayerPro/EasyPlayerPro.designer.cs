namespace PlayerSDK
{
    partial class EasyPlayerPro
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.skinPanel2 = new System.Windows.Forms.Panel();
            this.textURL = new System.Windows.Forms.TextBox();
            this.skinTrackBar1 = new System.Windows.Forms.TrackBar();
            this.skinPanel3 = new System.Windows.Forms.Panel();
            this.button8 = new System.Windows.Forms.Button();
            this.lblTime = new System.Windows.Forms.Label();
            this.button7 = new System.Windows.Forms.Button();
            this.skinComboBox1 = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.panel1 = new System.Windows.Forms.Panel();
            this.skinPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.skinTrackBar1)).BeginInit();
            this.skinPanel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // skinPanel2
            // 
            this.skinPanel2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.skinPanel2.Controls.Add(this.textURL);
            this.skinPanel2.Controls.Add(this.skinTrackBar1);
            this.skinPanel2.Location = new System.Drawing.Point(33, 22);
            this.skinPanel2.Name = "skinPanel2";
            this.skinPanel2.Size = new System.Drawing.Size(994, 733);
            this.skinPanel2.TabIndex = 1;
            // 
            // textURL
            // 
            this.textURL.Location = new System.Drawing.Point(4, 539);
            this.textURL.Name = "textURL";
            this.textURL.Size = new System.Drawing.Size(983, 25);
            this.textURL.TabIndex = 10;
            this.textURL.Text = "http://demo.easydss.com:10080/fvod/ULJyMRhZR/video.m3u8";
            // 
            // skinTrackBar1
            // 
            this.skinTrackBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.skinTrackBar1.AutoSize = false;
            this.skinTrackBar1.Location = new System.Drawing.Point(4, 510);
            this.skinTrackBar1.Name = "skinTrackBar1";
            this.skinTrackBar1.Size = new System.Drawing.Size(987, 22);
            this.skinTrackBar1.TabIndex = 9;
            this.skinTrackBar1.Scroll += new System.EventHandler(this.skinTrackBar1_Scroll);
            this.skinTrackBar1.MouseCaptureChanged += new System.EventHandler(this.skinTrackBar1_MouseCaptureChanged);
            // 
            // skinPanel3
            // 
            this.skinPanel3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.skinPanel3.BackColor = System.Drawing.Color.LightGray;
            this.skinPanel3.Controls.Add(this.button8);
            this.skinPanel3.Controls.Add(this.lblTime);
            this.skinPanel3.Controls.Add(this.button7);
            this.skinPanel3.Controls.Add(this.skinComboBox1);
            this.skinPanel3.Controls.Add(this.button1);
            this.skinPanel3.Controls.Add(this.button6);
            this.skinPanel3.Controls.Add(this.button2);
            this.skinPanel3.Controls.Add(this.button3);
            this.skinPanel3.Controls.Add(this.button5);
            this.skinPanel3.Controls.Add(this.button4);
            this.skinPanel3.Location = new System.Drawing.Point(33, 596);
            this.skinPanel3.Name = "skinPanel3";
            this.skinPanel3.Size = new System.Drawing.Size(991, 67);
            this.skinPanel3.TabIndex = 0;
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(480, 21);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(50, 30);
            this.button8.TabIndex = 13;
            this.button8.Text = "退出";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // lblTime
            // 
            this.lblTime.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.lblTime.AutoSize = true;
            this.lblTime.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblTime.Location = new System.Drawing.Point(748, 27);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(200, 20);
            this.lblTime.TabIndex = 8;
            this.lblTime.Text = "时长：00分:00秒/00分:00秒";
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(424, 21);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(50, 30);
            this.button7.TabIndex = 12;
            this.button7.Text = "全屏";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // skinComboBox1
            // 
            this.skinComboBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.skinComboBox1.AutoCompleteCustomSource.AddRange(new string[] {
            "AA",
            "BB",
            "CC"});
            this.skinComboBox1.FormatString = "N2";
            this.skinComboBox1.FormattingEnabled = true;
            this.skinComboBox1.Items.AddRange(new object[] {
            "10",
            "20",
            "30",
            "40",
            "50",
            "60",
            "70",
            "80",
            "90",
            "100",
            "200",
            "300",
            "400",
            "500",
            "600"});
            this.skinComboBox1.Location = new System.Drawing.Point(333, 23);
            this.skinComboBox1.Name = "skinComboBox1";
            this.skinComboBox1.Size = new System.Drawing.Size(83, 23);
            this.skinComboBox1.TabIndex = 11;
            this.skinComboBox1.SelectedIndexChanged += new System.EventHandler(this.skinComboBox1_SelectedIndexChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(222, 22);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(50, 30);
            this.button1.TabIndex = 1;
            this.button1.Text = "播放";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(276, 21);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(50, 30);
            this.button6.TabIndex = 10;
            this.button6.Text = "速度";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(62, 22);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(50, 30);
            this.button2.TabIndex = 2;
            this.button2.Text = "停止";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(115, 22);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(50, 30);
            this.button3.TabIndex = 3;
            this.button3.Text = "暂停";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(6, 22);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(50, 30);
            this.button5.TabIndex = 5;
            this.button5.Text = "开始";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(169, 22);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(50, 30);
            this.button4.TabIndex = 4;
            this.button4.Text = "单帧";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // timer2
            // 
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Location = new System.Drawing.Point(33, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(994, 526);
            this.panel1.TabIndex = 1;
            // 
            // EasyPlayerPro
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1039, 667);
            this.Controls.Add(this.skinPanel3);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.skinPanel2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.HelpButton = true;
            this.MaximizeBox = false;
            this.Name = "EasyPlayerPro";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "EasyPlayerPro";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.PalyerForm_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.PlayerForm_FormClosed);
            this.Load += new System.EventHandler(this.PalyerForm_Load);
            this.skinPanel2.ResumeLayout(false);
            this.skinPanel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.skinTrackBar1)).EndInit();
            this.skinPanel3.ResumeLayout(false);
            this.skinPanel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel skinPanel2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.TrackBar skinTrackBar1;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.ComboBox skinComboBox1;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Panel skinPanel3;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox textURL;
    }
}
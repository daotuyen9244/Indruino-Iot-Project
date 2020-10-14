namespace C_sharp_LOGIN
{
    partial class F_Main
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
            BunifuAnimatorNS.Animation animation1 = new BunifuAnimatorNS.Animation();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(F_Main));
            this.panel1 = new System.Windows.Forms.Panel();
            this.chk_status_mqtt = new Bunifu.Framework.UI.BunifuCheckbox();
            this.btn_connect = new Guna.UI2.WinForms.Guna2Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.tb_port = new System.Windows.Forms.TextBox();
            this.tb_broker = new System.Windows.Forms.TextBox();
            this.pnl_container1 = new System.Windows.Forms.Panel();
            this.pnl_container = new System.Windows.Forms.Panel();
            this.bunifuTransition1 = new BunifuAnimatorNS.BunifuTransition(this.components);
            this.panel2 = new System.Windows.Forms.Panel();
            this.guna2CustomGradientPanel1 = new Guna.UI2.WinForms.Guna2CustomGradientPanel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.iconButton2 = new FontAwesome.Sharp.IconButton();
            this.tb_state = new System.Windows.Forms.Label();
            this.btn_in_out = new Guna.UI2.WinForms.Guna2Button();
            this.btn_config_baud = new Guna.UI2.WinForms.Guna2Button();
            this.btn_config_mega = new Guna.UI2.WinForms.Guna2Button();
            this.btn_adc = new Guna.UI2.WinForms.Guna2Button();
            this.btn_config_esp = new Guna.UI2.WinForms.Guna2Button();
            this.bunifuElipse1 = new Bunifu.Framework.UI.BunifuElipse(this.components);
            this.bunifuDragControl1 = new Bunifu.Framework.UI.BunifuDragControl(this.components);
            this.panel1.SuspendLayout();
            this.pnl_container1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.guna2CustomGradientPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Controls.Add(this.chk_status_mqtt);
            this.panel1.Controls.Add(this.btn_connect);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.tb_port);
            this.panel1.Controls.Add(this.tb_broker);
            this.bunifuTransition1.SetDecoration(this.panel1, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.panel1, "panel1");
            this.panel1.Name = "panel1";
            // 
            // chk_status_mqtt
            // 
            this.chk_status_mqtt.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(132)))), ((int)(((byte)(135)))), ((int)(((byte)(140)))));
            this.chk_status_mqtt.ChechedOffColor = System.Drawing.Color.FromArgb(((int)(((byte)(132)))), ((int)(((byte)(135)))), ((int)(((byte)(140)))));
            this.chk_status_mqtt.Checked = false;
            this.chk_status_mqtt.CheckedOnColor = System.Drawing.Color.FromArgb(((int)(((byte)(51)))), ((int)(((byte)(205)))), ((int)(((byte)(117)))));
            this.bunifuTransition1.SetDecoration(this.chk_status_mqtt, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.chk_status_mqtt, "chk_status_mqtt");
            this.chk_status_mqtt.ForeColor = System.Drawing.Color.White;
            this.chk_status_mqtt.Name = "chk_status_mqtt";
            // 
            // btn_connect
            // 
            this.btn_connect.CheckedState.Parent = this.btn_connect;
            this.btn_connect.CustomImages.Parent = this.btn_connect;
            this.bunifuTransition1.SetDecoration(this.btn_connect, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.btn_connect, "btn_connect");
            this.btn_connect.ForeColor = System.Drawing.Color.White;
            this.btn_connect.HoverState.Parent = this.btn_connect;
            this.btn_connect.Name = "btn_connect";
            this.btn_connect.ShadowDecoration.Parent = this.btn_connect;
            this.btn_connect.Click += new System.EventHandler(this.btn_connect_Click);
            // 
            // label2
            // 
            resources.ApplyResources(this.label2, "label2");
            this.bunifuTransition1.SetDecoration(this.label2, BunifuAnimatorNS.DecorationType.None);
            this.label2.Name = "label2";
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.bunifuTransition1.SetDecoration(this.label1, BunifuAnimatorNS.DecorationType.None);
            this.label1.Name = "label1";
            // 
            // tb_port
            // 
            this.bunifuTransition1.SetDecoration(this.tb_port, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.tb_port, "tb_port");
            this.tb_port.Name = "tb_port";
            // 
            // tb_broker
            // 
            this.bunifuTransition1.SetDecoration(this.tb_broker, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.tb_broker, "tb_broker");
            this.tb_broker.Name = "tb_broker";
            // 
            // pnl_container1
            // 
            this.pnl_container1.Controls.Add(this.pnl_container);
            this.pnl_container1.Controls.Add(this.panel1);
            this.bunifuTransition1.SetDecoration(this.pnl_container1, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.pnl_container1, "pnl_container1");
            this.pnl_container1.Name = "pnl_container1";
            // 
            // pnl_container
            // 
            this.pnl_container.BackColor = System.Drawing.Color.White;
            this.bunifuTransition1.SetDecoration(this.pnl_container, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.pnl_container, "pnl_container");
            this.pnl_container.Name = "pnl_container";
            // 
            // bunifuTransition1
            // 
            this.bunifuTransition1.AnimationType = BunifuAnimatorNS.AnimationType.ScaleAndRotate;
            this.bunifuTransition1.Cursor = null;
            animation1.AnimateOnlyDifferences = true;
            animation1.BlindCoeff = ((System.Drawing.PointF)(resources.GetObject("animation1.BlindCoeff")));
            animation1.LeafCoeff = 0F;
            animation1.MaxTime = 1F;
            animation1.MinTime = 0F;
            animation1.MosaicCoeff = ((System.Drawing.PointF)(resources.GetObject("animation1.MosaicCoeff")));
            animation1.MosaicShift = ((System.Drawing.PointF)(resources.GetObject("animation1.MosaicShift")));
            animation1.MosaicSize = 0;
            animation1.Padding = new System.Windows.Forms.Padding(30);
            animation1.RotateCoeff = 0.5F;
            animation1.RotateLimit = 0.2F;
            animation1.ScaleCoeff = ((System.Drawing.PointF)(resources.GetObject("animation1.ScaleCoeff")));
            animation1.SlideCoeff = ((System.Drawing.PointF)(resources.GetObject("animation1.SlideCoeff")));
            animation1.TimeCoeff = 0F;
            animation1.TransparencyCoeff = 0F;
            this.bunifuTransition1.DefaultAnimation = animation1;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.White;
            this.panel2.Controls.Add(this.guna2CustomGradientPanel1);
            this.bunifuTransition1.SetDecoration(this.panel2, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.panel2, "panel2");
            this.panel2.Name = "panel2";
            // 
            // guna2CustomGradientPanel1
            // 
            this.guna2CustomGradientPanel1.BackColor = System.Drawing.Color.Transparent;
            this.guna2CustomGradientPanel1.BorderRadius = 18;
            this.guna2CustomGradientPanel1.Controls.Add(this.pictureBox1);
            this.guna2CustomGradientPanel1.Controls.Add(this.iconButton2);
            this.guna2CustomGradientPanel1.Controls.Add(this.tb_state);
            this.guna2CustomGradientPanel1.Controls.Add(this.btn_in_out);
            this.guna2CustomGradientPanel1.Controls.Add(this.btn_config_baud);
            this.guna2CustomGradientPanel1.Controls.Add(this.btn_config_mega);
            this.guna2CustomGradientPanel1.Controls.Add(this.btn_adc);
            this.guna2CustomGradientPanel1.Controls.Add(this.btn_config_esp);
            this.bunifuTransition1.SetDecoration(this.guna2CustomGradientPanel1, BunifuAnimatorNS.DecorationType.None);
            this.guna2CustomGradientPanel1.FillColor = System.Drawing.Color.Silver;
            this.guna2CustomGradientPanel1.FillColor2 = System.Drawing.Color.Silver;
            this.guna2CustomGradientPanel1.FillColor3 = System.Drawing.Color.Silver;
            this.guna2CustomGradientPanel1.FillColor4 = System.Drawing.Color.Silver;
            resources.ApplyResources(this.guna2CustomGradientPanel1, "guna2CustomGradientPanel1");
            this.guna2CustomGradientPanel1.Name = "guna2CustomGradientPanel1";
            this.guna2CustomGradientPanel1.ShadowDecoration.Parent = this.guna2CustomGradientPanel1;
            // 
            // pictureBox1
            // 
            this.bunifuTransition1.SetDecoration(this.pictureBox1, BunifuAnimatorNS.DecorationType.None);
            this.pictureBox1.Image = global::C_sharp_LOGIN.Properties.Resources.logo;
            resources.ApplyResources(this.pictureBox1, "pictureBox1");
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.TabStop = false;
            // 
            // iconButton2
            // 
            this.bunifuTransition1.SetDecoration(this.iconButton2, BunifuAnimatorNS.DecorationType.None);
            this.iconButton2.FlatAppearance.BorderSize = 0;
            resources.ApplyResources(this.iconButton2, "iconButton2");
            this.iconButton2.Flip = FontAwesome.Sharp.FlipOrientation.Normal;
            this.iconButton2.IconChar = FontAwesome.Sharp.IconChar.Futbol;
            this.iconButton2.IconColor = System.Drawing.Color.Black;
            this.iconButton2.IconSize = 16;
            this.iconButton2.Name = "iconButton2";
            this.iconButton2.Rotation = 0D;
            this.iconButton2.UseVisualStyleBackColor = true;
            this.iconButton2.Click += new System.EventHandler(this.iconButton2_Click);
            // 
            // tb_state
            // 
            this.tb_state.BackColor = System.Drawing.Color.White;
            this.bunifuTransition1.SetDecoration(this.tb_state, BunifuAnimatorNS.DecorationType.None);
            resources.ApplyResources(this.tb_state, "tb_state");
            this.tb_state.Name = "tb_state";
            // 
            // btn_in_out
            // 
            this.btn_in_out.BackColor = System.Drawing.Color.Transparent;
            this.btn_in_out.BorderRadius = 20;
            this.btn_in_out.BorderStyle = System.Drawing.Drawing2D.DashStyle.Dash;
            this.btn_in_out.ButtonMode = Guna.UI2.WinForms.Enums.ButtonMode.RadioButton;
            this.btn_in_out.Checked = true;
            this.btn_in_out.CheckedState.FillColor = System.Drawing.Color.White;
            this.btn_in_out.CheckedState.Parent = this.btn_in_out;
            this.btn_in_out.CustomImages.Parent = this.btn_in_out;
            this.bunifuTransition1.SetDecoration(this.btn_in_out, BunifuAnimatorNS.DecorationType.None);
            this.btn_in_out.FillColor = System.Drawing.Color.White;
            resources.ApplyResources(this.btn_in_out, "btn_in_out");
            this.btn_in_out.ForeColor = System.Drawing.Color.Black;
            this.btn_in_out.HoverState.Parent = this.btn_in_out;
            this.btn_in_out.Name = "btn_in_out";
            this.btn_in_out.ShadowDecoration.Parent = this.btn_in_out;
            this.btn_in_out.Click += new System.EventHandler(this.btn_in_out_Click);
            // 
            // btn_config_baud
            // 
            this.btn_config_baud.BackColor = System.Drawing.Color.Transparent;
            this.btn_config_baud.BorderRadius = 20;
            this.btn_config_baud.ButtonMode = Guna.UI2.WinForms.Enums.ButtonMode.RadioButton;
            this.btn_config_baud.CheckedState.FillColor = System.Drawing.Color.White;
            this.btn_config_baud.CheckedState.Parent = this.btn_config_baud;
            this.btn_config_baud.CustomImages.Parent = this.btn_config_baud;
            this.bunifuTransition1.SetDecoration(this.btn_config_baud, BunifuAnimatorNS.DecorationType.None);
            this.btn_config_baud.FillColor = System.Drawing.Color.White;
            resources.ApplyResources(this.btn_config_baud, "btn_config_baud");
            this.btn_config_baud.ForeColor = System.Drawing.Color.Black;
            this.btn_config_baud.HoverState.Parent = this.btn_config_baud;
            this.btn_config_baud.Name = "btn_config_baud";
            this.btn_config_baud.ShadowDecoration.Parent = this.btn_config_baud;
            this.btn_config_baud.Click += new System.EventHandler(this.btn_config_baud_Click);
            // 
            // btn_config_mega
            // 
            this.btn_config_mega.BackColor = System.Drawing.Color.Transparent;
            this.btn_config_mega.BorderRadius = 20;
            this.btn_config_mega.ButtonMode = Guna.UI2.WinForms.Enums.ButtonMode.RadioButton;
            this.btn_config_mega.CheckedState.FillColor = System.Drawing.Color.White;
            this.btn_config_mega.CheckedState.Parent = this.btn_config_mega;
            this.btn_config_mega.CustomImages.Parent = this.btn_config_mega;
            this.bunifuTransition1.SetDecoration(this.btn_config_mega, BunifuAnimatorNS.DecorationType.None);
            this.btn_config_mega.FillColor = System.Drawing.Color.White;
            resources.ApplyResources(this.btn_config_mega, "btn_config_mega");
            this.btn_config_mega.ForeColor = System.Drawing.Color.Black;
            this.btn_config_mega.HoverState.Parent = this.btn_config_mega;
            this.btn_config_mega.Name = "btn_config_mega";
            this.btn_config_mega.ShadowDecoration.Parent = this.btn_config_mega;
            this.btn_config_mega.Click += new System.EventHandler(this.btn_config_mega_Click);
            // 
            // btn_adc
            // 
            this.btn_adc.BackColor = System.Drawing.Color.Transparent;
            this.btn_adc.BorderRadius = 20;
            this.btn_adc.ButtonMode = Guna.UI2.WinForms.Enums.ButtonMode.RadioButton;
            this.btn_adc.CheckedState.FillColor = System.Drawing.Color.White;
            this.btn_adc.CheckedState.Parent = this.btn_adc;
            this.btn_adc.CustomImages.Parent = this.btn_adc;
            this.bunifuTransition1.SetDecoration(this.btn_adc, BunifuAnimatorNS.DecorationType.None);
            this.btn_adc.FillColor = System.Drawing.Color.White;
            resources.ApplyResources(this.btn_adc, "btn_adc");
            this.btn_adc.ForeColor = System.Drawing.Color.Black;
            this.btn_adc.HoverState.Parent = this.btn_adc;
            this.btn_adc.Name = "btn_adc";
            this.btn_adc.ShadowDecoration.Parent = this.btn_adc;
            this.btn_adc.Click += new System.EventHandler(this.btn_adc_Click);
            // 
            // btn_config_esp
            // 
            this.btn_config_esp.BackColor = System.Drawing.Color.Transparent;
            this.btn_config_esp.BorderRadius = 20;
            this.btn_config_esp.ButtonMode = Guna.UI2.WinForms.Enums.ButtonMode.RadioButton;
            this.btn_config_esp.CheckedState.FillColor = System.Drawing.Color.White;
            this.btn_config_esp.CheckedState.Parent = this.btn_config_esp;
            this.btn_config_esp.CustomImages.Parent = this.btn_config_esp;
            this.bunifuTransition1.SetDecoration(this.btn_config_esp, BunifuAnimatorNS.DecorationType.None);
            this.btn_config_esp.FillColor = System.Drawing.Color.White;
            resources.ApplyResources(this.btn_config_esp, "btn_config_esp");
            this.btn_config_esp.ForeColor = System.Drawing.Color.Black;
            this.btn_config_esp.HoverState.Parent = this.btn_config_esp;
            this.btn_config_esp.Name = "btn_config_esp";
            this.btn_config_esp.ShadowDecoration.Parent = this.btn_config_esp;
            this.btn_config_esp.Click += new System.EventHandler(this.btn_config_esp_Click);
            // 
            // bunifuElipse1
            // 
            this.bunifuElipse1.ElipseRadius = 30;
            this.bunifuElipse1.TargetControl = this;
            // 
            // bunifuDragControl1
            // 
            this.bunifuDragControl1.Fixed = true;
            this.bunifuDragControl1.Horizontal = true;
            this.bunifuDragControl1.TargetControl = this.pictureBox1;
            this.bunifuDragControl1.Vertical = true;
            // 
            // F_Main
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.pnl_container1);
            this.bunifuTransition1.SetDecoration(this, BunifuAnimatorNS.DecorationType.None);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "F_Main";
            this.Load += new System.EventHandler(this.F_Main_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.pnl_container1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.guna2CustomGradientPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private Guna.UI2.WinForms.Guna2Button btn_connect;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tb_port;
        private System.Windows.Forms.TextBox tb_broker;
        private System.Windows.Forms.Panel pnl_container1;
        private BunifuAnimatorNS.BunifuTransition bunifuTransition1;
        private Bunifu.Framework.UI.BunifuCheckbox chk_status_mqtt;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel pnl_container;
        private Bunifu.Framework.UI.BunifuElipse bunifuElipse1;
        private Guna.UI2.WinForms.Guna2CustomGradientPanel guna2CustomGradientPanel1;
        private System.Windows.Forms.Label tb_state;
        private Guna.UI2.WinForms.Guna2Button btn_in_out;
        private Guna.UI2.WinForms.Guna2Button btn_config_baud;
        private Guna.UI2.WinForms.Guna2Button btn_config_mega;
        private Guna.UI2.WinForms.Guna2Button btn_adc;
        private Guna.UI2.WinForms.Guna2Button btn_config_esp;
        private Bunifu.Framework.UI.BunifuDragControl bunifuDragControl1;
        private FontAwesome.Sharp.IconButton iconButton2;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}
namespace C_sharp_LOGIN
{
    partial class uC_ADC
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.sli_A4 = new Bunifu.Framework.UI.BunifuSlider();
            this.label26 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.cir_adc0 = new Guna.UI2.WinForms.Guna2CircleProgressBar();
            this.tb_adc0 = new System.Windows.Forms.TextBox();
            this.label22 = new System.Windows.Forms.Label();
            this.tb_adc1 = new System.Windows.Forms.TextBox();
            this.label23 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.tb_adc7 = new System.Windows.Forms.TextBox();
            this.tb_adc2 = new System.Windows.Forms.TextBox();
            this.tb_adc6 = new System.Windows.Forms.TextBox();
            this.tb_adc3 = new System.Windows.Forms.TextBox();
            this.label24 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.tb_adc5 = new System.Windows.Forms.TextBox();
            this.tb_adc4 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cir_adc0.SuspendLayout();
            this.SuspendLayout();
            // 
            // sli_A4
            // 
            this.sli_A4.BackColor = System.Drawing.Color.Transparent;
            this.sli_A4.BackgroudColor = System.Drawing.Color.DarkGray;
            this.sli_A4.BorderRadius = 0;
            this.sli_A4.IndicatorColor = System.Drawing.Color.SeaGreen;
            this.sli_A4.Location = new System.Drawing.Point(235, 122);
            this.sli_A4.Margin = new System.Windows.Forms.Padding(5, 5, 5, 5);
            this.sli_A4.MaximumValue = 255;
            this.sli_A4.Name = "sli_A4";
            this.sli_A4.Size = new System.Drawing.Size(159, 35);
            this.sli_A4.TabIndex = 72;
            this.sli_A4.Value = 0;
            this.sli_A4.ValueChanged += new System.EventHandler(this.sli_A4_ValueChanged);
            this.sli_A4.ValueChangeComplete += new System.EventHandler(this.sli_A4_ValueChangeComplete);
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(29, 32);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(25, 17);
            this.label26.TabIndex = 71;
            this.label26.Text = "A0";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(11, 31);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(25, 17);
            this.label18.TabIndex = 56;
            this.label18.Text = "A0";
            // 
            // cir_adc0
            // 
            this.cir_adc0.Animated = true;
            this.cir_adc0.Controls.Add(this.label26);
            this.cir_adc0.Enabled = false;
            this.cir_adc0.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.cir_adc0.FillThickness = 15;
            this.cir_adc0.Location = new System.Drawing.Point(216, 22);
            this.cir_adc0.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.cir_adc0.Maximum = 1023;
            this.cir_adc0.Name = "cir_adc0";
            this.cir_adc0.ProgressColor = System.Drawing.Color.Red;
            this.cir_adc0.ProgressColor2 = System.Drawing.Color.Red;
            this.cir_adc0.ShadowDecoration.Mode = Guna.UI2.WinForms.Enums.ShadowMode.Circle;
            this.cir_adc0.ShadowDecoration.Parent = this.cir_adc0;
            this.cir_adc0.Size = new System.Drawing.Size(85, 82);
            this.cir_adc0.TabIndex = 70;
            // 
            // tb_adc0
            // 
            this.tb_adc0.Location = new System.Drawing.Point(77, 28);
            this.tb_adc0.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc0.Name = "tb_adc0";
            this.tb_adc0.Size = new System.Drawing.Size(100, 22);
            this.tb_adc0.TabIndex = 54;
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(11, 268);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(25, 17);
            this.label22.TabIndex = 69;
            this.label22.Text = "A7";
            // 
            // tb_adc1
            // 
            this.tb_adc1.Location = new System.Drawing.Point(77, 63);
            this.tb_adc1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc1.Name = "tb_adc1";
            this.tb_adc1.Size = new System.Drawing.Size(100, 22);
            this.tb_adc1.TabIndex = 55;
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(11, 235);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(25, 17);
            this.label23.TabIndex = 68;
            this.label23.Text = "A6";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(11, 65);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(25, 17);
            this.label19.TabIndex = 57;
            this.label19.Text = "A1";
            // 
            // tb_adc7
            // 
            this.tb_adc7.Location = new System.Drawing.Point(77, 267);
            this.tb_adc7.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc7.Name = "tb_adc7";
            this.tb_adc7.Size = new System.Drawing.Size(100, 22);
            this.tb_adc7.TabIndex = 67;
            // 
            // tb_adc2
            // 
            this.tb_adc2.Location = new System.Drawing.Point(77, 97);
            this.tb_adc2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc2.Name = "tb_adc2";
            this.tb_adc2.Size = new System.Drawing.Size(100, 22);
            this.tb_adc2.TabIndex = 58;
            // 
            // tb_adc6
            // 
            this.tb_adc6.Location = new System.Drawing.Point(77, 233);
            this.tb_adc6.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc6.Name = "tb_adc6";
            this.tb_adc6.Size = new System.Drawing.Size(100, 22);
            this.tb_adc6.TabIndex = 66;
            // 
            // tb_adc3
            // 
            this.tb_adc3.Location = new System.Drawing.Point(77, 130);
            this.tb_adc3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc3.Name = "tb_adc3";
            this.tb_adc3.Size = new System.Drawing.Size(100, 22);
            this.tb_adc3.TabIndex = 59;
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(11, 201);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(25, 17);
            this.label24.TabIndex = 65;
            this.label24.Text = "A5";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(11, 98);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(25, 17);
            this.label21.TabIndex = 60;
            this.label21.Text = "A2";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(11, 167);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(25, 17);
            this.label25.TabIndex = 64;
            this.label25.Text = "A4";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(11, 133);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(25, 17);
            this.label20.TabIndex = 61;
            this.label20.Text = "A3";
            // 
            // tb_adc5
            // 
            this.tb_adc5.Location = new System.Drawing.Point(77, 199);
            this.tb_adc5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc5.Name = "tb_adc5";
            this.tb_adc5.Size = new System.Drawing.Size(100, 22);
            this.tb_adc5.TabIndex = 63;
            // 
            // tb_adc4
            // 
            this.tb_adc4.Enabled = false;
            this.tb_adc4.Location = new System.Drawing.Point(77, 165);
            this.tb_adc4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tb_adc4.Name = "tb_adc4";
            this.tb_adc4.ReadOnly = true;
            this.tb_adc4.Size = new System.Drawing.Size(100, 22);
            this.tb_adc4.TabIndex = 62;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(189, 134);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 17);
            this.label1.TabIndex = 73;
            this.label1.Text = "A4";
            // 
            // uC_ADC
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.sli_A4);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.cir_adc0);
            this.Controls.Add(this.tb_adc0);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.tb_adc1);
            this.Controls.Add(this.label23);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.tb_adc7);
            this.Controls.Add(this.tb_adc2);
            this.Controls.Add(this.tb_adc6);
            this.Controls.Add(this.tb_adc3);
            this.Controls.Add(this.label24);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.label25);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.tb_adc5);
            this.Controls.Add(this.tb_adc4);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "uC_ADC";
            this.Size = new System.Drawing.Size(672, 347);
            this.Load += new System.EventHandler(this.uC_ADC_Load);
            this.cir_adc0.ResumeLayout(false);
            this.cir_adc0.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Bunifu.Framework.UI.BunifuSlider sli_A4;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label18;
        private Guna.UI2.WinForms.Guna2CircleProgressBar cir_adc0;
        private System.Windows.Forms.TextBox tb_adc0;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.TextBox tb_adc1;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox tb_adc7;
        private System.Windows.Forms.TextBox tb_adc2;
        private System.Windows.Forms.TextBox tb_adc6;
        private System.Windows.Forms.TextBox tb_adc3;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox tb_adc5;
        private System.Windows.Forms.TextBox tb_adc4;
        private System.Windows.Forms.Label label1;
    }
}

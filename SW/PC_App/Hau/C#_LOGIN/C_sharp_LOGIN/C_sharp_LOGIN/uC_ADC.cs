using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace C_sharp_LOGIN
{
    public partial class uC_ADC : UserControl
    {
        public uC_ADC()
        {
            InitializeComponent();
        }

        //private void bunifuSlider1_ValueChanged(object sender, EventArgs e)
        //{
        //    byte cb0 = Convert.ToByte(sw_out0.Checked);
        //    byte cb1 = Convert.ToByte(sw_out1.Checked);
        //    byte cb2 = Convert.ToByte(sw_out2.Checked);
        //    byte cb3 = Convert.ToByte(sw_out3.Checked);
        //    byte cb4 = Convert.ToByte(sw_out4.Checked);
        //    byte cb5 = Convert.ToByte(sw_out5.Checked);
        //    byte cb6 = Convert.ToByte(sw_out6.Checked);
        //    byte cb7 = Convert.ToByte(sw_out7.Checked);


        //    byte temp = 0x00;
        //    temp |= cb0;
        //    temp |= Convert.ToByte(cb1 << 1);
        //    temp |= Convert.ToByte(cb2 << 2);
        //    temp |= Convert.ToByte(cb3 << 3);
        //    temp |= Convert.ToByte(cb4 << 4);
        //    temp |= Convert.ToByte(cb5 << 5);
        //    temp |= Convert.ToByte(cb6 << 6);
        //    temp |= Convert.ToByte(cb7 << 7);



        //    DATA_SEND_NODE dataSend = new DATA_SEND_NODE();
        //    dataSend.OUT_P = temp;

        //    dataSend.A4 = sli_A4.Value;

        //    string json = JsonConvert.SerializeObject(dataSend, Formatting.Indented);
        //    mqttClient.Publish("/MASTER/GET/SENSOR", Encoding.UTF8.GetBytes(json), 0, true);
        //}

        public void disable()
        {
            tb_adc0.Enabled = false;
            tb_adc1.Enabled = false;
            tb_adc2.Enabled = false;
            tb_adc3.Enabled = false;
            tb_adc4.Enabled = false;
            tb_adc5.Enabled = false;
            tb_adc6.Enabled = false;
            tb_adc7.Enabled = false;
            cir_adc0.Animated = false;

            sli_A4.Enabled = false;
        }

        public void enable()
        {
            tb_adc0.Enabled = true;
            tb_adc1.Enabled = true;
            tb_adc2.Enabled = true;
            tb_adc3.Enabled = true;
            tb_adc4.Enabled = true;
            tb_adc5.Enabled = true;
            tb_adc6.Enabled = true;
            tb_adc7.Enabled = true;
            cir_adc0.Animated = true;

            sli_A4.Enabled = true;
        }

        public string ADC0
        {
            get { return tb_adc0.Text; }
            set { tb_adc0.Text = value;}
        }

        public string ADC1
        {
            get { return tb_adc1.Text; }
            set { tb_adc1.Text = value; }
        }
        public string ADC2
        {
            get { return tb_adc2.Text; }
            set { tb_adc2.Text = value; }
        }
        public string ADC3
        {
            get { return tb_adc3.Text; }
            set { tb_adc3.Text = value; }
        }
        public string ADC4
        {
            get { return tb_adc4.Text; }
            set { tb_adc4.Text = value; }
        }
        public string ADC5
        {
            get { return tb_adc5.Text; }
            set { tb_adc5.Text = value; }
        }
        public string ADC6
        {
            get { return tb_adc6.Text; }
            set { tb_adc6.Text = value; }
        }

        public string ADC7
        {
            get { return tb_adc7.Text; }
            set { tb_adc7.Text = value; }
        }



        public int cir_ADC0
        {
            get { return cir_adc0.Value; }
            set { cir_adc0.Value = value; }
        }
        public int sli_a4
        {
            get { return sli_A4.Value; }
            set { sli_A4.Value = value; }
        }

        private void sli_A4_ValueChanged(object sender, EventArgs e)
        {
            tb_adc4.Text = sli_A4.Value.ToString();
        }

        private void sli_A4_ValueChangeComplete(object sender, EventArgs e)
        {
            DATA_GLOBAL.IN_OUT_uC.CheckedChanged(sender, e);
        }

        private void uC_ADC_Load(object sender, EventArgs e)
        {
            this.BackColor = DATA_GLOBAL.de_color;
        }
    }
}

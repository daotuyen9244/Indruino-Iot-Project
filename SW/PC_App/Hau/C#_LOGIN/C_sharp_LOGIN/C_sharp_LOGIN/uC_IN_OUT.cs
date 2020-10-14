using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;


namespace C_sharp_LOGIN
{
    public partial class uC_IN_OUT : UserControl
    {
        public uC_IN_OUT()
        {
            InitializeComponent();
        }
        private void setSwitch(int pos, bool value)
        {
            switch (pos)
            {
                case 0:
                    {
                        sw_out0.Checked = value;
                        break;
                    }
                case 1:
                    {
                        sw_out1.Checked = value;
                        break;
                    }
                case 2:
                    {
                        sw_out2.Checked = value;
                        break;
                    }
                case 3:
                    {
                        sw_out3.Checked = value;
                        break;
                    }
                case 4:
                    {
                        sw_out4.Checked = value;
                        break;
                    }
                case 5:
                    {
                        sw_out5.Checked = value;
                        break;
                    }
                case 6:
                    {
                        sw_out6.Checked = value;
                        break;
                    }
                case 7:
                    {
                        sw_out7.Checked = value;

                        break;
                    }
                default:
                    break;
            }
        }
        public void output_lamp(byte value)
        {
            for (byte i = 0; i < 8; i++)
            {
                setLamp(i, bitRead(value, i));
            }
        }
        public void output_switch(byte value)
        {
            for (byte i = 0; i < 8; i++)
            {
                setSwitch(i, bitRead(value, i));
            }

        }



        private void setLamp(int pos, bool value)
        {
            switch (pos)
            {
                case 0:
                    {
                        if (value)
                        {
                            ptb_IN0.Image = Properties.Resources.lamp_on;
                        }
                        else
                        {
                            ptb_IN0.Image = Properties.Resources.lamp_off;
                        }
                        break;
                    }
                case 1:
                    {
                        if (value)
                        {
                            ptb_IN1.Image = Properties.Resources.lamp_on;
                        }
                        else
                        {
                            ptb_IN1.Image = Properties.Resources.lamp_off;
                        }
                        break;
                    }
                case 2:
                    {
                        if (value)
                        {
                            ptb_IN2.Image = Properties.Resources.lamp_on;
                        }
                        else
                        {
                            ptb_IN2.Image = Properties.Resources.lamp_off;
                        }
                        break;
                    }
                case 3:
                    if (value)
                    {
                        ptb_IN3.Image = Properties.Resources.lamp_on;
                    }
                    else
                    {
                        ptb_IN3.Image = Properties.Resources.lamp_off;
                    }
                    break;
                case 4:
                    if (value)
                    {
                        ptb_IN4.Image = Properties.Resources.lamp_on;
                    }
                    else
                    {
                        ptb_IN4.Image = Properties.Resources.lamp_off;
                    }
                    break;
                case 5:
                    if (value)
                    {
                        ptb_IN5.Image = Properties.Resources.lamp_on;
                    }
                    else
                    {
                        ptb_IN5.Image = Properties.Resources.lamp_off;
                    }
                    break;
                case 6:
                    if (value)
                    {
                        ptb_IN6.Image = Properties.Resources.lamp_on;
                    }
                    else
                    {
                        ptb_IN6.Image = Properties.Resources.lamp_off;
                    }
                    break;
                case 7:
                    if (value)
                    {
                        ptb_IN7.Image = Properties.Resources.lamp_on;
                    }
                    else
                    {
                        ptb_IN7.Image = Properties.Resources.lamp_off;
                    }
                    break;
                default:
                    break;
            }
        }


        public void CheckedChanged(object sender, EventArgs e) //value change send packet
        {
            byte cb0 = Convert.ToByte(sw_out0.Checked);
            byte cb1 = Convert.ToByte(sw_out1.Checked);
            byte cb2 = Convert.ToByte(sw_out2.Checked);
            byte cb3 = Convert.ToByte(sw_out3.Checked);
            byte cb4 = Convert.ToByte(sw_out4.Checked);
            byte cb5 = Convert.ToByte(sw_out5.Checked);
            byte cb6 = Convert.ToByte(sw_out6.Checked);
            byte cb7 = Convert.ToByte(sw_out7.Checked);


            byte temp = 0x00;
            temp |= cb0;
            temp |= Convert.ToByte(cb1 << 1);
            temp |= Convert.ToByte(cb2 << 2);
            temp |= Convert.ToByte(cb3 << 3);
            temp |= Convert.ToByte(cb4 << 4);
            temp |= Convert.ToByte(cb5 << 5);
            temp |= Convert.ToByte(cb6 << 6);
            temp |= Convert.ToByte(cb7 << 7);


            DATA_SEND_NODE dataSend = new DATA_SEND_NODE();
            dataSend.A4 = DATA_GLOBAL.ADC_uC.sli_a4;
            dataSend.OUT_P = temp;
            string json = JsonConvert.SerializeObject(dataSend, Formatting.Indented);
            DATA_GLOBAL.mqttClient.Publish("/MASTER/GET/SENSOR", Encoding.UTF8.GetBytes(json), 0, true);
        }

        static void bitWrite(ref byte value, ref int pos)
        {
            value |= (byte)(1 << pos);
        }
        private bool bitRead(byte value, int pos)
        {
            byte tmp = (byte)(1 << pos);
            tmp = (byte)(tmp & value);
            if (tmp != 0)
            {
                return true;
            }
            return false;
        }
        public void disable()
        {
            sw_out0.Enabled = false;
            sw_out1.Enabled = false;
            sw_out2.Enabled = false;
            sw_out3.Enabled = false;
            sw_out4.Enabled = false;
            sw_out5.Enabled = false;
            sw_out6.Enabled = false;
            sw_out7.Enabled = false;
        }
        public void enable()
        {
            sw_out0.Enabled = true;
            sw_out1.Enabled = true;
            sw_out2.Enabled = true;
            sw_out3.Enabled = true;
            sw_out4.Enabled = true;
            sw_out5.Enabled = true;
            sw_out6.Enabled = true;
            sw_out7.Enabled = true;
        }

        private void uC_IN_OUT_Load(object sender, EventArgs e)
        {
            this.BackColor = DATA_GLOBAL.de_color;
        }
    }
}

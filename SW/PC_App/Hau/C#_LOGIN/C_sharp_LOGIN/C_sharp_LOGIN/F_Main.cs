using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//
using Guna.UI2.WinForms;
using uPLibrary.Networking.M2Mqtt;
using Newtonsoft.Json;
using System.Threading;


namespace C_sharp_LOGIN
{
    public partial class F_Main : Form
    {
        
    
        public F_Main()
        {
            InitializeComponent();
        }
        //private void F_Main_FormClosed(object sender, FormClosedEventArgs e)
        //{
            
        //}

        private void F_Main_Load(object sender, EventArgs e)
        {
            DATA_GLOBAL.ADC_uC = new uC_ADC();
            DATA_GLOBAL.IN_OUT_uC = new uC_IN_OUT();
            DATA_GLOBAL.MEGA_Config_uC = new uC_MEGA_Config();
            DATA_GLOBAL.ESP_Config_uC = new uC_ESP_Config();


            guna2CustomGradientPanel1.FillColor = System.Drawing.Color.FromArgb(23, 74, 181);
            guna2CustomGradientPanel1.FillColor2 = System.Drawing.Color.FromArgb(23, 74, 181);
            guna2CustomGradientPanel1.FillColor3= System.Drawing.Color.FromArgb(23, 74, 181);
            guna2CustomGradientPanel1.FillColor4 = System.Drawing.Color.FromArgb(23, 74, 181);


            btn_in_out.FillColor = System.Drawing.Color.FromArgb(23, 74, 181);
            btn_adc.FillColor = System.Drawing.Color.FromArgb(23, 74, 181);
            btn_config_esp.FillColor = System.Drawing.Color.FromArgb(23, 74, 181);
            btn_config_mega.FillColor = System.Drawing.Color.FromArgb(23, 74, 181);
            btn_config_baud.FillColor = System.Drawing.Color.FromArgb(23, 74, 181);


            tb_state.Size = new Size(tb_state.Size.Width, btn_in_out.Size.Height);
           
            //need a function
            //rev//pnl_container.Controls.Clear();
            //rev//ADC_uC.BringToFront();
            //rev//ADC_uC.Dock = DockStyle.Fill;
            //rev//pnl_container.Controls.Add(ADC_uC);
            change_UControl(DATA_GLOBAL.IN_OUT_uC);
            //need a function
            disable();
        }
        private void change_UControl(Control value)
        {
            pnl_container.Controls.Clear();
            value.BringToFront();
            value.Dock = DockStyle.Fill;
            pnl_container.Controls.Add(value);
        }
        private void MqttClient_MqttMsgPublishReceived(object sender, uPLibrary.Networking.M2Mqtt.Messages.MqttMsgPublishEventArgs e)
        {
            ReceiveAction = Receive;
            string message = Encoding.UTF8.GetString(e.Message);
            string topic = e.Topic;
            try
            {
                this.BeginInvoke(ReceiveAction, topic, message);
            }
            catch (Exception)
            {

                throw;
            }


            //    throw new NotImplementedException();
        }

        Action<string, string> ReceiveAction;
        void Receive(string topic, string message)
        {


            if (topic == "/MASTER/POST/SENSOR")
            {
                DATA_RECIVE_NODE dataFromNode = JsonConvert.DeserializeObject<DATA_RECIVE_NODE>(message);
                DATA_GLOBAL.ADC_uC.ADC0 = dataFromNode.A0.ToString();
                DATA_GLOBAL.ADC_uC.ADC1 = dataFromNode.A1.ToString();
                DATA_GLOBAL.ADC_uC.ADC2 = dataFromNode.A2.ToString();
                DATA_GLOBAL.ADC_uC.ADC3 = dataFromNode.A3.ToString();
                DATA_GLOBAL.ADC_uC.ADC4 = dataFromNode.A4.ToString();
                DATA_GLOBAL.ADC_uC.ADC5 = dataFromNode.A5.ToString();
                DATA_GLOBAL.ADC_uC.ADC6 = dataFromNode.A6.ToString();
                DATA_GLOBAL.ADC_uC.ADC7 = dataFromNode.A7.ToString();
                DATA_GLOBAL.ADC_uC.cir_ADC0 = dataFromNode.A0;

                DATA_GLOBAL.IN_OUT_uC.output_lamp(dataFromNode.IN_P);
            }
            if (topic == "/MASTER/GET/SENSOR")
            {
                DATA_GLOBAL.mqttClient.Unsubscribe(new string[] { "/MASTER/GET/SENSOR" });
                DATA_SEND_NODE dataFromPc = JsonConvert.DeserializeObject<DATA_SEND_NODE>(message);
                DATA_GLOBAL.IN_OUT_uC.output_switch(dataFromPc.OUT_P);
                DATA_GLOBAL.ADC_uC.sli_a4 = dataFromPc.A4;
                
            }

            //  DATA_RECIVE_NODE dataFromNode = JsonConvert.DeserializeObject<DATA_RECIVE_NODE>(message);
            //neu o topic va function code == bla bla

            //  if()
            //MessageBox.Show(message);

        }
        private void disable()
        {
            DATA_GLOBAL.IN_OUT_uC.disable();

            DATA_GLOBAL.ADC_uC.disable();

            tb_broker.Enabled = true;
            tb_port.Enabled = true;
            chk_status_mqtt.Checked = false;

        }
        private void enable()
        {
            DATA_GLOBAL.IN_OUT_uC.enable();
            DATA_GLOBAL.ADC_uC.enable();

            btn_connect.Text = "OK";
            tb_broker.Enabled = false;
            tb_port.Enabled = false;
            chk_status_mqtt.Checked = true;

        }


        private void btn_connect_Click(object sender, EventArgs e)
        {
            try
            {
                if (!chk_status_mqtt.Checked)
                {
                    
                    DATA_GLOBAL.mqttClient = new MqttClient(tb_broker.Text, int.Parse(tb_port.Text), false, MqttSslProtocols.None, null, null);
                    DATA_GLOBAL.mqttClient.ProtocolVersion = MqttProtocolVersion.Version_3_1;
                    byte code = DATA_GLOBAL.mqttClient.Connect(Guid.NewGuid().ToString());
                    if (code == 0)
                    {
                        //MessageBox.Show(this, "connected", "thong bao", MessageBoxButtons.OK, MessageBoxIcon.Question);
                        DATA_GLOBAL.mqttClient.MqttMsgPublishReceived += MqttClient_MqttMsgPublishReceived;
                        DATA_GLOBAL.mqttClient.Subscribe(new string[] { "/MASTER/POST/SENSOR", "/MASTER/GET/SENSOR" }, new byte[] { 0, 0 });
                        enable();
                    }
                    else
                    {
                        MessageBox.Show(this, "Connect Fail", "Message", MessageBoxButtons.OK, MessageBoxIcon.Question);
                        disable();
                    }
                }
            }
            catch (Exception)
            {
                MessageBox.Show(this, "Wrong Format", "Message", MessageBoxButtons.OK, MessageBoxIcon.Question);
                disable();
            }
        }

        private void btn_adc_Click(object sender, EventArgs e)
        {
            change_UControl(DATA_GLOBAL.ADC_uC);
            move_tb_state(sender);
        }

        private void btn_in_out_Click(object sender, EventArgs e)
        {
            change_UControl(DATA_GLOBAL.IN_OUT_uC);
            move_tb_state(sender);
        }

        private void move_tb_state(object sender) //move tb_state same Y location with sender
        {
            Guna2Button tmp = (Guna2Button)sender;
            tb_state.Location = new Point(tb_state.Location.X, tmp.Location.Y);


        }

        private void btn_config_esp_Click(object sender, EventArgs e)
        {
            change_UControl(DATA_GLOBAL.ESP_Config_uC);
            move_tb_state(sender);
        }

        private void btn_config_mega_Click(object sender, EventArgs e)
        {
            change_UControl(DATA_GLOBAL.MEGA_Config_uC);
            move_tb_state(sender);
        }

        private void btn_config_baud_Click(object sender, EventArgs e)
        {   
            
            move_tb_state(sender);
        }

        private void iconButton2_Click(object sender, EventArgs e)
        {
            System.Environment.Exit(1);
        }
        //void at post/sensor send //
        //void at get/sensor receive
    }


    public class DATA_RECIVE_NODE
    {
        public string code { get; set; }
        public byte mNumSlv { get; set; }
        public byte idSlv { get; set; }
        public byte codeFunc { get; set; }
        public int A0 { get; set; }
        public int A1 { get; set; }
        public int A2 { get; set; }
        public int A3 { get; set; }
        public int A4 { get; set; }
        public int A5 { get; set; }
        public int A6 { get; set; }
        public int A7 { get; set; }
        public byte IN_P { get; set; }
    }

    public class DATA_SEND_NODE
    {
        public string code { get; set; }
        public byte mNumSlv { get; set; } 
        public byte idSlv { get; set; }
        public byte codeFunc { get; set;}
        public int A0 { get; set; }
        public int A1 { get; set; }
        public int A2 { get; set; }
        public int A3 { get; set; }
        public int A4 { get; set; }
        public int A5 { get; set; }
        public int A6 { get; set; }
        public int A7 { get; set; }
        public byte OUT_P { get; set; }
        public void setNull()
        {
            

        }
    }
    public static class DATA_GLOBAL
    {
         public static MqttClient mqttClient;
         public static uC_ADC ADC_uC;
         public static uC_IN_OUT IN_OUT_uC;
         public static uC_ESP_Config ESP_Config_uC;
         public static uC_MEGA_Config MEGA_Config_uC;
         public static Color de_color { get; set; } = System.Drawing.Color.FromArgb(255,255,255);
    }

}




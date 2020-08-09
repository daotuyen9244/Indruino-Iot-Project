using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;



namespace C_sharp_LOGIN
{   
    public partial class F_login : Form
    {
        public string username = "indruino";
        public string password = "indruino";
        public F_login()
        {
            InitializeComponent();
            
        }

        private void btn_exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btn_login_Click(object sender, EventArgs e)
        {
            login_event();
        }

        private void login_event()
        {
            if (check_login())
            {
                true_login();
            }
            else
            {
                false_login();
            }
        }
        private bool check_login()
        {
            if((this.txt_PassWord.Text == password) &&(this.txt_UserName.Text == username))
            {
                return true;
            }
            return false;
        }
        private void true_login()
        {
            F_Main frm = new F_Main();
            this.Hide();
            frm.Show();
        }
        private void false_login()
        {
            this.lb_infor.Visible = true;
            tmr_login_flase.Start();
        }

        private void tmr_login_flase_Tick(object sender, EventArgs e)
        {
            this.lb_infor.Visible = false;
        }

        private void txt_PassWord_OnValueChanged(object sender, EventArgs e)
        {
            if(this.txt_PassWord.Text == null)
            {
                this.txt_PassWord.isPassword = false;
            }
            else
            {
                this.txt_PassWord.isPassword = true;
            }
        }

        private void txt_PassWord_KeyPress(object sender, KeyPressEventArgs e)
        {
            if(e.KeyChar == 13)
            {
                login_event();
            }
        }

        private void txt_UserName_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
            {
                login_event();
            }
        }
    }
}

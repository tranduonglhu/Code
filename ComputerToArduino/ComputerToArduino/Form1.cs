using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace ComputerToArduino
{
    public partial class Form1 : Form

    {
        bool isConnected = false;
        String[] ports;
        SerialPort port;

        public Form1()
        {
            InitializeComponent();
            disableControls();
            getAvailableComPorts();

            foreach (string port in ports)
            {
                comboBox1.Items.Add(port);
                Console.WriteLine(port);
                if (ports[0] != null)
                {
                    comboBox1.SelectedItem = ports[0];
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!isConnected)
            {
                connectToArduino();
            } else
            {
                disconnectFromArduino();
            }
        }

        void getAvailableComPorts()
        {
            ports = SerialPort.GetPortNames();
        }

        private void connectToArduino()
        {
            isConnected = true;
            string selectedPort = comboBox1.GetItemText(comboBox1.SelectedItem);
            port = new SerialPort(selectedPort, 9600, Parity.None, 8, StopBits.One);
            port.Open();
            button1.Text = "Disconnect";
            enableControls();
        }

        private void Led1CheckboxClicked(object sender, EventArgs e)

        {
            if(isConnected)
            {
                if(checkBox1.Checked)
                {
                    port.Write("led 1\n");
                }
                else
                {
                    port.Write("led 0\n");
                }
            }
        }

  


        private void disconnectFromArduino()
        {
            isConnected = false;
            port.Write("reset\n");
            port.Close();
            button1.Text = "Connect";
            disableControls();
            resetDefaults();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (isConnected)
            {
                 port.Write("TEXT " + textBox1.Text + "\n");
            }
        }

        private void enableControls()
        {
            checkBox1.Enabled = true;
            checkBox2.Enabled = true;
            button2.Enabled = true;
            textBox1.Enabled = true;
            groupBox1.Enabled = true;
            groupBox3.Enabled = true;

        }

        private void disableControls()
        {
            checkBox1.Enabled = false;
            checkBox2.Enabled = true;
            button2.Enabled = false;
            textBox1.Enabled = false;
            groupBox1.Enabled = false;
            groupBox3.Enabled = false;
        }

        private void resetDefaults()
        {
            checkBox1.Checked = false;
            checkBox2.Checked = false;
            textBox1.Text = "";
            
        }

        private void groupBox3_Enter(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Button3_Click(object sender, EventArgs e)
        {
            port.Write("reset\n");
        }

        private void TextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void CheckBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (isConnected)
            {
                if (checkBox2.Checked)
                {
                    port.Write("ledLCD 1\n");
               
                }
                else
                {
                    port.Write("ledLCD 0\n");
                  
                }
            }
        }

        private void GroupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void PictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}

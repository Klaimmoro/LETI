using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;

namespace CardScanner
{
    public partial class Form1 : Form
    {
        private SqlConnection con;
        public bool stopwhile = false;
        public string BarCode = "";
        int x = 0; int y = 0;
        bool connection = false;
        public Form1()
        {
            InitializeComponent();

        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }




        private void connectionSQLWindows()
        {
            string connstring = "Data Source = KLAIMMOR;Initial Catalog = CardScan;Integrated Security = true";
            con = new SqlConnection(connstring);
            
        }

        private void connectionSQLUser()
        {

            string connstring = "Data Source = KLAIMMOR;Initial Catalog = CardScan;Persist Security Info = true;User ID=" + textBox1.Text + ";Password=" + textBox2.Text + ";";
            con = new SqlConnection(connstring);

            try
            {
                con.Open();
                label5.Visible = false;
                connection = true;
            }
            catch
            {
                label5.Text = "Ошибка соединения с базой данных, проверьте правильность пароля и логина!";
                connection = false;
            }
            //Application.DoEvents();
            con.Close();
        }

        private void BarCodeScan(object sender, KeyEventArgs e)
        {
            if (connection)
            {
                if (con != null)
                {
                    if ('A' - 1 < (char)e.KeyCode && (char)e.KeyCode < 'Z')
                    {
                        BarCode += (char)e.KeyCode;
                    }
                    else if ('0' - 1 < (char)e.KeyCode && (char)e.KeyCode < '9' + 1)
                    {
                        BarCode += (char)e.KeyCode;
                    }
                    Thread.Sleep(10);
                    if (BarCode.Length == 2)
                    {
                        cardScan();
                    }
                }
            }
        }


        private void cardScan()
        { 
            string card = "";
            switch (BarCode[0])
            {
                case 'S':
                    card += "Spades";
                    break;
                case 'H':
                    card += "Hearts";
                    break;
                case 'D':
                    card += "Diamonds";
                    break;
                case 'C':
                    card += "Clubs";
                    break;
                default:
                    break;
            }
            card += " ";
            switch (BarCode[1])
            {
                case 'A':
                    card += "Ace";
                    break;
                case 'K':
                    card += "King";
                    break;
                case 'Q':
                    card += "Queen";
                    break;
                case 'J':
                    card += "Jack";
                    break;
                default:
                    card += BarCode[1];
                    break;
            }
            PictureBox pictureBox = new PictureBox();
            pictureBox.Image = Image.FromFile("C:\\Users\\klaim\\Downloads\\" + BarCode[0] + BarCode[1] + ".png");
            pictureBox.Location = new Point(x, y);
            pictureBox.SizeMode = PictureBoxSizeMode.AutoSize;
            x += 100;
            if (x + 100 > 720)
            {
                x = 0;
                y += 150;

            }
            panel1.Controls.Add(pictureBox);
            mainFunc(card);
        }


        private void mainFunc(string card)
        {
            bool openCon = false;
            if (stopwhile == false)
            {
                if (openCon == false)
                {
                    con.Open();
                    openCon = true;
                }
                if (BarCode.Length == 2)
                {
                    panel1.Show();
                    label2.Text = card;
                    string query = "DECLARE @currentTime TIME(7);\r\n    " +
                    "SET @currentTime = CONVERT(TIME(7), GETDATE());\r\n" +
                    "EXECUTE InsertCard 1," + card.Substring(0, card.IndexOf(" ")) + "," + card.Substring(card.IndexOf(" ")) + ", 1, @currentTime ";
                    SqlCommand cmd = new SqlCommand(query, con);
                    SqlDataReader reader = cmd.ExecuteReader();
                    BarCode = "";
                    card = "";

                }
                con.Close();
                openCon = false;
            }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            connectionSQLUser();
            //connectionSQLWindows();
            if (connection)
            {
                label1.Text = "Программа готова для считывания карт";
                button1.Visible = false;
                button2.Visible = true;
                button3.Visible = true;
                panel1.Visible = true;
                textBox1.Visible = false;
                textBox2.Visible = false;
                label3.Visible = false;
                label4.Visible = false;
            }
        }


        private void button2_Click(object sender, EventArgs e)
        {
            stopwhile = true;
            Application.Exit();
        }


        private void label2_Click(object sender, EventArgs e)
        {

        }


        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }


        private void button3_Click(object sender, EventArgs e)
        {
            panel1.Controls.Clear();
            x = 0;
            y = 0;
            stopwhile = false;
            
        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {

        }
    }



}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Drawing;

namespace VisualRE
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("..\\..\\..\\Debug\\core.dll", EntryPoint = "Sum", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Sum(int a, int b);

        [DllImport("..\\..\\..\\Debug\\core.dll", EntryPoint = "generate_dot", CallingConvention = CallingConvention.Cdecl)]
        private static extern void generate_dot(string str);

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            generate_dot(textBox.GetLineText(0));
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Form form = new Form();
            form.Show();

            PictureBox pb = new PictureBox();
            pb.ImageLocation = "nfa.dt.jpg";
            pb.SizeMode = PictureBoxSizeMode.Normal;

            System.Drawing.Image img = System.Drawing.Image.FromFile("nfa.dt.jpg");
            System.Drawing.Size size = new System.Drawing.Size(img.Size.Width + 20, img.Height + 40);
            form.Size = size;
            pb.Size = img.Size;


            form.Controls.Add(pb);
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            Form form = new Form();
            form.Show();

            PictureBox pb = new PictureBox();
            pb.ImageLocation = "dfa.dt.jpg";
            pb.SizeMode = PictureBoxSizeMode.Zoom;

            System.Drawing.Image img = System.Drawing.Image.FromFile("dfa.dt.jpg");
            System.Drawing.Size size = new System.Drawing.Size(img.Size.Width + 20, img.Height + 40);
            form.Size = size;
            pb.Size = img.Size;

            form.Controls.Add(pb);
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            Form form = new Form();
            form.Show();

            PictureBox pb = new PictureBox();
            pb.ImageLocation = "miniDfa.dt.jpg";
            pb.SizeMode = PictureBoxSizeMode.Zoom;

            System.Drawing.Image img = System.Drawing.Image.FromFile("miniDfa.dt.jpg");
            System.Drawing.Size size = new System.Drawing.Size(img.Size.Width + 20, img.Height + 40);
            form.Size = size;
            pb.Size = img.Size;

            form.Controls.Add(pb);
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {

        }
    }
}

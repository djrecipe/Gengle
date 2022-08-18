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
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GengleDemoApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private System.Windows.Threading.DispatcherTimer updateTimer = new System.Windows.Threading.DispatcherTimer();
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            HwndHost host = new GengleHwndHost();
            hwndPlaceholder.Child = host;
            //
            updateTimer.Interval = new TimeSpan(160000);
            updateTimer.Tick += new EventHandler(updateTimer_Tick);
            updateTimer.Start();
        }
        private void updateTimer_Tick(object sender, EventArgs e)
        {
            if (null != hwndPlaceholder &&
                null != hwndPlaceholder.Child)
            {
                hwndPlaceholder.Child.InvalidateVisual();
            }
        }
    }
}

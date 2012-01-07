using System;
using System.Diagnostics;
using System.Threading;
using System.Windows;
using System.Windows.Controls.Primitives;
using System.Windows.Controls;

namespace TestClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        /// how fast should the values be updated
        private int SAMPLE_TIME = 20;

        /// update thread for COM calls
        private Thread mThread;

        /// call back definition
        public delegate void callbackType(string s);

        /// lisa COM object
        private Lisa50Lib.ILisaCOM mLisaCOM;

        /// Timer for updating the status bar
        private Timer mTimer;

        /// Lisa COM Controller
        private Lisa50Lib.ILisaCOMController mLisaController;
        private static bool mConnected = false;


        /// <summary>
        /// Create main window and initialize the combobox
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();

            cbTestCOM.Items.Add("getCOPForce");
            cbTestCOM.Items.Add("getCOPPosition");
            cbTestCOM.Items.Add("getLinkPosition");
            cbTestCOM.Items.Add("getJointCoordinates");
            cbTestCOM.Items.Add("getLinkMass");
            cbTestCOM.Items.Add("getLinkPosition");
            cbTestCOM.Items.Add("getLinkPositionByName");

            cbTestController.Items.Add("getParameters");
            cbTestController.Items.Add("getPosition");
            cbTestController.Items.Add("getTorque");
            cbTestController.Items.Add("getVelocity");
            cbTestController.Items.Add("getSetpoint");
            //cbTestController.Items.Add("setParameter");
            //cbTestController.Items.Add("setParameters");
            //cbTestController.Items.Add("setSetpoint");

            cbTestCOM.IsEnabled = false;
            cbTestController.IsEnabled = false;

            tbPause.IsEnabled = false;
        }

        /// <summary>
        /// Create thread that will call the selected function
        /// </summary>
        private void WorkThreadCOM(object o)
        {
            try
            {
                ThreadParamsTestCOM t = (ThreadParamsTestCOM)o;
                new TestLisaCOM(new callbackType(outputCallback), mLisaCOM, t.Method, SAMPLE_TIME, t.Num, t.Name);
            }
            catch (ThreadAbortException)
            {
                // thread was aborted by us
            }
            catch (System.Exception ex)
            {
                // undefined exception
                string msg = ex.Message;
            }
            finally
            {

            }
        }

        /// <summary>
        /// Create thread that test COMController
        /// </summary>
        private void WorkThreadCOMController(object o)
        {
            try
            {
                ThreadParamsTestCOM t = (ThreadParamsTestCOM)o;
                new TestLisaCOMController(new callbackType(outputCallbackCtrl), mLisaController, t.Method, SAMPLE_TIME, t.Num, t.Name);
            }
            catch (ThreadAbortException)
            {
                // thread was aborted by us
            }
            catch (System.Exception ex)
            {
                // undefined exception
                string msg = ex.Message;
            }
            finally
            {

            }
        }

        /// <summary>
        /// display return values on the GUI screen
        /// </summary>
        /// <param name="s"></param>
        private void outputCallback(string s)
        {
            Application.Current.Dispatcher.BeginInvoke((ThreadStart)delegate()
            {
                txtLog.Text += s;
                txtLog.ScrollToEnd();
            }, null);
        }

        /// <summary>
        /// display return values on the GUI screen
        /// </summary>
        /// <param name="s"></param>
        private void outputCallbackCtrl(string s)
        {
            Application.Current.Dispatcher.BeginInvoke((ThreadStart)delegate()
            {
                txtLogCtrl.Text += s;
                txtLogCtrl.ScrollToEnd();
            }, null);
        }

        /// <summary>
        /// Status bar message display
        /// </summary>
        /// <param name="stateInfo"></param>
        private void statusBarCallback(Object stateInfo)
        {
            Application.Current.Dispatcher.BeginInvoke((ThreadStart)delegate()
            {
                int tc = Process.GetCurrentProcess().Threads.Count;
                ((StatusBarItem)(statusBar.Items[1])).Content = mLisaCOM.time.ToString() + "   [" + tc + "]";
            }, null);
        }

        /// <summary>
        /// When connect/disconnect button is pressed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void connect_Click(object sender, RoutedEventArgs e)
        {
            if (mThread == null)
            {
                Connect();
            }
            else
            {
                Disconnect();
            }
        }

        /// <summary>
        /// Connect to Lisa
        /// start thread
        /// </summary>
        private void Connect()
        {

            // add LisaCOM object
            mLisaCOM = new Lisa50Lib.LisaCOM();

            mConnected = true;

            // add LisaController object
            mLisaController = new Lisa50Lib.LisaCOMController();

            lblNumActuators.Content = mLisaController.number;

            // make initial GUI state
            btnConnect.Content = "Disconnect";
            ((StatusBarItem)(statusBar.Items[0])).Content = "Connected to Lisa";
            mTimer = new Timer(new TimerCallback(statusBarCallback), null, 0, 100);

            cbTestCOM.IsEnabled = true;
            cbTestController.IsEnabled = true;

            tbPause.IsEnabled = true;
            tbPause.IsChecked = mLisaCOM.isPaused() == 1;

            tabControl1_SelectionChanged(null, null);
        }

        /// <summary>
        /// Disconnect from COM server
        /// </summary>
        private void Disconnect()
        {
            mConnected = false;
            cbTestCOM.IsEnabled = false;
            cbTestController.IsEnabled = false;
            tbPause.IsEnabled = false;
            stopThread();

            btnConnect.Content = "Connect";
            ((StatusBarItem)(statusBar.Items[0])).Content = "Disconnected ...";

            mLisaCOM.close();
        }

        /// <summary>
        /// start method test thread
        /// </summary>
        private void startThreadTestCOM()
        {
            object o = cbTestCOM.SelectedItem;
            if ((o != null) && (mThread == null) && !tbPause.IsChecked.Value)
            {
                ThreadParamsTestCOM t = new ThreadParamsTestCOM(o.ToString(), (ushort)lbLinks.SelectedIndex, lbLinks.SelectedValue.ToString());
                mThread = new Thread(WorkThreadCOM);
                mThread.Start(t);
            }
        }

        /// <summary>
        /// start COM Controller test thread
        /// </summary>
        private void startThreadTestCOMController()
        {
            object o = cbTestController.SelectedItem;
            if ((o != null) && (mThread == null) && !tbPause.IsChecked.Value)
            {
                ThreadParamsTestCOM t = new ThreadParamsTestCOM(o.ToString(), (ushort)lbLinks.SelectedIndex, lbLinks.SelectedValue.ToString());
                mThread = new Thread(WorkThreadCOMController);
                mThread.Start(t);
            }
        }

        /// <summary>
        /// stop method test thread
        /// </summary>
        private void stopThread()
        {
            if (mThread != null)
            {
                mThread.Abort();
                mThread.Join();
                mThread = null;
            }
        }

        /// <summary>
        /// change com selection
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cbTest_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            StartCOMTest();
        }

        /// <summary>
        /// Pause or resume the simulation
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPause_Click(object sender, RoutedEventArgs e)
        {
            bool paused = tbPause.IsChecked.Value;
            mLisaCOM.pause(Convert.ToByte(!paused));
        }

        /// <summary>
        /// change text
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbPause_Unchecked(object sender, RoutedEventArgs e)
        {
            tbPause.Content = "Pause";
            StartCOMTest();
        }

        /// <summary>
        /// change text
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbPause_Checked(object sender, RoutedEventArgs e)
        {
            stopThread();
            tbPause.Content = "Resume";
        }

        /// <summary>
        /// selected actor was changed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void lbLinks_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            // change the procedure that is running
            StartCOMTest();
        }

        /// <summary>
        /// return connection status
        /// </summary>
        /// <returns></returns>
        internal static bool isConnected()
        {
            return mConnected;
        }

        /// <summary>
        /// tab selection was changed
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tabControl1_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            // prevent multiple calls
            lbLinks.SelectionChanged -= this.lbLinks_SelectionChanged;

            if (((TabItem)(tabControl1.SelectedItem)).Header.ToString() == "testCOM")
            {
                lblLinks.Content = "links";
                if (mLisaCOM != null)
                {
                    // display all link names in the left pane
                    string[] linkNames = mLisaCOM.enumerateLinks();

                    lblNumLinks.Content = mLisaCOM.numLinks;
                    lbLinks.Items.Clear();

                    foreach (string s in linkNames)
                    {
                        lbLinks.Items.Add(s);
                    }

                    lbLinks.SelectedIndex = 0;
                }
            }
            else if (((TabItem)(tabControl1.SelectedItem)).Header.ToString() == "testCOMController")
            {
                // display joint names in the left pane                                
                lblLinks.Content = "joints";

                if ((mLisaController != null))
                {
                    lblNumLinks.Content = mLisaController.number;
                    lbLinks.Items.Clear();

                    for (int i = 0; i < mLisaController.number; ++i)
                    {
                        lbLinks.Items.Add("Joint " + i);
                    }

                    lbLinks.SelectedIndex = 0;
                }
            }

            lbLinks.SelectionChanged += this.lbLinks_SelectionChanged;
            StartCOMTest();
        }

        /// <summary>
        /// select COM test to run
        /// </summary>
        private void StartCOMTest()
        {
            stopThread();

            if (((TabItem)(tabControl1.SelectedItem)).Header.ToString() == "testCOM")
            {
                startThreadTestCOM();
            }
            else if (((TabItem)(tabControl1.SelectedItem)).Header.ToString() == "testCOMController")
            {
                startThreadTestCOMController();
            }
        }

        private void btnSetSetpoint_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                double d = Double.Parse(tbSetSetPoint.Text);
                if (mLisaController!=null)
                {
                    ushort i = (ushort)lbLinks.SelectedIndex;
                    mLisaController.setSetpoint(i, 0, d);
                }
            }
            catch (FormatException) { }
        }
    }
}

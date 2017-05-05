using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace LINTool
{
    public partial class FrmMain : Form
    {
        //Constant 
        const byte SLAVE_ID=0xD8;
        const byte MASTER_SEND_ID=0x97;
        const int KEY_NUM = 18;
        enum LED_option_t {LED_LEFT=0,LED_RIGHT,LED_WIN_LOCK,LED_BCM_LOCK};

        // Global Variable
        private bool Listening = false;//是否没有执行完invoke相关操作  
        private bool Closing = false;   //是否正在关闭串口，执行Application.DoEvents，并阻止再次invoke  
        List<byte> SendBuffer = new List<byte>();
        List<byte> RecBuffer = new List<byte>();
        
        private CheckBox[] chkKeys;
        private int[] reflectTable={20,21,22,23,24,25,16,19,26,7,5,3,1,27,15,13,11,9};
        byte[] keyStates = new byte[KEY_NUM];
        bool[] isKeyPressedOnce = new bool[KEY_NUM];

        bool waitSlaveKeysData = false;
        bool isSlaveAwake = false;

        bool stopAutotest = false;

        public FrmMain()
        {
            InitializeComponent();

            chkKeys = new CheckBox[18];

            chkKeys[0] = this.chkLeftMirror;
            chkKeys[1] = this.chkRightMirror;
            chkKeys[2] = this.chkMirrorUp;
            chkKeys[3] = this.chkMirrorDown;
            chkKeys[4] = this.chkMirrorLeft;
            chkKeys[5] = this.chkMirrorRight;
            chkKeys[6] = this.chkWinLock;
            chkKeys[7] = this.chkMirrorFold;
            chkKeys[8] = this.chkBCMLock;
            chkKeys[9] = this.chkLRWinDown;
            chkKeys[10] = this.chkLRWinUp;
            chkKeys[11] = this.chkLFWinDown;
            chkKeys[12] = this.chkLFWinUp;
            chkKeys[13] = this.chkBCMUnlock;
            chkKeys[14] = this.chkRRWinDown;
            chkKeys[15] = this.chkRRWinUp;
            chkKeys[16] = this.chkRFWinDown;
            chkKeys[17] = this.chkRFWinUp;

        }

        private void FrmMain_Load(object sender, EventArgs e)
        {
            //-----------------串口设置----------------------
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort_DataReceived);
            serialPort1.NewLine = "\r\n";   //新行的内容
            

            foreach (string com in SerialPort.GetPortNames())
                cmbPort.Items.Add(com);
            if (cmbPort.Items.Count > 0)
                cmbPort.SelectedIndex = 0;

            cmbBaud.Items.Add("9600");
            cmbBaud.Items.Add("19200");
          //  cmbBaud.Items.Add("57600");
          //  cmbBaud.Items.Add("115200");
            cmbBaud.SelectedIndex = 1;

            //设定字体大小
            for (int i = 0; i < KEY_NUM; i++)
                chkKeys[i].Font=new Font(chkKeys[i].Font.FontFamily,12,chkKeys[i].Font.Style);

            
           
        }

 
        void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (Closing) return;//如果正在关闭，忽略操作，直接返回，尽快的完成串口监听线程的一次循环 
            try
            {
                Listening = true;//设置标记，说明我已经开始处理数据，一会儿要使用系统UI的。  
               
                if (waitSlaveKeysData == false) { 
                    serialPort1.DiscardInBuffer();
                }
                else{
                    byte[] rcv = new byte[serialPort1.BytesToRead];
                    serialPort1.Read(rcv, 0, rcv.Length);
                    RecBuffer.AddRange(rcv);
                    //cntTotal++;
                    //干掉自发自收的轮询指令 0x00 0x55 0xD8
                    if (RecBuffer.ToArray().Length >= 3)
                    {
                        int i = 0;
                        //for (int i = 0; i < RecBuffer.ToArray().Length - 2; i++)
                        while (i < RecBuffer.ToArray().Length - 2)
                        {
                            if (((RecBuffer.ToArray()[i] == 0x00) && (RecBuffer.ToArray()[i + 1] == 0x55) && ((RecBuffer.ToArray()[i + 2] == SLAVE_ID) || (RecBuffer.ToArray()[i + 2] == MASTER_SEND_ID))))
                            {
                                if ((RecBuffer.ToArray()[i + 2] == SLAVE_ID))//单次轮询
                                {
                                    RecBuffer.RemoveRange(i, 3);
                                }
                            }
                            i++;
                        }
                    }
                    //if (RecBuffer.Count >= 9+3)   //接收完成
                    if (RecBuffer.Count >= 9)   //接收到有效的从机数据，接收完成
                    {
                        //cntValid++;
                        isSlaveAwake = true;
                        //删除开头自发的询问指令0x00 0x55 0xD8，Important
                        //RecBuffer.RemoveRange(0, 3);
                        //处理LinData
                        UpdateKeysUI(RecBuffer.ToArray());
                        RecBuffer.Clear();
                        //判断是否完成所有按键测试
                        ChkTestDone();
                        //
                        waitSlaveKeysData = false;
                    }
                }
                //if(cntTotal > cntValid + 10)
                /*
                byte[] rcv = new byte[serialPort1.BytesToRead];
                serialPort1.Read(rcv, 0, rcv.Length);

                else
                {

                    RecBuffer.AddRange(rcv);
                    //屏蔽自发的
                    //RecBuffer.RemoveAll(
                    if (RecBuffer.ToArray().Length >= 3)
                    {
                        int i = 0;
                        //for (int i = 0; i < RecBuffer.ToArray().Length - 2; i++)
                        while (i < RecBuffer.ToArray().Length - 2)
                        {
                            if (((RecBuffer.ToArray()[i] == 0x00) && (RecBuffer.ToArray()[i + 1] == 0x55) && ((RecBuffer.ToArray()[i + 2] == SLAVE_ID) || (RecBuffer.ToArray()[i + 2] == MASTER_SEND_ID))))
                            {
                                if ((RecBuffer.ToArray()[i + 2] == SLAVE_ID))//单次轮询
                                {
                                    RecBuffer.RemoveRange(i, 3);
                                }
                                else   //发lED，后加8个字节
                                {
                                    if (RecBuffer.ToArray().Length >= i + 3 + 8)
                                        RecBuffer.RemoveRange(i, 3 + 8);
                                }
                            }

                            i++;
                        }
                    }

                    //
                    if (RecBuffer.Count >= 9)   //接收完成
                    {
                        //处理LinData
                        UpdateKeysUI(RecBuffer.ToArray());
                        //判断是否完成所有按键测试
                        ChkTestDone();
                        //
                        waitSlaveKeysData = false;
                    }
                 
                }*/
                
              

                //因为要访问ui资源，所以需要使用invoke方式同步ui。  
                /*this.Invoke((EventHandler)(delegate
                {
                    //tssRecCnt.Text = "    Rec count: " + received_count.ToString();
                    //tssRecCnt.Text = string.Format("    Rec count: {0}    ", received_count);
                    //lblTest.Text = ((int)rcv[0]).ToString();
                    
                }));*/

            }
            finally
            {
                Listening = false;//我用完了，ui可以关闭串口了。  
            }

            
        }
       
       
        private void btnManual_Click(object sender, EventArgs e)
        {
            //等待从机唤醒，以防万一。
            //lblState.Text = "等待从机唤醒中...";
            isSlaveAwake = false;
            WaitSlaveWakeup();
            LEDControl(chkLEDBCMLock.Checked, chkLEDWinLock.Checked, chkLEDLeft.Checked, chkLEDRight.Checked);
        }

        private void btnPortOpen_Click(object sender, EventArgs e)
        {
            
            if (serialPort1.IsOpen)
            {
                //若进在测试，需要复位UI、线程及状态变量
                if(btnAuto.Text=="停止测试")
                {
                    ResetAndClear();
                }
                //
                serialPortSafeClose(serialPort1);
                
            }
            else
            {
                //关闭时点击，则设置好端口，波特率后打开  
                serialPort1.PortName = cmbPort.Text;
                serialPort1.BaudRate = int.Parse(cmbBaud.Text);
                
                try
                {
                    serialPort1.Open();
                    //serialPort1.DiscardInBuffer();
                    //serialPort1.DiscardOutBuffer();
                }
                catch (Exception ex)
                {
                    //捕获到异常信息，创建一个新的comm对象，之前的不能用了。  !!!! 
                    serialPort1 = new SerialPort();
                    //现实异常信息给客户。  
                    MessageBox.Show(ex.Message);
                }
            }

            //设置按钮的状态  
            btnPortOpen.Text = serialPort1.IsOpen ? "Close" : "Open";

            //只要串口重新开关，都要关闭轮询线程
            if (stopAutotest == false)
            {
                stopAutotest = true;
                Thread.Sleep(350);
            }
          /*  if (serialPort1.IsOpen)
                tssl1.Text = "    Serial port is open     ";
            else
                tssl1.Text = "    Serial port is close    ";
           */
        }


        

        void serialPortSafeClose(SerialPort sp)
        {
            Closing = true;
            while (Listening) Application.DoEvents();
            //打开时点击，则关闭串口  
            sp.Close();
            Closing = false;

            
        }
        //安全发送
        int serialPortSafeWrite(SerialPort sp, byte[] buffer, int offset, int count)
        {
            if (sp.IsOpen)
            {
                sp.Write(buffer, offset, count);
                return 1;
            }
            else
            {
                MessageBox.Show("串口未打开", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return -1;
            }
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void btnAuto_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == false)
            {
                MessageBox.Show("串口未打开", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            if ((btnAuto.Text == "自动测试") )
            {
                //等待从机唤醒 
                lblState.Text = "等待从机唤醒中...";
                isSlaveAwake = false;
                if (WaitSlaveWakeup() == -1)
                {
                    lblState.Text = "待测试";
                    return;
                }
                lblState.Text = "测试中...";
               
                //软件的绿色指示灯变灰
                btnAuto.Text = "停止测试";
                LEDTipSet(false);
                //四个灯，闪三秒，保持全亮
                //ThreadPool.QueueUserWorkItem(ThreadTestLED, "None");
                //发送LED控制指令，全常亮
                LEDControl(true, true, true, true); 
                //开始轮询前，清空uart所有接收buffer、禁止手动控制LED，避免刚才自发自收影响
                Thread.Sleep(100);  //重要
                serialPort1.DiscardInBuffer();
                btnManual.Enabled = false;
                //间隔0.1秒轮询，显示键值
                stopAutotest = false;
                ThreadPool.QueueUserWorkItem(ThreadQueryState, "None");
                
            }
            else if(btnAuto.Text=="停止测试")
            {
                stopAutotest = true;
                isSlaveAwake = false;
                btnAuto.Text = "自动测试";
                lblState.Text = "待测试";
                KeysUIClear();
                LEDTipSet(false);
                //发送LED控制指令，全常亮
                LEDControl(false, false, false, false);
                btnManual.Enabled = true;
                if(rdoNo.Checked == true)
                    chkKeys[7].BackColor = Color.Gray;
            }
        }

        private void ResetAndClear()
        {
            stopAutotest = true;
            isSlaveAwake = false;
            btnAuto.Text = "自动测试";
            lblState.Text = "待测试";
            KeysUIClear();
            LEDTipSet(false);
            //发送LED控制指令，全常亮
            //LEDControl(false, false, false, false);
            btnManual.Enabled = true;
            if (rdoNo.Checked == true)
                chkKeys[7].BackColor = Color.Gray;

        }
        
        private void ThreadTestLED(object data)
        {
            bool on=true;
            /*
            for(int i=0;i<6;i++)
            {
                if (LEDControl(on, on, on, on) == -1)
                    break;
                on = !on;
                Thread.Sleep(500);
            } */
            for (int i = 0; i < 7; i++)
            {
                LEDControl(on, on, on, on);
              //  Thread.Sleep(300);
            }
        }

        private void ThreadQueryState(object data)
        {
          //  int sta = 0;    //movement state FSM
          //  int noLinReturnCnt = 0;

            while (!stopAutotest)
            {
                int res;
                res = LinReqState();
                System.Threading.Thread.Sleep(300);
                /*
                if (waitSlaveKeysData == true)    //waitSlaveKeysData未被复位,说明没接收到Lin从机的数据
                {
                    noLinReturnCnt++;
                    if (noLinReturnCnt >= 10)
                    {
                        noLinReturnCnt = 0;
                        KeysUIClear();
                    }
                }*/

                if (res != 1)
                    break;
            }

            stopAutotest = false;
        }

        

        //----下层函数---//
        //等待从机唤醒
        private int WaitSlaveWakeup()
        {
            int cnt = 0;
            while (isSlaveAwake == false)
            {
                
                LinReqState();
                Thread.Sleep(300);
                cnt++;
                if (cnt >= 10)
                {
                    MessageBox.Show("从机未能唤醒，请检查连接。", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return -1;
                    break;

                }
            }
            return 1;
        }
        //灯控制
        private int LEDControl(bool bcm,bool win,bool left,bool right)
        {
            byte ledB=0;
            byte[] LinData={0,0,0,0,0,0,0,0};
            //读取控件的选择状态
            if (bcm)
                ledB = (byte)(ledB |  (0x01 << 3));
            if (win)
                ledB = (byte)(ledB | (0x01 << 4));
            if (left)
                ledB = (byte)(ledB | (0x01 << 6));
            if (right)
                ledB = (byte)(ledB | (0x01 << 7));
            LinData[0] = ledB;

            //串口发送
            SendBuffer.Clear();
            SendBuffer.Add(0x00);
            SendBuffer.Add(0x55);
            SendBuffer.Add(MASTER_SEND_ID);
            SendBuffer.AddRange(LinData);

            //发指令暂时不用和校验
            return serialPortSafeWrite(serialPort1, SendBuffer.ToArray(), 0, SendBuffer.Count);

        }
        //单次轮询
        private int LinReqState()
        {
            int res;
            SendBuffer.Clear();
            SendBuffer.Add(0x00);
            SendBuffer.Add(0x55);
            SendBuffer.Add(SLAVE_ID);
            
            res = serialPortSafeWrite(serialPort1, SendBuffer.ToArray(), 0, SendBuffer.Count);

            if(res==-1)
                return res;
            //清空自发自收的数据,但瞬时发的0x00，0x55 0xD8清不掉（因紧接着要收，至少此前发过或收过带来的干扰。
            serialPort1.DiscardInBuffer();
            //等待接收数据
            waitSlaveKeysData = true;
            RecBuffer.Clear();
            return 1;

        }
        //根据linData显示UI
        private void UpdateKeysUI(byte[] linData)
        {
            Int32 keysVal= (Int32)(linData[4] << 24 | linData[3] << 16 | linData[2] << 8 | linData[1]);
            int i;
             
            // 对linData做和校验
            

            // linData映射到按键值chkKeys，并在UI上即时勾选
            for (i = 0; i < reflectTable.Count(); i++)
            {
                // 
                if ((keysVal & (Int32)(1 << reflectTable[i])) != 0)
                {
                    this.Invoke((EventHandler)delegate{
                        chkKeys[i].Checked = true; 
                    });

                }
                else
                    this.Invoke((EventHandler)delegate{
                    chkKeys[i].Checked = false;
                    });

                // 根据历史按键值状态判断是否按过,并加背景灰色
                switch (keyStates[i])
                { 
                    case 0: //idle
                        if (chkKeys[i].Checked)
                            keyStates[i] = 1;
                        break;
                    case 1: //press down
                        if (chkKeys[i].Checked == false)
                        {
                            this.Invoke((EventHandler)delegate
                            {
                                isKeyPressedOnce[i] = true;
                                chkKeys[i].BackColor = Color.Gray;  //按过背景变灰
                            });
                            keyStates[i] = 0;
                        }
                        break;
                   // case 2: //relieve
                        
                   //     break;
                }

                /*
                if (chkKeys[i].Checked == true && isKeyPressedOnce[i] == false)
                {
                  //  chkKeys[i].BackColor = Color.Red;
                }
                else if ( isKeyPressedOnce[i] == true)
                {
                    chkKeys[i].BackColor = Color.Gray;
                }
                 */

            }



        }
        //清空UI
        private void KeysUIClear()
        {
            for (int i = 0; i < KEY_NUM; i++)
            {
                this.Invoke((EventHandler)delegate
                {
                    isKeyPressedOnce[i] = false;
                    chkKeys[i].BackColor = Color.WhiteSmoke;  //按过背景变灰
                    chkKeys[i].Checked = false;
                });
                keyStates[i] = 0;
            }
        }

        //判断是否测试通过
        private void ChkTestDone()
        {
            bool testPass=true;

            for (int i = 0; i < KEY_NUM; i++)
            {
                if (chkKeys[i].BackColor != Color.Gray)
                {
                    testPass = false;
                    break;
                }
            }
            if (testPass == true)
            {
                this.Invoke((EventHandler)delegate
                {
                    lblState.BackColor = Color.Green;
                    lblState.Text = "测试通过";

                    btnAuto.Text = "自动测试";
                    stopAutotest = true;
                    KeysUIClear();
                    
                    //亮绿灯
                    LEDTipSet(true);
                });
            }
        }


        private void chkBCMUnlock_CheckedChanged(object sender, EventArgs e)
        {

        }
        //是否测折叠
        private void rdoNo_CheckedChanged(object sender, EventArgs e)
        {
             //ledTip.BackColor = Color.Green;//
           // LEDTipSet(true);
            if (rdoNo.Checked == true)
            {
                for (int i = 7; i < 8; i++)
                {
                    chkKeys[i].BackColor = Color.Gray;
                }
            }
            else
            {
                for (int i = 7; i < 8; i++)
                {
                    chkKeys[i].BackColor = Color.WhiteSmoke;
                }
            }
            
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void ledTip_Load(object sender, EventArgs e)
        {

        }

        private void LEDTipSet(bool on)
        {
            if (on)
            {/*
                ledTip.LEDCenterColor = Color.YellowGreen;
                ledTip.LEDCircleColor = Color.LightGreen;
                ledTip.LEDSurroundColor = Color.LightGreen;
                //ledTip.LEDSwitch = false;
              */
                ledTipOff.Visible = false;
                ledTipOn.Visible = true;
                
            }
            else
            {
                /*
                ledTip.LEDCenterColor = Color.Black;
                ledTip.LEDCircleColor = Color.Gray;
                ledTip.LEDSurroundColor = Color.Gray;
                 */
                ledTipOff.Visible = true;
                ledTipOn.Visible = false;
            }

        }

        private void chkLEDBCMLock_CheckedChanged(object sender, EventArgs e)
        {
        }
    }
}

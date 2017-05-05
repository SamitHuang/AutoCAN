namespace LINTool
{
    partial class FrmMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.gbSerialPort = new System.Windows.Forms.GroupBox();
            this.cmbBaud = new System.Windows.Forms.ComboBox();
            this.cmbPort = new System.Windows.Forms.ComboBox();
            this.lblPort = new System.Windows.Forms.Label();
            this.lblBaud = new System.Windows.Forms.Label();
            this.btnPortOpen = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.chkLEDRight = new System.Windows.Forms.CheckBox();
            this.chkLEDLeft = new System.Windows.Forms.CheckBox();
            this.chkLEDWinLock = new System.Windows.Forms.CheckBox();
            this.btnManual = new System.Windows.Forms.Button();
            this.chkLEDBCMLock = new System.Windows.Forms.CheckBox();
            this.btnAuto = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.ledTipOn = new LEDLib.LEDControl();
            this.lblLedTip = new System.Windows.Forms.Label();
            this.ledTipOff = new LEDLib.LEDControl();
            this.label1 = new System.Windows.Forms.Label();
            this.rdoNo = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.chkRFWinUp = new System.Windows.Forms.CheckBox();
            this.chkRFWinDown = new System.Windows.Forms.CheckBox();
            this.chkRRWinUp = new System.Windows.Forms.CheckBox();
            this.chkRRWinDown = new System.Windows.Forms.CheckBox();
            this.chkBCMUnlock = new System.Windows.Forms.CheckBox();
            this.chkLFWinUp = new System.Windows.Forms.CheckBox();
            this.chkLFWinDown = new System.Windows.Forms.CheckBox();
            this.chkLRWinUp = new System.Windows.Forms.CheckBox();
            this.chkLRWinDown = new System.Windows.Forms.CheckBox();
            this.chkBCMLock = new System.Windows.Forms.CheckBox();
            this.chkMirrorFold = new System.Windows.Forms.CheckBox();
            this.chkWinLock = new System.Windows.Forms.CheckBox();
            this.chkMirrorRight = new System.Windows.Forms.CheckBox();
            this.chkMirrorLeft = new System.Windows.Forms.CheckBox();
            this.chkMirrorDown = new System.Windows.Forms.CheckBox();
            this.chkMirrorUp = new System.Windows.Forms.CheckBox();
            this.chkRightMirror = new System.Windows.Forms.CheckBox();
            this.chkLeftMirror = new System.Windows.Forms.CheckBox();
            this.lblState = new System.Windows.Forms.Label();
            this.gbSerialPort.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbSerialPort
            // 
            this.gbSerialPort.BackColor = System.Drawing.Color.Transparent;
            this.gbSerialPort.Controls.Add(this.cmbBaud);
            this.gbSerialPort.Controls.Add(this.cmbPort);
            this.gbSerialPort.Controls.Add(this.lblPort);
            this.gbSerialPort.Controls.Add(this.lblBaud);
            this.gbSerialPort.Controls.Add(this.btnPortOpen);
            this.gbSerialPort.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.gbSerialPort.Location = new System.Drawing.Point(14, 50);
            this.gbSerialPort.Name = "gbSerialPort";
            this.gbSerialPort.Size = new System.Drawing.Size(583, 85);
            this.gbSerialPort.TabIndex = 6;
            this.gbSerialPort.TabStop = false;
            this.gbSerialPort.Text = "串口设置";
            // 
            // cmbBaud
            // 
            this.cmbBaud.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBaud.FormattingEnabled = true;
            this.cmbBaud.Location = new System.Drawing.Point(238, 34);
            this.cmbBaud.Name = "cmbBaud";
            this.cmbBaud.Size = new System.Drawing.Size(121, 24);
            this.cmbBaud.TabIndex = 2;
            // 
            // cmbPort
            // 
            this.cmbPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPort.FormattingEnabled = true;
            this.cmbPort.Location = new System.Drawing.Point(31, 33);
            this.cmbPort.Name = "cmbPort";
            this.cmbPort.Size = new System.Drawing.Size(121, 24);
            this.cmbPort.Sorted = true;
            this.cmbPort.TabIndex = 1;
            // 
            // lblPort
            // 
            this.lblPort.AutoSize = true;
            this.lblPort.Location = new System.Drawing.Point(2, 37);
            this.lblPort.Name = "lblPort";
            this.lblPort.Size = new System.Drawing.Size(32, 16);
            this.lblPort.TabIndex = 3;
            this.lblPort.Text = "COM";
            // 
            // lblBaud
            // 
            this.lblBaud.AutoSize = true;
            this.lblBaud.Location = new System.Drawing.Point(191, 37);
            this.lblBaud.Name = "lblBaud";
            this.lblBaud.Size = new System.Drawing.Size(40, 16);
            this.lblBaud.TabIndex = 4;
            this.lblBaud.Text = "Rate";
            // 
            // btnPortOpen
            // 
            this.btnPortOpen.Location = new System.Drawing.Point(445, 28);
            this.btnPortOpen.Name = "btnPortOpen";
            this.btnPortOpen.Size = new System.Drawing.Size(75, 35);
            this.btnPortOpen.TabIndex = 0;
            this.btnPortOpen.Text = "Open";
            this.btnPortOpen.UseVisualStyleBackColor = true;
            this.btnPortOpen.Click += new System.EventHandler(this.btnPortOpen_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.chkLEDRight);
            this.groupBox1.Controls.Add(this.chkLEDLeft);
            this.groupBox1.Controls.Add(this.chkLEDWinLock);
            this.groupBox1.Controls.Add(this.btnManual);
            this.groupBox1.Controls.Add(this.chkLEDBCMLock);
            this.groupBox1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(14, 141);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(583, 133);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "指示灯控制";
            // 
            // chkLEDRight
            // 
            this.chkLEDRight.AutoSize = true;
            this.chkLEDRight.Location = new System.Drawing.Point(445, 33);
            this.chkLEDRight.Name = "chkLEDRight";
            this.chkLEDRight.Size = new System.Drawing.Size(91, 20);
            this.chkLEDRight.TabIndex = 0;
            this.chkLEDRight.Text = "右后视镜";
            this.chkLEDRight.UseVisualStyleBackColor = true;
            // 
            // chkLEDLeft
            // 
            this.chkLEDLeft.AutoSize = true;
            this.chkLEDLeft.Location = new System.Drawing.Point(305, 33);
            this.chkLEDLeft.Name = "chkLEDLeft";
            this.chkLEDLeft.Size = new System.Drawing.Size(91, 20);
            this.chkLEDLeft.TabIndex = 0;
            this.chkLEDLeft.Text = "左后视镜";
            this.chkLEDLeft.UseVisualStyleBackColor = true;
            // 
            // chkLEDWinLock
            // 
            this.chkLEDWinLock.AutoSize = true;
            this.chkLEDWinLock.Location = new System.Drawing.Point(155, 33);
            this.chkLEDWinLock.Name = "chkLEDWinLock";
            this.chkLEDWinLock.Size = new System.Drawing.Size(75, 20);
            this.chkLEDWinLock.TabIndex = 0;
            this.chkLEDWinLock.Text = "车窗锁";
            this.chkLEDWinLock.UseVisualStyleBackColor = true;
            // 
            // btnManual
            // 
            this.btnManual.Location = new System.Drawing.Point(141, 75);
            this.btnManual.Name = "btnManual";
            this.btnManual.Size = new System.Drawing.Size(255, 41);
            this.btnManual.TabIndex = 1;
            this.btnManual.Text = "单次发送";
            this.btnManual.UseVisualStyleBackColor = true;
            this.btnManual.Click += new System.EventHandler(this.btnManual_Click);
            // 
            // chkLEDBCMLock
            // 
            this.chkLEDBCMLock.AutoSize = true;
            this.chkLEDBCMLock.Location = new System.Drawing.Point(10, 33);
            this.chkLEDBCMLock.Name = "chkLEDBCMLock";
            this.chkLEDBCMLock.Size = new System.Drawing.Size(75, 20);
            this.chkLEDBCMLock.TabIndex = 0;
            this.chkLEDBCMLock.Text = "中控锁";
            this.chkLEDBCMLock.UseVisualStyleBackColor = true;
            this.chkLEDBCMLock.CheckedChanged += new System.EventHandler(this.chkLEDBCMLock_CheckedChanged);
            // 
            // btnAuto
            // 
            this.btnAuto.Location = new System.Drawing.Point(143, 366);
            this.btnAuto.Name = "btnAuto";
            this.btnAuto.Size = new System.Drawing.Size(255, 41);
            this.btnAuto.TabIndex = 1;
            this.btnAuto.Text = "自动测试";
            this.btnAuto.UseVisualStyleBackColor = true;
            this.btnAuto.Click += new System.EventHandler(this.btnAuto_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.ledTipOn);
            this.groupBox2.Controls.Add(this.lblLedTip);
            this.groupBox2.Controls.Add(this.ledTipOff);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.rdoNo);
            this.groupBox2.Controls.Add(this.btnAuto);
            this.groupBox2.Controls.Add(this.radioButton1);
            this.groupBox2.Controls.Add(this.chkRFWinUp);
            this.groupBox2.Controls.Add(this.chkRFWinDown);
            this.groupBox2.Controls.Add(this.chkRRWinUp);
            this.groupBox2.Controls.Add(this.chkRRWinDown);
            this.groupBox2.Controls.Add(this.chkBCMUnlock);
            this.groupBox2.Controls.Add(this.chkLFWinUp);
            this.groupBox2.Controls.Add(this.chkLFWinDown);
            this.groupBox2.Controls.Add(this.chkLRWinUp);
            this.groupBox2.Controls.Add(this.chkLRWinDown);
            this.groupBox2.Controls.Add(this.chkBCMLock);
            this.groupBox2.Controls.Add(this.chkMirrorFold);
            this.groupBox2.Controls.Add(this.chkWinLock);
            this.groupBox2.Controls.Add(this.chkMirrorRight);
            this.groupBox2.Controls.Add(this.chkMirrorLeft);
            this.groupBox2.Controls.Add(this.chkMirrorDown);
            this.groupBox2.Controls.Add(this.chkMirrorUp);
            this.groupBox2.Controls.Add(this.chkRightMirror);
            this.groupBox2.Controls.Add(this.chkLeftMirror);
            this.groupBox2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.Location = new System.Drawing.Point(14, 289);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(585, 434);
            this.groupBox2.TabIndex = 8;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "按键状态";
            this.groupBox2.Enter += new System.EventHandler(this.groupBox2_Enter);
            // 
            // ledTipOn
            // 
            this.ledTipOn.LEDCenterColor = System.Drawing.Color.GreenYellow;
            this.ledTipOn.LEDCircleColor = System.Drawing.Color.LightGreen;
            this.ledTipOn.LEDClickEnable = true;
            this.ledTipOn.LEDSurroundColor = System.Drawing.Color.LightGreen;
            this.ledTipOn.LEDSwitch = true;
            this.ledTipOn.Location = new System.Drawing.Point(463, 47);
            this.ledTipOn.Margin = new System.Windows.Forms.Padding(4);
            this.ledTipOn.Name = "ledTipOn";
            this.ledTipOn.Size = new System.Drawing.Size(73, 79);
            this.ledTipOn.TabIndex = 7;
            this.ledTipOn.Visible = false;
            // 
            // lblLedTip
            // 
            this.lblLedTip.AutoSize = true;
            this.lblLedTip.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblLedTip.Location = new System.Drawing.Point(471, 131);
            this.lblLedTip.Name = "lblLedTip";
            this.lblLedTip.Size = new System.Drawing.Size(65, 12);
            this.lblLedTip.TabIndex = 6;
            this.lblLedTip.Text = "通过指示灯";
            // 
            // ledTipOff
            // 
            this.ledTipOff.LEDCenterColor = System.Drawing.Color.Black;
            this.ledTipOff.LEDCircleColor = System.Drawing.Color.Gray;
            this.ledTipOff.LEDClickEnable = true;
            this.ledTipOff.LEDSurroundColor = System.Drawing.Color.Gray;
            this.ledTipOff.LEDSwitch = true;
            this.ledTipOff.Location = new System.Drawing.Point(463, 47);
            this.ledTipOff.Margin = new System.Windows.Forms.Padding(4);
            this.ledTipOff.Name = "ledTipOff";
            this.ledTipOff.Size = new System.Drawing.Size(73, 80);
            this.ledTipOff.TabIndex = 5;
            this.ledTipOff.Load += new System.EventHandler(this.ledTip_Load);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(28, 51);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(152, 16);
            this.label1.TabIndex = 3;
            this.label1.Text = "是否测试折叠功能：";
            // 
            // rdoNo
            // 
            this.rdoNo.AutoSize = true;
            this.rdoNo.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.rdoNo.Location = new System.Drawing.Point(329, 47);
            this.rdoNo.Name = "rdoNo";
            this.rdoNo.Size = new System.Drawing.Size(42, 20);
            this.rdoNo.TabIndex = 2;
            this.rdoNo.Text = "否";
            this.rdoNo.UseVisualStyleBackColor = true;
            this.rdoNo.CheckedChanged += new System.EventHandler(this.rdoNo_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.radioButton1.Location = new System.Drawing.Point(206, 47);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(42, 20);
            this.radioButton1.TabIndex = 1;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "是";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // chkRFWinUp
            // 
            this.chkRFWinUp.AutoCheck = false;
            this.chkRFWinUp.AutoSize = true;
            this.chkRFWinUp.Location = new System.Drawing.Point(291, 229);
            this.chkRFWinUp.Name = "chkRFWinUp";
            this.chkRFWinUp.Size = new System.Drawing.Size(107, 20);
            this.chkRFWinUp.TabIndex = 0;
            this.chkRFWinUp.Text = "右前窗上升";
            this.chkRFWinUp.UseVisualStyleBackColor = true;
            // 
            // chkRFWinDown
            // 
            this.chkRFWinDown.AutoCheck = false;
            this.chkRFWinDown.AutoSize = true;
            this.chkRFWinDown.Location = new System.Drawing.Point(291, 262);
            this.chkRFWinDown.Name = "chkRFWinDown";
            this.chkRFWinDown.Size = new System.Drawing.Size(107, 20);
            this.chkRFWinDown.TabIndex = 0;
            this.chkRFWinDown.Text = "右前窗下降";
            this.chkRFWinDown.UseVisualStyleBackColor = true;
            // 
            // chkRRWinUp
            // 
            this.chkRRWinUp.AutoCheck = false;
            this.chkRRWinUp.AutoSize = true;
            this.chkRRWinUp.Location = new System.Drawing.Point(291, 294);
            this.chkRRWinUp.Name = "chkRRWinUp";
            this.chkRRWinUp.Size = new System.Drawing.Size(107, 20);
            this.chkRRWinUp.TabIndex = 0;
            this.chkRRWinUp.Text = "右后窗上升";
            this.chkRRWinUp.UseVisualStyleBackColor = true;
            // 
            // chkRRWinDown
            // 
            this.chkRRWinDown.AutoCheck = false;
            this.chkRRWinDown.AutoSize = true;
            this.chkRRWinDown.Location = new System.Drawing.Point(291, 326);
            this.chkRRWinDown.Name = "chkRRWinDown";
            this.chkRRWinDown.Size = new System.Drawing.Size(107, 20);
            this.chkRRWinDown.TabIndex = 0;
            this.chkRRWinDown.Text = "右后窗下降";
            this.chkRRWinDown.UseVisualStyleBackColor = true;
            // 
            // chkBCMUnlock
            // 
            this.chkBCMUnlock.AutoCheck = false;
            this.chkBCMUnlock.AutoSize = true;
            this.chkBCMUnlock.Location = new System.Drawing.Point(291, 117);
            this.chkBCMUnlock.Name = "chkBCMUnlock";
            this.chkBCMUnlock.Size = new System.Drawing.Size(91, 20);
            this.chkBCMUnlock.TabIndex = 0;
            this.chkBCMUnlock.Text = "中控解锁";
            this.chkBCMUnlock.UseVisualStyleBackColor = true;
            this.chkBCMUnlock.CheckedChanged += new System.EventHandler(this.chkBCMUnlock_CheckedChanged);
            // 
            // chkLFWinUp
            // 
            this.chkLFWinUp.AutoCheck = false;
            this.chkLFWinUp.AutoSize = true;
            this.chkLFWinUp.Location = new System.Drawing.Point(31, 229);
            this.chkLFWinUp.Name = "chkLFWinUp";
            this.chkLFWinUp.Size = new System.Drawing.Size(107, 20);
            this.chkLFWinUp.TabIndex = 0;
            this.chkLFWinUp.Text = "左前窗上升";
            this.chkLFWinUp.UseVisualStyleBackColor = true;
            // 
            // chkLFWinDown
            // 
            this.chkLFWinDown.AutoCheck = false;
            this.chkLFWinDown.AutoSize = true;
            this.chkLFWinDown.Location = new System.Drawing.Point(31, 262);
            this.chkLFWinDown.Name = "chkLFWinDown";
            this.chkLFWinDown.Size = new System.Drawing.Size(107, 20);
            this.chkLFWinDown.TabIndex = 0;
            this.chkLFWinDown.Text = "左前窗下降";
            this.chkLFWinDown.UseVisualStyleBackColor = true;
            // 
            // chkLRWinUp
            // 
            this.chkLRWinUp.AutoCheck = false;
            this.chkLRWinUp.AutoSize = true;
            this.chkLRWinUp.Location = new System.Drawing.Point(31, 294);
            this.chkLRWinUp.Name = "chkLRWinUp";
            this.chkLRWinUp.Size = new System.Drawing.Size(107, 20);
            this.chkLRWinUp.TabIndex = 0;
            this.chkLRWinUp.Text = "左后窗上升";
            this.chkLRWinUp.UseVisualStyleBackColor = true;
            // 
            // chkLRWinDown
            // 
            this.chkLRWinDown.AutoCheck = false;
            this.chkLRWinDown.AutoSize = true;
            this.chkLRWinDown.Location = new System.Drawing.Point(31, 326);
            this.chkLRWinDown.Name = "chkLRWinDown";
            this.chkLRWinDown.Size = new System.Drawing.Size(107, 20);
            this.chkLRWinDown.TabIndex = 0;
            this.chkLRWinDown.Text = "左后窗下降";
            this.chkLRWinDown.UseVisualStyleBackColor = true;
            // 
            // chkBCMLock
            // 
            this.chkBCMLock.AutoCheck = false;
            this.chkBCMLock.AutoSize = true;
            this.chkBCMLock.Location = new System.Drawing.Point(291, 87);
            this.chkBCMLock.Name = "chkBCMLock";
            this.chkBCMLock.Size = new System.Drawing.Size(75, 20);
            this.chkBCMLock.TabIndex = 0;
            this.chkBCMLock.Text = "中控锁";
            this.chkBCMLock.UseVisualStyleBackColor = true;
            // 
            // chkMirrorFold
            // 
            this.chkMirrorFold.AutoCheck = false;
            this.chkMirrorFold.AutoSize = true;
            this.chkMirrorFold.Location = new System.Drawing.Point(291, 180);
            this.chkMirrorFold.Name = "chkMirrorFold";
            this.chkMirrorFold.Size = new System.Drawing.Size(107, 20);
            this.chkMirrorFold.TabIndex = 0;
            this.chkMirrorFold.Text = "后视镜折叠";
            this.chkMirrorFold.UseVisualStyleBackColor = true;
            // 
            // chkWinLock
            // 
            this.chkWinLock.AutoCheck = false;
            this.chkWinLock.AutoSize = true;
            this.chkWinLock.Location = new System.Drawing.Point(291, 148);
            this.chkWinLock.Name = "chkWinLock";
            this.chkWinLock.Size = new System.Drawing.Size(59, 20);
            this.chkWinLock.TabIndex = 0;
            this.chkWinLock.Text = "窗锁";
            this.chkWinLock.UseVisualStyleBackColor = true;
            // 
            // chkMirrorRight
            // 
            this.chkMirrorRight.AutoCheck = false;
            this.chkMirrorRight.AutoSize = true;
            this.chkMirrorRight.Location = new System.Drawing.Point(106, 180);
            this.chkMirrorRight.Name = "chkMirrorRight";
            this.chkMirrorRight.Size = new System.Drawing.Size(59, 20);
            this.chkMirrorRight.TabIndex = 0;
            this.chkMirrorRight.Text = "右动";
            this.chkMirrorRight.UseVisualStyleBackColor = true;
            // 
            // chkMirrorLeft
            // 
            this.chkMirrorLeft.AutoCheck = false;
            this.chkMirrorLeft.AutoSize = true;
            this.chkMirrorLeft.Location = new System.Drawing.Point(31, 180);
            this.chkMirrorLeft.Name = "chkMirrorLeft";
            this.chkMirrorLeft.Size = new System.Drawing.Size(59, 20);
            this.chkMirrorLeft.TabIndex = 0;
            this.chkMirrorLeft.Text = "左动";
            this.chkMirrorLeft.UseVisualStyleBackColor = true;
            // 
            // chkMirrorDown
            // 
            this.chkMirrorDown.AutoCheck = false;
            this.chkMirrorDown.AutoSize = true;
            this.chkMirrorDown.Location = new System.Drawing.Point(106, 148);
            this.chkMirrorDown.Name = "chkMirrorDown";
            this.chkMirrorDown.Size = new System.Drawing.Size(59, 20);
            this.chkMirrorDown.TabIndex = 0;
            this.chkMirrorDown.Text = "下动";
            this.chkMirrorDown.UseVisualStyleBackColor = true;
            // 
            // chkMirrorUp
            // 
            this.chkMirrorUp.AutoCheck = false;
            this.chkMirrorUp.AutoSize = true;
            this.chkMirrorUp.Location = new System.Drawing.Point(31, 148);
            this.chkMirrorUp.Name = "chkMirrorUp";
            this.chkMirrorUp.Size = new System.Drawing.Size(59, 20);
            this.chkMirrorUp.TabIndex = 0;
            this.chkMirrorUp.Text = "上动";
            this.chkMirrorUp.UseVisualStyleBackColor = true;
            // 
            // chkRightMirror
            // 
            this.chkRightMirror.AutoCheck = false;
            this.chkRightMirror.AutoSize = true;
            this.chkRightMirror.Location = new System.Drawing.Point(31, 117);
            this.chkRightMirror.Name = "chkRightMirror";
            this.chkRightMirror.Size = new System.Drawing.Size(123, 20);
            this.chkRightMirror.TabIndex = 0;
            this.chkRightMirror.Text = "右后视镜选择";
            this.chkRightMirror.UseVisualStyleBackColor = true;
            // 
            // chkLeftMirror
            // 
            this.chkLeftMirror.AutoCheck = false;
            this.chkLeftMirror.AutoSize = true;
            this.chkLeftMirror.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.chkLeftMirror.Location = new System.Drawing.Point(31, 87);
            this.chkLeftMirror.Name = "chkLeftMirror";
            this.chkLeftMirror.Size = new System.Drawing.Size(123, 20);
            this.chkLeftMirror.TabIndex = 0;
            this.chkLeftMirror.Text = "左后视镜选择";
            this.chkLeftMirror.UseVisualStyleBackColor = true;
            // 
            // lblState
            // 
            this.lblState.BackColor = System.Drawing.Color.Black;
            this.lblState.Font = new System.Drawing.Font("华文细黑", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblState.ForeColor = System.Drawing.Color.Yellow;
            this.lblState.Location = new System.Drawing.Point(15, 9);
            this.lblState.Name = "lblState";
            this.lblState.Size = new System.Drawing.Size(582, 30);
            this.lblState.TabIndex = 0;
            this.lblState.Text = "待测试";
            this.lblState.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // FrmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(610, 729);
            this.Controls.Add(this.lblState);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.gbSerialPort);
            this.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.MaximizeBox = false;
            this.Name = "FrmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "LIN Tool V0.2";
            this.Load += new System.EventHandler(this.FrmMain_Load);
            this.gbSerialPort.ResumeLayout(false);
            this.gbSerialPort.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbSerialPort;
        private System.Windows.Forms.ComboBox cmbBaud;
        private System.Windows.Forms.ComboBox cmbPort;
        private System.Windows.Forms.Label lblPort;
        private System.Windows.Forms.Label lblBaud;
        private System.Windows.Forms.Button btnPortOpen;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox chkLEDRight;
        private System.Windows.Forms.CheckBox chkLEDLeft;
        private System.Windows.Forms.CheckBox chkLEDWinLock;
        private System.Windows.Forms.CheckBox chkLEDBCMLock;
        private System.Windows.Forms.Button btnAuto;
        private System.Windows.Forms.Button btnManual;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.CheckBox chkLeftMirror;
        private System.Windows.Forms.CheckBox chkRightMirror;
        private System.Windows.Forms.CheckBox chkMirrorUp;
        private System.Windows.Forms.CheckBox chkRRWinUp;
        private System.Windows.Forms.CheckBox chkRRWinDown;
        private System.Windows.Forms.CheckBox chkBCMUnlock;
        private System.Windows.Forms.CheckBox chkLFWinUp;
        private System.Windows.Forms.CheckBox chkLFWinDown;
        private System.Windows.Forms.CheckBox chkLRWinUp;
        private System.Windows.Forms.CheckBox chkLRWinDown;
        private System.Windows.Forms.CheckBox chkBCMLock;
        private System.Windows.Forms.CheckBox chkMirrorFold;
        private System.Windows.Forms.CheckBox chkWinLock;
        private System.Windows.Forms.CheckBox chkMirrorRight;
        private System.Windows.Forms.CheckBox chkMirrorLeft;
        private System.Windows.Forms.CheckBox chkMirrorDown;
        private System.Windows.Forms.CheckBox chkRFWinUp;
        private System.Windows.Forms.CheckBox chkRFWinDown;
        private System.Windows.Forms.Label lblState;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RadioButton rdoNo;
        private System.Windows.Forms.RadioButton radioButton1;
        private LEDLib.LEDControl ledTipOff;
        private System.Windows.Forms.Label lblLedTip;
        private LEDLib.LEDControl ledTipOn;
    }
}


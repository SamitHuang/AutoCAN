using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace LEDLib
{
    /// <summary>
    /// 初始化
    /// </summary>
    public partial class LEDControl : UserControl
    {
        public LEDControl()
        {
            InitializeComponent();

            // 设置控件属性,用户自定义绘制,双缓冲,调整大小重绘,选中重绘,支持透明
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            SetStyle(ControlStyles.ResizeRedraw, true);
            SetStyle(ControlStyles.Selectable, true);
            SetStyle(ControlStyles.SupportsTransparentBackColor, true);
            SetStyle(ControlStyles.UserPaint, true);
        }

        /// <summary>
        /// 使能LED双击是否有变色效果
        /// </summary>
        private bool ledClickEnable = true;
        [CategoryAttribute("状态"), Description("LED双击变色是否有效")]
        public bool LEDClickEnable
        {
            set { ledClickEnable = value; }
            get { return ledClickEnable; }
        }

        /// <summary>
        /// LED打开或者关闭
        /// </summary>
        private bool ledSwitch = true;
        [CategoryAttribute("状态"), Description("LED打开或关闭")]
        public bool LEDSwitch
        {
            set { ledSwitch = value; }
            get { return ledSwitch; }
        }

        /// <summary>
        /// LED中心颜色
        /// </summary>
        private Color ledCenterColor = Color.LightYellow;
        [CategoryAttribute("颜色"), Description("中心颜色")]
        public Color LEDCenterColor
        {
            set { ledCenterColor = value; }
            get { return ledCenterColor; }
        }

        /// <summary>
        /// LED边缘颜色
        /// </summary>
        private Color ledSurroundColor = Color.Yellow;
        [CategoryAttribute("颜色"), Description("边缘颜色")]
        public Color LEDSurroundColor
        {
            set { ledSurroundColor = value; }
            get { return ledSurroundColor; }
        }

        /// <summary>
        /// LED外环颜色
        /// </summary>
        private Color ledCircleColor = Color.Gray;
        [CategoryAttribute("颜色"), Description("外环颜色")]
        public Color LEDCircleColor
        {
            set { ledCircleColor = value; }
            get { return ledCircleColor; }
        }

        /// <summary>
        /// 绘制LED响应
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LEDControl_Paint(object sender, PaintEventArgs e)
        {
            int ledSize;
            Color centerColor;
            Color surroundColor;

            // 获取LED的大小,为正圆
            if (this.Width > this.Height)
            {
                ledSize = this.Height - 4;
            }
            else
            {
                ledSize = this.Width - 4;
            }

            // 设置GDI+模式为精细模式
            e.Graphics.SmoothingMode = SmoothingMode.HighQuality;

            // 获取要绘制的颜色
            if (ledSwitch)
            {
                centerColor = ledCenterColor;
                surroundColor = ledSurroundColor;
            }
            else
            {
                centerColor = Color.LightGray;
                surroundColor = Color.Gray;
            }

            // 创建一个变色圆形的区域
            GraphicsPath path = new GraphicsPath();
            path.AddEllipse(2, 2, ledSize, ledSize);

            PathGradientBrush pthGrBrush = new PathGradientBrush(path);

            // 设置中间颜色
            pthGrBrush.CenterColor = centerColor;

            // 设置边缘颜色
            Color[] colors = { surroundColor };
            pthGrBrush.SurroundColors = colors;

            // 绘制变色圆形
            e.Graphics.FillEllipse(pthGrBrush, 2, 2, ledSize, ledSize);

            // 绘制圆形边框
            Pen p = new Pen(new SolidBrush(ledCircleColor), 2);
            e.Graphics.DrawEllipse(p, 2, 2, ledSize, ledSize);

            // 控件区域为圆形
            GraphicsPath gp = new GraphicsPath();
            gp.AddEllipse(0, 0, (ledSize + 4), (ledSize + 4));
            this.Region = new Region(gp);//这句就是设置圆形的规格区域的 
        }

        /// <summary>
        /// 双击LED响应
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LEDControl_DoubleClick(object sender, EventArgs e)
        {
            if (ledClickEnable)
            {
                if (ledSwitch)
                    ledSwitch = false;
                else
                    ledSwitch = true;
                Invalidate();
            }
        }
    }
}

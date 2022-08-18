using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;

namespace GengleDemoApp
{
    internal class GengleHwndHost : HwndHost
    {
        private readonly GengleClient client = null;
        internal GengleHwndHost() : base()
        {
            this.client = new GengleClient();
        }
        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            IntPtr result = client.CreateNewWindow(hwndParent.Handle);
            client.InitializeOpengl(result);
            return new HandleRef(this, result);
        }

        protected override void OnRender(DrawingContext drawingContext)
        {
            this.client.Render();
        }

        protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo)
        {
            double m_dScaleX = 0.0, m_dScaleY = 0.0;
            this.client.GetScale(out m_dScaleX, out m_dScaleY);
            int iHeight = (int)(sizeInfo.NewSize.Height * m_dScaleY);
            int iWidth = (int)(sizeInfo.NewSize.Width * m_dScaleX);
            this.client.ChangeSize(iWidth, iHeight);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            this.client.Cleanup(hwnd.Handle);
        }
    }
}

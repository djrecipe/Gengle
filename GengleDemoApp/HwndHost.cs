using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Interop;

namespace GengleDemoApp
{
    internal class GengleHost : HwndHost
    {
        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            throw new NotImplementedException();
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
            throw new NotImplementedException();
        }
    }
}

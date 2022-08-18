using System;
using System.Windows.Interop;

namespace GengleDemoApp
{
    internal class GengleClient
    {
        public GengleClient()
        {
            NativeLibrary library = new NativeLibrary("GengleInterop.dll");
            GengleInterop.Initialize(library);
        }

        public void ChangeSize(double width, double height)
        {
            GengleInterop.ChangeSize(width, height);
        }
        public void Cleanup(IntPtr handle)
        {
            GengleInterop.Cleanup(handle);
        }
        public IntPtr CreateNewWindow(IntPtr parent)
        {
            IntPtr result= IntPtr.Zero;
            GengleInterop.CreateNewWindow(parent, out result);
            return result;
        }
        public void Demo()
        {
            GengleInterop.Demo();
        }

        public void GetScale(out double scale_x, out double scale_y)
        {
            GengleInterop.GetScale(out scale_x, out scale_y);
        }
    }
}

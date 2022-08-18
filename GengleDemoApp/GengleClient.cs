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
    }
}

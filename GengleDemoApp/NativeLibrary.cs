using System;
using System.Runtime.InteropServices;

namespace GengleDemoApp
{
    public class NativeLibrary : IDisposable
    {
        private readonly LibraryLoader _loader;
        public IntPtr Handle { get; }
        public NativeLibrary(string name)
        {
            _loader = LibraryLoader.GetPlatformDefaultLoader();
            Handle = _loader.LoadNativeLibrary(name);
        }
        public T LoadFunction<T>(string name)
        {
            IntPtr functionPtr = _loader.LoadFunctionPointer(Handle, name);
            if (functionPtr == IntPtr.Zero)
            {
                var lastWin32Error = Marshal.GetLastWin32Error();
                var exceptionForHr = Marshal.GetExceptionForHR(lastWin32Error);
                throw new InvalidOperationException($"No function was found with the name {name} with error code ({lastWin32Error}).", exceptionForHr);
            }

            var x =  Marshal.GetDelegateForFunctionPointer<T>(functionPtr);

            return x;


        }
        public T LoadFunction<T>()
        {
            return LoadFunction<T>(typeof(T).Name);
        }
        public IntPtr LoadFunction(string name)
        {
            return _loader.LoadFunctionPointer(Handle, name);
        }
        public void Dispose()
        {
            _loader.FreeNativeLibrary(Handle);
        }
    }
}

using System;
using System.Runtime.InteropServices;

namespace GengleDemoApp
{
    internal class GengleInterop
    {
        private static NativeLibrary libInterop;

        internal static void Initialize(NativeLibrary lib_interop)
        {
            if (lib_interop == null)
                throw new ArgumentNullException(nameof(lib_interop), "Invalid interop library");
            libInterop = lib_interop;
        }

        internal class UnmanagedDelegates
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void CreateNewWindow(IntPtr parent, out IntPtr result);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void Demo();

        }
        internal static void CreateNewWindow(IntPtr parent, out IntPtr result)
        {
            libInterop.LoadFunction<UnmanagedDelegates.CreateNewWindow>("CreateNewWindow")(parent, out result);
        }
        internal static void Demo()
        {
            libInterop.LoadFunction<UnmanagedDelegates.Demo>("Demo")();
            return;
        }
        
    }
}
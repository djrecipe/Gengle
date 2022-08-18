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
            internal delegate void ChangeSize(double width, double height);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void Cleanup(IntPtr handle);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void CreateNewWindow(IntPtr parent, out IntPtr result);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void Demo();
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void GetScale(out double scale_x, out double scale_y);
        }

        internal static void ChangeSize(double width, double height)
        {
            libInterop.LoadFunction<UnmanagedDelegates.ChangeSize>("ChangeSize")(width, height);
        }
        internal static void Cleanup(IntPtr handle)
        {
            libInterop.LoadFunction<UnmanagedDelegates.Cleanup>("Cleanup")(handle);
        }
        internal static void CreateNewWindow(IntPtr parent, out IntPtr result)
        {
            libInterop.LoadFunction<UnmanagedDelegates.CreateNewWindow>("CreateNewWindow")(parent, out result);
        }

        internal static void GetScale(out double scale_x, out double scale_y)
        {
            libInterop.LoadFunction<UnmanagedDelegates.GetScale>("GetScale")(out scale_x, out scale_y);
        }
        internal static void Demo()
        {
            libInterop.LoadFunction<UnmanagedDelegates.Demo>("Demo")();
            return;
        }
        
    }
}
using System;
using System.Runtime.InteropServices;

namespace GengleDemoApp
{
    internal static class Libdl
    {
        private const string LibName = "libdl";

        public const int RTLD_NOW = 0x002;

        [DllImport(LibName, SetLastError = true)]
        public static extern IntPtr dlopen(String fileName, int flags);

        [DllImport(LibName, SetLastError = true)]
        public static extern IntPtr dlsym(IntPtr handle, String name);

        [DllImport(LibName, SetLastError = true)]
        public static extern int dlclose(IntPtr handle);

        [DllImport(LibName, SetLastError = true)]
        public static extern IntPtr dlerror();
    }
    internal static class Libdl2
    {
        private const string LibName = "libdl.so.2";

        public const int RTLD_NOW = 0x002;

        [DllImport(LibName, SetLastError = true)]
        public static extern IntPtr dlopen(String fileName, int flags);

        [DllImport(LibName, SetLastError = true)]
        public static extern IntPtr dlsym(IntPtr handle, String name);

        [DllImport(LibName, SetLastError = true)]
        public static extern int dlclose(IntPtr handle);

        [DllImport(LibName, SetLastError = true)]
        public static extern IntPtr dlerror();
    }
}

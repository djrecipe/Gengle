using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Runtime.InteropServices;

namespace GengleDemoApp
{
    /// <summary>
    /// Exposes functionality for loading native libraries and function pointers.
    /// </summary>
    public abstract class LibraryLoader
    {
        /// <summary>
        /// Loads a native library by name and returns an operating system handle to it.
        /// </summary>
        /// <param name="name">The name of the library to open.</param>
        /// <returns>The operating system handle for the shared library.</returns>
        public IntPtr LoadNativeLibrary(string name)
        {
            IntPtr result = IntPtr.Zero;
            for (int i = 0; i < 2; i++)
            {
                try
                {
                    result = CoreLoadNativeLibrary(name);
                }
                catch
                {
                    // NOTE 7/21/22: the first time after using dlopen() followed by dlerror(), dlerror() doesn't return an error message, so we just try two times and our second attempt has proper error messages... 
                    // TODO 7/21/22: fix this nonsense and determine the correct order of operations for using dlopen() and dlerror() such that dlerror() properly returns an error message the first time invoked
                    if (i == 1)
                        throw;
                }
            }
            return result;
        }

        /// <summary>
        /// Loads a function pointer out of the given library by name.
        /// </summary>
        /// <param name="handle">The operating system handle of the opened shared library.</param>
        /// <param name="functionName">The name of the exported function to load.</param>
        /// <returns>A pointer to the loaded function.</returns>
        public IntPtr LoadFunctionPointer(IntPtr handle, string functionName)
        {
            if (string.IsNullOrEmpty(functionName))
            {
                throw new ArgumentException("Parameter must not be null or empty.", nameof(functionName));
            }

            return CoreLoadFunctionPointer(handle, functionName);
        }

        /// <summary>
        /// Frees the library represented by the given operating system handle.
        /// </summary>
        /// <param name="handle">The handle of the open shared library.</param>
        public void FreeNativeLibrary(IntPtr handle)
        {
            if (handle == IntPtr.Zero)
            {
                throw new ArgumentException("Parameter must not be zero.", nameof(handle));
            }

            CoreFreeNativeLibrary(handle);
        }
        public abstract string GetErrorMessage();
        /// <summary>
        /// Loads a native library by name and returns an operating system handle to it.
        /// </summary>
        /// <param name="name">The name of the library to open. This parameter must not be null or empty.</param>
        /// <returns>The operating system handle for the shared library.
        /// If the library cannot be loaded, IntPtr.Zero should be returned.</returns>
        protected abstract IntPtr CoreLoadNativeLibrary(string name);

        /// <summary>
        /// Frees the library represented by the given operating system handle.
        /// </summary>
        /// <param name="handle">The handle of the open shared library. This must not be zero.</param>
        protected abstract void CoreFreeNativeLibrary(IntPtr handle);

        /// <summary>
        /// Loads a function pointer out of the given library by name.
        /// </summary>
        /// <param name="handle">The operating system handle of the opened shared library. This must not be zero.</param>
        /// <param name="functionName">The name of the exported function to load. This must not be null or empty.</param>
        /// <returns>A pointer to the loaded function.</returns>
        protected abstract IntPtr CoreLoadFunctionPointer(IntPtr handle, string functionName);

        /// <summary>
        /// Returns a default library loader for the running operating system.
        /// </summary>
        /// <returns>A LibraryLoader suitable for loading libraries.</returns>
        public static LibraryLoader GetPlatformDefaultLoader()
        {
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                return new Win32LibraryLoader();
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                return new UnixLibraryLoader();
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                return new UnixLibraryLoader();
            }
            throw new PlatformNotSupportedException($"Invalid/unsupported platform for loading native libraries: {RuntimeInformation.OSDescription}");
        }

        private class Win32LibraryLoader : LibraryLoader
        {

            protected bool _IsVCRuntimeInstalled = false;
            protected bool IsVCRuntimeInstalled
            {
                get
                {
                    if (_IsVCRuntimeInstalled) { return true; }

                    //https://docs.microsoft.com/en-us/cpp/windows/redistributing-visual-cpp-files?view=msvc-170
                    //HKEY_LOCAL_MACHINE\SOFTWARE[\Wow6432Node]\Microsoft\VisualStudio\14.0\VC\Runtimes\{x86|x64|ARM}

                    try
                    {
                        var vcRedistKeyStr = @"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x64";

                        if (!Environment.Is64BitProcess)
                        {
                            // We're running as a 32-bit process, check if the OS is 64 or 32 bits
                            vcRedistKeyStr = Environment.Is64BitOperatingSystem ?
                                // 32-bit process on a 64-bit OS
                                @"HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\VisualStudio\14.0\VC\Runtimes\x86" :
                                // 32-bit process on a 32-bit OS
                                @"HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x86";
                        }

                        var vcRedistInstalled = Microsoft.Win32.Registry.GetValue(vcRedistKeyStr, "Installed", 0);

                        _IsVCRuntimeInstalled = (vcRedistInstalled != null && (int)vcRedistInstalled == 1);
                    }
                    catch (Exception e)
                    {
                    }

                    return _IsVCRuntimeInstalled;
                }
            }
            protected override void CoreFreeNativeLibrary(IntPtr handle)
            {
                Kernel32.FreeLibrary(handle);
            }

            protected override IntPtr CoreLoadFunctionPointer(IntPtr handle, string functionName)
            {
                return Kernel32.GetProcAddress(handle, functionName);
            }

            public override string GetErrorMessage()
            {
                string error = new Win32Exception(Marshal.GetLastWin32Error()).Message;
                return error;
            }

            protected override IntPtr CoreLoadNativeLibrary(string name)
            {
                if (!File.Exists(name))
                    throw new Exception($"Error while locating native library '{name}'");
                IntPtr library = IntPtr.Zero;
                try
                {

                    library = Kernel32.LoadLibrary(name);
                    if (library == IntPtr.Zero)
                    {
                        string error = GetErrorMessage();
                        throw new Exception(error);
                    }
                }
                catch (Exception e)
                {
                    if (!IsVCRuntimeInstalled)
                    {
                        var strBit = Environment.Is64BitProcess ? "64" : "32";
                        throw new Exception($"Visual C++ Runtime ({strBit} bit) for Windows may not be installed on this machine. It is required to load {name}.\n\nPlease visit https://support.microsoft.com/en-au/help/2977003/the-latest-supported-visual-c-downloads to download and run the free installer.", e);
                    }
                    else
                    {
                        throw e;
                    }
                }

                return library;
            }
        }

        private class UnixLibraryLoader : LibraryLoader
        {
            private bool use_libdl2 = false;
            // NOTE 7/21/22: some linux distros use libdl.so.2 instead of libdl.so
            private const string ERR_LIBDL = @"Unable to load shared library 'libdl' or one of its dependencies.";
            protected override void CoreFreeNativeLibrary(IntPtr handle)
            {
                if (use_libdl2)
                    Libdl2.dlclose(handle);
                else
                    Libdl.dlclose(handle);
                return;
            }

            protected override IntPtr CoreLoadFunctionPointer(IntPtr handle, string functionName)
            {
                IntPtr ptr = IntPtr.Zero;
                if (use_libdl2)
                    ptr = Libdl2.dlsym(handle, functionName);
                else
                    ptr = Libdl.dlsym(handle, functionName);
                return ptr;
            }

            public override string GetErrorMessage()
            {
                IntPtr error_ptr = IntPtr.Zero;
                // NOTE 7/21/22: it's possible for GetErrorMessage() to be set before use_libdl2 ever has the chance to be set
                if (use_libdl2)
                {
                    error_ptr = Libdl2.dlerror();
                }
                else
                {
                    try
                    {
                        error_ptr = Libdl.dlerror();
                    }
                    catch (Exception e)
                    {
                        // ignored
                        if (e.Message.Contains(ERR_LIBDL))
                            error_ptr = Libdl2.dlerror();
                        else
                            throw e;
                    }
                }
                string error = Marshal.PtrToStringAnsi(error_ptr);
                return error;
            }

            protected override IntPtr CoreLoadNativeLibrary(string name)
            {
                if (!File.Exists(name))
                    throw new Exception($"Error while locating native library '{name}'");
                IntPtr result = IntPtr.Zero;
                try
                {
                    result = Libdl.dlopen(name, Libdl.RTLD_NOW);
                }
                catch (Exception e)
                {
                    if (e.Message.Contains(ERR_LIBDL))
                    {
                        use_libdl2 = true;
                        result = Libdl2.dlopen(name, Libdl2.RTLD_NOW);
                    }
                    else
                        throw e;
                }
                if (result == IntPtr.Zero)
                {
                    var error = GetErrorMessage();
                    throw new Exception(error);
                }
                return result;
            }
        }
    }
}
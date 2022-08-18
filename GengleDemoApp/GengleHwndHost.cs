using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Interop;

namespace GengleDemoApp
{
    internal class GengleHwndHost : HwndHost
    {
        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            GengleClient client = new GengleClient();
            IntPtr result = client.CreateNewWindow(hwndParent.Handle);
            return new HandleRef(this, result);
    //        // Get HINSTANCE
    //        m_hInstance = (HINSTANCE)GetModuleHandle(NULL);
    //        m_sWindowName = L"OpenGL in HwndHost";
    //        m_sClassName = L"OGLClassHwnd";

    //        if (RegisterWindowClass())
    //        {
    //            // some default size
    //            int iWidth = 2;
    //            int iHeight = 2;

    //            DWORD dwStyle = WS_CHILD | WS_VISIBLE;

    //            // Get the parent (WPF) Hwnd. This is important: Windows won't let you create
    //            // the Hwnd otherwise.
    //            HWND parentHwnd = (HWND)hwndParent.Handle.ToPointer();

    //            m_hWnd = CreateWindowEx(0,
    //                m_sClassName,
    //                m_sWindowName,
    //                dwStyle,
    //                0,  // X Pos
    //                0,  // Y Pos
    //                iWidth,
    //                iHeight,
    //                parentHwnd, // Parent
    //                0,  // Menu
    //                m_hInstance,
    //                0); // Param

    //            if (!m_hWnd)
    //            {
    //                Helper::ErrorExit(L"BuildWindowCore");
    //            }

    //            m_hDC = GetDC(m_hWnd);
    //            if (!m_hDC)
    //            {
    //                Helper::ErrorExit(L"BuildWindowCore");
    //            }

    //            //
    //            // Create PixelFormatDescriptor and choose pixel format
    //            //
    //            uint PixelFormat;

    //            BYTE iAlphaBits = 0;
    //            BYTE iColorBits = 32;
    //            BYTE iDepthBits = 16;
    //            BYTE iAccumBits = 0;
    //            BYTE iStencilBits = 0;

    //            static PIXELFORMATDESCRIPTOR pfd =
    //            {
    //                sizeof(PIXELFORMATDESCRIPTOR),	//size
				//	1,								//version
				//	PFD_DRAW_TO_WINDOW |				//flags
				//	PFD_SUPPORT_OPENGL |
    //                PFD_DOUBLEBUFFER,
    //                PFD_TYPE_RGBA,					//pixeltype
				//	iColorBits,
    //                0, 0, 0, 0, 0, 0,				//color bits ignored
				//	iAlphaBits,
    //                0,								//alpha shift ignored
				//	iAccumBits,						//accum. buffer
				//	0, 0, 0, 0,						//accum bits ignored
				//	iDepthBits,						//depth buffer
				//	iStencilBits,					//stencil buffer
				//	0,								//aux buffer
				//	PFD_MAIN_PLANE,					//layer type
				//	0,								//reserved
				//	0, 0, 0							//masks ignored
				//};

    //            PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
    //            if (!PixelFormat)
    //            {
    //                Helper::ErrorExit(L"BuildWindowCore");
    //            }

    //            if (!SetPixelFormat(m_hDC, PixelFormat, &pfd))
    //            {
    //                Helper::ErrorExit(L"BuildWindowCore");
    //            }

    //            m_hRC = wglCreateContext(m_hDC);
    //            if (!m_hRC)
    //            {
    //                Helper::ErrorExit(L"BuildWindowCore");
    //            }

    //            if (!wglMakeCurrent(m_hDC, m_hRC))
    //            {
    //                Helper::ErrorExit(L"BuildWindowCore");
    //            }

    //            //
    //            // Get DPI information and store scaling relative to 96 DPI.
    //            // See http://msdn2.microsoft.com/en-us/library/ms969894.aspx
    //            //
    //            m_dScaleX = GetDeviceCaps(m_hDC, LOGPIXELSX) / 96.0;
    //            m_dScaleY = GetDeviceCaps(m_hDC, LOGPIXELSY) / 96.0;

    //            glEnable(GL_DEPTH_TEST);
    //            glDisable(GL_TEXTURE_2D);

    //            return HandleRef(this, IntPtr(m_hWnd));
    //        }

    //        return HandleRef(nullptr, System::IntPtr::Zero);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {
        }
    }
}

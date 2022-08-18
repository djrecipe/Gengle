#include "WindowManager.h"
using namespace std;
namespace Gengle
{
HGLRC WindowManager::m_hRC;
HDC WindowManager::m_hDC;
void WindowManager::SetGlContext(HWND hwnd)
{
	m_hDC = GetDC(hwnd);

	BYTE iAlphaBits = 0;
	BYTE iColorBits = 32;
	BYTE iDepthBits = 16;
	BYTE iAccumBits = 0;
	BYTE iStencilBits = 0;

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	//size
		1,								//version
		PFD_DRAW_TO_WINDOW |				//flags
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,					//pixeltype
		iColorBits,
		0, 0, 0, 0, 0, 0,				//color bits ignored
		iAlphaBits,
		0,								//alpha shift ignored
		iAccumBits,						//accum. buffer
		0, 0, 0, 0,						//accum bits ignored
		iDepthBits,						//depth buffer
		iStencilBits,					//stencil buffer
		0,								//aux buffer
		PFD_MAIN_PLANE,					//layer type
		0,								//reserved
		0, 0, 0							//masks ignored
	};

	glm::uint PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, PixelFormat, &pfd);
	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);
}
void WindowManager::ChangeSize(double width, double height)
{
	wglMakeCurrent(m_hDC, m_hRC);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	// gluPerspective( 67.5, ((double)(iWidth) / (double)(iHeight)), 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//glClear(GL_COLOR_BUFFER_BIT);
}

void WindowManager::Cleanup(HWND handle)
{
	if (NULL != m_hRC)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}

	if (NULL != handle && NULL != m_hDC)
	{
		ReleaseDC(handle, m_hDC);
		m_hDC = NULL;
	}

	if (NULL != handle)
	{
		::DestroyWindow(handle);
		handle = NULL;
	}

	wstring m_sClassName = L"OGLClassHwnd";
	HINSTANCE m_hInstance = (HINSTANCE)GetModuleHandle(NULL);
	UnregisterClass(m_sClassName.c_str(), m_hInstance);
}

HWND WindowManager::CreateNewWindow(HWND parent)
{
	HINSTANCE m_hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wstring m_sWindowName = L"OpenGL in HwndHost";
	wstring m_sClassName = L"OGLClassHwnd";
	WindowManager::RegisterWindowClass(m_hInstance, m_sClassName.c_str());
	DWORD dwStyle = WS_CHILD | WS_VISIBLE;
	int iWidth = 200;
	int iHeight = 200;
	HWND m_hWnd = CreateWindowEx(0,
		m_sClassName.c_str(),
		m_sWindowName.c_str(),
		dwStyle,
		0,  // X Pos
		0,  // Y Pos
		iWidth,
		iHeight,
		parent, // Parent
		0,  // Menu
		m_hInstance,
		0); // Param
	return m_hWnd;
}
void WindowManager::ErrorExit(LPCTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	::MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}
void WindowManager::GetScale(double& scale_x, double& scale_y)
{
	scale_x = GetDeviceCaps(m_hDC, LOGPIXELSX) / 96.0;
	scale_x = GetDeviceCaps(m_hDC, LOGPIXELSY) / 96.0;
}

LRESULT WINAPI WindowManager::MyMsgProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_msg)
	{
		// Make sure the window gets focus when it has to!
	case WM_IME_SETCONTEXT:
		// LOWORD(wParam) = 0 stands for deactivation, so don't set
		// focus then (results in a rather, err... 'greedy' window...)
		if (LOWORD(_wParam) > 0)
			SetFocus(_hWnd);

		return 0;

	default:
		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
	}
}
bool WindowManager::RegisterWindowClass(HINSTANCE m_hInstance, LPCWSTR m_sClassName)
{
	//
	// Create custom WNDCLASS
	//
	WNDCLASS wndClass;

	if (GetClassInfo(m_hInstance, m_sClassName, &wndClass))
	{
		// Class is already registered!
		return true;
	}

	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	// Not providing a WNDPROC here results in a crash on my system:
	wndClass.lpfnWndProc = (WNDPROC)MyMsgProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.hbrBackground = 0;
	wndClass.lpszMenuName = 0; // No menu
	wndClass.lpszClassName = m_sClassName;

	// ... and register it
	if (!RegisterClass(&wndClass))
	{
		ErrorExit(L"RegisterWindowClass");
		return false;
	}

	return true;
}
}
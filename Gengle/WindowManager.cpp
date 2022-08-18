#include "WindowManager.h"
using namespace std;
namespace Gengle
{
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
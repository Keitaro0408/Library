/**
 * @file   Window.h
 * @brief  Windowクラスの実装
 * @author kotani
 */
#include "Window.h"


Lib::Window::Window() : 
m_hWnd(NULL)
{
}

Lib::Window::~Window()
{
}

HRESULT Lib::Window::InitWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName)
{
	// ウィンドウの定義
	WNDCLASSEX  windowClass;
	ZeroMemory(&windowClass, sizeof(windowClass));
	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = _hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	windowClass.lpszClassName = TEXT(_windowName);
	windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&windowClass);

	//ウィンドウの作成
	m_hWnd = CreateWindow(_windowName, _windowName, WS_OVERLAPPEDWINDOW,
		0, 0, _width, _height, 0, 0, _hInstance, 0);
	if (!m_hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT Lib::Window::InitWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName, LPCTSTR _iconName)
{
	// ウィンドウの定義
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = _hInstance;
	//アイコン読み込み
	wc.hIcon = (HICON)LoadImage(NULL, _iconName, IMAGE_ICON, 0, 0, LR_SHARED | LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = _windowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	m_hWnd = CreateWindow(_windowName, _windowName, WS_OVERLAPPEDWINDOW,
		0, 0, _width, _height, 0, 0, _hInstance, 0);
	if (!m_hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

LRESULT CALLBACK Lib::Window::WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYDOWN:
		switch (static_cast<CHAR>(_wParam))
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		}
		break;
	}

	return DefWindowProc(_hwnd, _message, _wParam, _lParam);
}


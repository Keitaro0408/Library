/**
 * @file   Window.h
 * @brief  Windowクラスの実装
 * @author kotani
 */
#include "Window.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

HRESULT Lib::Window::DispWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName, LRESULT CALLBACK _wndProc(HWND, UINT, WPARAM, LPARAM))
{
	m_hInstance = _hInstance;

	// ウィンドウの定義
	WNDCLASSEX  Wndclass;
	ZeroMemory(&Wndclass, sizeof(Wndclass));
	Wndclass.cbSize = sizeof(Wndclass);
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = _wndProc;
	Wndclass.hInstance = _hInstance;
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszClassName = TEXT(_windowName);
	Wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wndclass);

	
	//ウィンドウの作成
	m_hWnd = CreateWindow(
		_windowName,
		_windowName,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_VISIBLE,
		0,
		0,
		_width,
		_height,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!m_hWnd)
	{
		return E_FAIL;
	}

	RECT rw, rc;
	GetWindowRect(m_hWnd, &rw); // ウィンドウ全体のサイズ
	GetClientRect(m_hWnd, &rc); // クライアント領域のサイズ

	int new_width = (rw.right - rw.left) - (rc.right - rc.left) + _width;
	int new_height = (rw.bottom - rw.top) - (rc.bottom - rc.top) + _height;

	SetWindowPos(m_hWnd, NULL, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER);
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

HRESULT Lib::Window::DispWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName, LPCTSTR _iconName, LRESULT CALLBACK _wndProc(HWND, UINT, WPARAM, LPARAM))
{
	m_hInstance = _hInstance;

	// ウィンドウの定義
	WNDCLASSEX  Wndclass;
	ZeroMemory(&Wndclass, sizeof(Wndclass));
	Wndclass.cbSize = sizeof(Wndclass);
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;
	Wndclass.lpfnWndProc = _wndProc;
	Wndclass.hInstance = _hInstance;
	//アイコン読み込み
	Wndclass.hIcon = (HICON)LoadImage(NULL, _iconName, IMAGE_ICON, 0, 0, LR_SHARED | LR_LOADFROMFILE);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wndclass.lpszClassName = _windowName;
	Wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wndclass);

	//ウィンドウの作成
	m_hWnd = CreateWindow(
		_windowName,
		_windowName,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_VISIBLE,
		0,
		0,
		_width,
		_height,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!m_hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

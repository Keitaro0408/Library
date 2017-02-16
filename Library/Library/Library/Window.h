/**
 * @file   Window.h
 * @brief  Windowクラスのヘッダファイル
 * @author kotani
 */
#ifndef WINDOW_H
#define WINDOW_H
#include <windows.h>

namespace Lib
{
	class Window
	{
	public:
		inline static Window* GetInstance()
		{
			static Window Instance;
			return &Instance;
		}

		inline HWND GetWindowHandle() const
		{
			return m_hWnd;
		}

		/**
		 * ウィンドウの生成
		 * @param[in] _hInstance インスタンスハンドル
		 * @param[in] _width ウィンドウの横幅
		 * @param[in] _height ウィンドウの縦幅
		 * @param[in] _windowName ウィンドウの名前
		 * @return 成功したらS_OK
		 */
		HRESULT InitWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName);

		/**
		 * ウィンドウの生成(アイコンあり)
		 * @param[in] _hInstance インスタンスハンドル
		 * @param[in] _width ウィンドウの横幅
		 * @param[in] _height ウィンドウの縦幅
		 * @param[in] _windowName ウィンドウの名前
		 * @param[in] _iconName アイコンのパス
		 * @return 成功したらS_OK
		 */
		HRESULT InitWindow(HINSTANCE _hInstance, INT _width, INT _height, LPCTSTR _windowName, LPCTSTR _iconName);

	private:
		Window();
		~Window();

		static LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
		HWND m_hWnd;

	};
}


#endif

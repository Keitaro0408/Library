#include <crtdbg.h>
#include <stdio.h>
#include <thread>
#include <Library\Window\Window.h>
#include <Library\Dx11\DX11Manager.h>
#include <Library\Sound\DSoundManager.h>
#include <Library\Singleton.h>
#include <Library\DxInput\DXInputDevice.h>
#include <Library\Texture\TextureManager.h>

#include "SceneManager.h"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define FULLSCREEN 0

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

void Init(HWND _hWnd)
{
	//Directx11関係
	SINGLETON_CREATE(Lib::DX11Manager);
	SINGLETON_INSTANCE(Lib::DX11Manager).Init(_hWnd);

	//DirectSound関係
	SINGLETON_CREATE(Lib::DSoundManager);
	SINGLETON_INSTANCE(Lib::DSoundManager).Init(_hWnd);

	//テクスチャ
	SINGLETON_CREATE(Lib::TextureManager);
	SINGLETON_INSTANCE(Lib::TextureManager).
		Init(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice());

	//DirectInput関係
	SINGLETON_CREATE(Lib::DXInputDevice);
	SINGLETON_INSTANCE(Lib::DXInputDevice).Init(_hWnd);

	SINGLETON_CREATE(Lib::MouseDevice);
	SINGLETON_INSTANCE(Lib::MouseDevice).Init(
		SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), _hWnd);

	SINGLETON_CREATE(Lib::KeyDevice);
	SINGLETON_INSTANCE(Lib::KeyDevice).Init(
		SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), _hWnd);
}

void Exit()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Release();
	SINGLETON_DELETE(Lib::KeyDevice);

	SINGLETON_INSTANCE(Lib::MouseDevice).Release();
	SINGLETON_DELETE(Lib::MouseDevice);

	SINGLETON_INSTANCE(Lib::DXInputDevice).Release();
	SINGLETON_DELETE(Lib::DXInputDevice);

	SINGLETON_DELETE(Lib::TextureManager);

	SINGLETON_INSTANCE(Lib::DSoundManager).Release();
	SINGLETON_DELETE(Lib::DSoundManager);

	SINGLETON_INSTANCE(Lib::DX11Manager).Release();
	SINGLETON_DELETE(Lib::DX11Manager);
	SINGLETON_DELETE(Lib::Window);
}

//----------------------------------------------------------------------------------------------------
//
// テスト用プロジェクト
//
//----------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Window表示
	SINGLETON_CREATE(Lib::Window);
	SINGLETON_INSTANCE(Lib::Window).DispWindow(hInst, WINDOW_WIDTH, WINDOW_HEIGHT, "test", &WindowProc);
	HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();
	Init(hWnd);

#if FULLSCREEN
	SINGLETON_INSTANCE(Lib::DX11Manager).SetFullScreenState(true);
#else
	SINGLETON_INSTANCE(Lib::DX11Manager).SetFullScreenState(false);
#endif

	SceneManager* sceneManager = new SceneManager(hWnd);

	MSG Msg;
	ZeroMemory(&Msg, sizeof(Msg));
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			if (sceneManager->Run())
			{
				break;
			}
		}
	}

	delete sceneManager;
	Exit();

	return (INT)Msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
	switch (_message)
	{
	case WM_CLOSE:
		if (MessageBox(_hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(_hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	case WM_KEYDOWN:
		switch (static_cast<CHAR>(_wParam))
		{
		case VK_ESCAPE:
			if (MessageBox(_hwnd, TEXT("終わりますか？"), TEXT("終了"), MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DestroyWindow(_hwnd);
			}
			break;
		}
		break;
	default: 
		return DefWindowProc(_hwnd, _message, _wParam, _lParam);
	}
	return 0;
}

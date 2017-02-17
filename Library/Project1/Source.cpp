#include <crtdbg.h>
#include <stdio.h>
#include <Library\Window.h>
#include <Library\DX11Manager.h>
#include <Library\DSound.h>
#include <Library\SoundContainer.h>
#include <Library\SingletonWrapper.h>
#include <Library\DXInputDevice.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

//----------------------------------------------------------------------------------------------------
//
// テスト用プロジェクト
//
//----------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int soundIndex = 0;
	int volume = 0;
	HWND hWnd = NULL;

	//Window表示
	SINGLETON_CREATE(Lib::Window);
	SINGLETON_INSTANCE(Lib::Window).DispWindow(hInst, WINDOW_WIDTH, WINDOW_HEIGHT, "test", &WindowProc);
	hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();
	
	//Directx11
	SINGLETON_CREATE(Lib::DX11Manager);
	SINGLETON_INSTANCE(Lib::DX11Manager).Init(hWnd);

	//DirectSound
	SINGLETON_CREATE(Lib::DSound);
	SINGLETON_INSTANCE(Lib::DSound).Init(hWnd);

	//SoundContainer
	SINGLETON_CREATE(Lib::SoundContainer);
	SINGLETON_INSTANCE(Lib::SoundContainer).Init(hWnd, SINGLETON_INSTANCE(Lib::DSound).GetIDSound());
	SINGLETON_INSTANCE(Lib::SoundContainer).LoadSound("test.wav", &soundIndex);

	//再生
	SINGLETON_INSTANCE(Lib::DSound).SoundOperation(SINGLETON_INSTANCE(Lib::SoundContainer).GetSound(soundIndex), Lib::SOUND_PLAY);

	//DirectInput関係
	SINGLETON_CREATE(Lib::DXInputDevice);
	SINGLETON_INSTANCE(Lib::DXInputDevice).Init(hWnd);

	SINGLETON_CREATE(Lib::MouseDevice);
	SINGLETON_INSTANCE(Lib::MouseDevice).Init(SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(),hWnd);

	SINGLETON_CREATE(Lib::KeyDevice);
	SINGLETON_INSTANCE(Lib::KeyDevice).Init(SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), hWnd);

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
			//メインループ
			SINGLETON_INSTANCE(Lib::MouseDevice).Update();
			SINGLETON_INSTANCE(Lib::KeyDevice).Update();
			SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_W);
			SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_S);

			if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_W] == Lib::KEY_RELEASE)
			{
				volume++;
			}
			if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_S] == Lib::KEY_ON)
			{
				volume--;
			}

			if (SINGLETON_INSTANCE(Lib::MouseDevice).GetMouseState().rgbButtons[Lib::MOUSEBUTTON_LEFT] == Lib::MOUSEBUTTON_ON)
			{
				volume--;
			}

			SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
			SINGLETON_INSTANCE(Lib::DSound).SetVolume(SINGLETON_INSTANCE(Lib::SoundContainer).GetSound(soundIndex), volume);
			SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
		}
	}

	SINGLETON_INSTANCE(Lib::KeyDevice).Release();
	SINGLETON_DELETE(Lib::KeyDevice);

	SINGLETON_INSTANCE(Lib::MouseDevice).Release();
	SINGLETON_DELETE(Lib::MouseDevice);

	SINGLETON_INSTANCE(Lib::DXInputDevice).Release();
	SINGLETON_DELETE(Lib::DXInputDevice);

	SINGLETON_INSTANCE(Lib::SoundContainer).ReleaseSound(soundIndex);
	SINGLETON_INSTANCE(Lib::SoundContainer).ClearBuffer();
	SINGLETON_DELETE(Lib::SoundContainer);

	SINGLETON_INSTANCE(Lib::DSound).Release();
	SINGLETON_DELETE(Lib::DSound);

	SINGLETON_INSTANCE(Lib::DX11Manager).Release();
	SINGLETON_DELETE(Lib::DX11Manager);

	SINGLETON_DELETE(Lib::Window);

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

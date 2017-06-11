/**
 * @file   ApplicationBase.cpp
 * @brief  ApplicationBaseクラスの実装
 * @author kotani
 */
#include <crtdbg.h>
#include "ApplicationBase.h"
#include "../Window/Window.h"
#include "../Dx11/DX11Manager.h"
#include "../Sound/DSoundManager.h"
#include "../DxInput/DXInputDevice.h"
#include "../Texture/TextureManager.h"
#include "../Application/ApplicationBase.h"

Lib::ApplicationBase* Lib::ApplicationBase::m_pInstance = nullptr;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SINGLETON_CREATE(Lib::Window);

	SINGLETON_INSTANCE(Lib::Window).Init(hInst);

	Lib::ApplicationBase::m_pInstance->Init();
	Lib::ApplicationBase::m_pInstance->InitLib();

	return Lib::ApplicationBase::m_pInstance->Boot();
}


namespace Lib
{
	ApplicationBase::ApplicationBase()
	{
		m_pInstance = this;
	}

	ApplicationBase::~ApplicationBase(void)
	{
		ReleaseLib();
		SINGLETON_DELETE(Lib::Window);
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	int ApplicationBase::Boot()
	{
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
				if (MainLoop())
				{
					break;
				}
			}
		}
		/* 先にサブクラスからデストラクタが実行されるのでここで解放する */
		Release();
		return 0;
	}

	void ApplicationBase::InitLib()
	{
		HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();

		//Directx11関係
		SINGLETON_CREATE(Lib::DX11Manager);
		SINGLETON_INSTANCE(Lib::DX11Manager).Init(hWnd,
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

		//DirectSound関係
		SINGLETON_CREATE(Lib::DSoundManager);
		SINGLETON_INSTANCE(Lib::DSoundManager).Init(hWnd);

		//テクスチャ
		SINGLETON_CREATE(Lib::TextureManager);
		SINGLETON_INSTANCE(Lib::TextureManager).
			Init(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice());

		//DirectInput関係
		SINGLETON_CREATE(Lib::DXInputDevice);
		SINGLETON_INSTANCE(Lib::DXInputDevice).Init(hWnd);

		SINGLETON_CREATE(Lib::MouseDevice);
		SINGLETON_INSTANCE(Lib::MouseDevice).Init(
			SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), hWnd);

		SINGLETON_CREATE(Lib::KeyDevice);
		SINGLETON_INSTANCE(Lib::KeyDevice).Init(
			SINGLETON_INSTANCE(Lib::DXInputDevice).GetInputDevice(), hWnd);
	}

	void ApplicationBase::ReleaseLib()
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
}


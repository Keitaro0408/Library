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
#include "../Shader/ShaderManager.h"
#include "../Event/EventManager.h"
#include "../TaskManager/TaskManager.h"
#include "../XInput/XInput.h"

Lib::ApplicationBase* Lib::ApplicationBase::m_pInstance = nullptr;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return Lib::ApplicationBase::GetInstance()->Boot();
}

namespace Lib
{
	ApplicationBase::ApplicationBase(LPCTSTR _appName, int _windowWidth, int _windowHeight) :
		m_AppName(_appName),
		m_WindowWidth(_windowWidth),
		m_WindowHeight(_windowHeight)
	{
		m_pInstance = this;
	}

	ApplicationBase::~ApplicationBase()
	{
		SINGLETON_DELETE(Lib::Window);
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	int ApplicationBase::Boot()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		SINGLETON_CREATE(Lib::Window);
		SINGLETON_INSTANCE(Lib::Window).DispWindow(m_WindowWidth,m_WindowHeight, m_AppName);

		InitLib();
		Init();

		MSG Msg;
		ZeroMemory(&Msg, sizeof(Msg));
		while (Msg.message != WM_QUIT)
		{
			if (PeekMessage(&Msg, nullptr, 0U, 0U, PM_REMOVE))
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
		ReleaseLib();
		return 0;
	}

	void ApplicationBase::InitLib()
	{
		HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();
		SINGLETON_CREATE(Lib::EventManager);
		SINGLETON_CREATE(Lib::TaskManager);
		
		SINGLETON_CREATE(Lib::XInput);

		//Directx11関係
		SINGLETON_CREATE(Lib::DX11Manager);
		SINGLETON_INSTANCE(Lib::DX11Manager).Init(hWnd,
			SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

		SINGLETON_CREATE(Lib::ShaderManager);
		SINGLETON_INSTANCE(Lib::ShaderManager).Init(
			SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice());

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

		SINGLETON_DELETE(Lib::ShaderManager);

		SINGLETON_INSTANCE(Lib::DX11Manager).Release();
		SINGLETON_DELETE(Lib::DX11Manager);

		SINGLETON_DELETE(Lib::XInput);

		SINGLETON_DELETE(Lib::TaskManager);

		SINGLETON_DELETE(Lib::EventManager);

		SINGLETON_DELETE(Lib::Window);
	}
}


#include "App.h"
#include "Library/Application/ApplicationBase.h"
#include "Library/Window/Window.h"
#include "SceneManager.h"


void App::Init()
{
	SINGLETON_INSTANCE(Lib::Window).DispWindow(1280,720,TEXT("test"));
	HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();
	InitLib(hWnd);
	m_pSceneManager = new SceneManager(hWnd);
}

void App::Release()
{
	delete m_pSceneManager;
	m_pSceneManager = NULL;
	ReleaseLib();
}

bool App::MainLoop()
{
	if (m_pSceneManager->Run())
	{
		return true;
	}
	return false;
}
App theApp;

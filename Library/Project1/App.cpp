#include "App.h"
#include "Library/Application/ApplicationBase.h"
#include "Library/Window/Window.h"
#include "SceneManager.h"

App theApp;

void App::Init()
{
	SINGLETON_INSTANCE(Lib::Window).DispWindow(1280, 720, "test");
	HWND hWnd = SINGLETON_INSTANCE(Lib::Window).GetWindowHandle();
	m_pSceneManager = new SceneManager(hWnd);
}

void App::Release()
{
	delete m_pSceneManager;
	m_pSceneManager = NULL;
}

bool App::MainLoop()
{
	if (m_pSceneManager->Run())
	{
		return true;
	}
	return false;
}

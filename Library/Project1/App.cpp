#include "App.h"
#include "Library/Application/ApplicationBase.h"
#include "Library/Window/Window.h"
#include "Library\Helper\Helper.h"

void App::Initialize()
{
	m_pGameScene = new GameScene();
	m_pTitleScene = new TitleScene();

	SINGLETON_INSTANCE(Lib::SceneManager).AddScene(m_pGameScene);
	SINGLETON_INSTANCE(Lib::SceneManager).AddScene(m_pTitleScene);
	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");

}

void App::Finalize()
{
	Lib::SafeDelete(m_pTitleScene);
	Lib::SafeDelete(m_pGameScene);
}

#include "App.h"
#include "Library/Application/ApplicationBase.h"
#include "Library/Window/Window.h"
#include "Library\Helper\Helper.h"
#include <memory>
#include <vector>
#include <assert.h>

void App::Initialize()
{
	m_pGameScene = Lib::MakeUnique<GameScene>();
	m_pTitleScene = Lib::MakeUnique<TitleScene>();

	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");
}

void App::Finalize()
{
}

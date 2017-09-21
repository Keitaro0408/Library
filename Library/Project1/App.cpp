#include "App.h"
#include "Library/Application/ApplicationBase.h"
#include "Library/Window/Window.h"
#include "Library\Helper\Helper.h"
#include <memory>
#include <vector>
#include <assert.h>

class Test
{
public:
	Test()
	{
		int test = 0;
	}

	Test(Test && o)
	{
		int test = 0;
	}

	~Test()
	{
		int test = 0;
	}

	void func()
	{
		assert(true);
	}
};

void App::Initialize()
{
	m_pGameScene = Lib::MakeUnique<GameScene>();
	m_pTitleScene = Lib::MakeUnique<TitleScene>();

	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");
}

void App::Finalize()
{
	m_pTitleScene->Finalize();
	m_pGameScene->Finalize();
}

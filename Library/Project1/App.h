#ifndef APP_H
#define APP_H
#include "Library/Application/ApplicationBase.h"
#include "Library\SceneManager\SceneManager.h"
#include "Library\SmartPointer\UniquePtr.h"
#include "GameScene\GameScene.h"
#include "TitleScene\TitleScene.h"

class App : public Lib::ApplicationBase
{
public:
	App() :
		ApplicationBase("test",1280, 720)
	{};
	~App() = default;

	void Initialize() override;
	void Finalize() override;

private:
	Lib::UniquePtr<TitleScene> m_pTitleScene;
	Lib::UniquePtr<Lib::SceneBase> m_pGameScene;

} theApp;



#endif

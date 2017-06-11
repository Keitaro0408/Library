#ifndef APP_H
#define APP_H
#include "Library/Application/ApplicationBase.h"
#include "SceneManager.h"

class App : public Lib::ApplicationBase
{
public:
	App() = default;
	~App() = default;

	bool MainLoop() override;

	void Init() override;

	void Release() override;

private:
	SceneManager* m_pSceneManager;

};



#endif

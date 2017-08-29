/**
 * @file TitleScene.cpp
 * @brief TitleSceneクラス実装
 * @author kotani
 */
#include "TitleScene.h"
#include "Library\Dx11\DX11Manager.h"

TitleScene::TitleScene() :
SceneBase("TitleScene")
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Execute()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();
}

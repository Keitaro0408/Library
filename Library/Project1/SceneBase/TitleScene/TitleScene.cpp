/**
 * @file TitleScene.cpp
 * @brief TitleSceneクラス実装
 * @author kotani
 */
#include "TitleScene.h"
#include <Library\DSoundContainer.h>
#include <Library\DSoundLoader.h>


TitleScene::TitleScene() :
SceneBase(SCENE_TITLE)
{
}

TitleScene::~TitleScene()
{
}

SceneBase::SceneID TitleScene::Control()
{
	SceneID NextSceneID = m_SceneID;

	NextSceneID = SCENE_GAME;
	return NextSceneID;
}

void TitleScene::Draw()
{
}

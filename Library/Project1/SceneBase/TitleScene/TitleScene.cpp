/**
 * @file TitleScene.cpp
 * @brief TitleSceneクラス実装
 * @author kotani
 */
#include "TitleScene.h"


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

	return NextSceneID;
}

void TitleScene::Draw()
{
}

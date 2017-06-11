/**
 * @file   GameScene.h
 * @brief  GameSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "..\SceneBase.h"
#include <Library\Vertex2D\Vertex2D.h>
#include <Library\Animation\AnimUvController.h>

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public SceneBase
{
public:
	/**
	 * GameSceneのコンストラクタ
	 */
	GameScene();

	/**
	 * GameSceneのデストラクタ
	 */
	virtual ~GameScene();

	/**
	 * GameSceneの制御関数
	 * @return シーンの遷移先ID
	 */
	virtual SceneID Update();

	/**
	 * GameSceneの描画関数
	 */
	virtual void Draw();

private:
	GameScene(const GameScene&);
	void operator=(const GameScene&);

	int m_SoundIndex;
	int m_TextureIndex;
	Lib::Vertex2D* m_Vertex;
	Lib::AnimUvController* m_Animation;

};


#endif

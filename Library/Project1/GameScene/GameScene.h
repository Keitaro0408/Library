/**
 * @file   GameScene.h
 * @brief  GameSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <Library/SceneManager/SceneBase/SceneBase.h>
#include <Library\Vertex2D\Vertex2D.h>
#include <Library\Animation\AnimUvController.h>
#include "Library/SmartPointer/UniquePtr.h"

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public Lib::SceneBase
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

	virtual bool Initialize();
	virtual void Finalize();

	virtual void Execute();


private:
	GameScene(const GameScene&);
	void operator=(const GameScene&);

	int m_SoundIndex;
	int m_TextureIndex;
	Lib::UniquePtr<Lib::Vertex2D>		  m_Vertex;
	Lib::UniquePtr<Lib::AnimUvController> m_Animation;

};


#endif

/**
 * @file TitleScene.h
 * @brief TitleSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef TITLESCENE_H
#define TITLESCENE_H
#include <Library/SceneManager/SceneBase/SceneBase.h>
#include "Math.h"


/**
 * タイトルシーンを管理するクラス
 */
class TitleScene : public Lib::SceneBase
{
public:
	/**
	 * TitleSceneのコンストラクタ
	 */
	TitleScene();

	/**
	 * TitleSceneのデストラクタ
	 */
	virtual ~TitleScene();

	virtual bool Initialize(){ return true; }
	virtual void Finalize(){}

	virtual void Execute();

private:
	TitleScene(const TitleScene&);
	void operator=(const TitleScene&);
	int m_SoundIndex;

};


#endif

﻿/**
 * @file   SceneBase.h
 * @brief  SceneBaseクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef SCENEBASE_H
#define SCENEBASE_H
#include <string>

namespace Lib
{
	class SceneBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _sceneName Sceneの名前
		 */
		SceneBase(std::string _sceneName) :
			m_SceneName(_sceneName){}

		/**
		 * デストラクタ
		 */
		~SceneBase() = default;
	
		/**
		 * 初期化処理
		 * シーンが遷移した最初に呼ばれる
		 */
		virtual bool Initialize() = 0;

		/**
		 * 終了処理
		 * シーンが遷移する前に呼ばれる
		 */
		virtual void Finalize() = 0;

		/**
		 * 制御処理
		 */
		virtual void Update() = 0;

		/**
		 * 描画処理
		 */
		virtual void Draw() = 0;

		/**
		 * Sceneの名前の取得
		 * @return Sceneの名前
		 */
		std::string GetSceneName()
		{
			return m_SceneName;
		}

	private:
		std::string m_SceneName;

	};
}

#endif

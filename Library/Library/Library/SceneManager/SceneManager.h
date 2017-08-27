/**
 * @file   SceneManager.h
 * @brief  SceneManagerクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <map>
#include <string>

namespace Lib
{
	class SceneBase;

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void Execute();

		void AddScene(SceneBase* _pScene, std::string _sceneName);

	private:
		SceneBase* m_pCurrentScene; //!< 現在のシーン
		std::map<std::string, SceneBase*> m_SceneList;
	};
}


#endif

﻿/**
 * @file   TaskManager.h
 * @brief  TaskManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <string>
#include <list>
#include <functional>
#include "../Singleton.h"
#include "TaskBase/UpdateTask/UpdateTask.h"
#include "TaskBase/DrawTask/DrawTask.h"
#include "TaskBase/DrawSetupTask/DrawSetupTask.h"

namespace Lib
{
	/**
	 * タスクの管理クラス
	 */
	class TaskManager
	{
		friend Singleton<TaskManager>;
	public:
		/**
		 * タスクの追加
		 * @param[in] _task 追加するタスク
		 */
		void AddTask(UpdateTask* _task);
		void AddTask(DrawTask* _task);
		void AddTask(DrawSetupTask* _task);

		/**
		 * タスクの削除
		 */
		void RemoveTask(UpdateTask* _task);
		void RemoveTask(DrawTask* _task);
		void RemoveTask(DrawSetupTask* _task);

		/**
		 * 登録しているタスクをUpdate,Drawの順に実行する
		 */
		void AllExecute();

		/**
		 * 全てのタスクを削除する
		 */
		void AllRemove();

	private:
		TaskManager();
		~TaskManager();

		std::list<DrawSetupTask*> m_DrawSetupTaskList; //!< 描画前処理
		std::list<UpdateTask*>	  m_UpdateTaskList;
		std::list<DrawTask*>	  m_DrawTaskList;
	};
}


#endif

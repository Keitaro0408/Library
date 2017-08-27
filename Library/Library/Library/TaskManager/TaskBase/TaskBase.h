#ifndef TASKBASE_H
#define TASKBASE_H
#include <string>

namespace Lib
{
	class TaskBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _priority 優先レベル
		 */
		TaskBase(int _priority = 0);
		
		/**
		 * デストラクタ
		 */
		virtual ~TaskBase();

		/**
		 * タスクを実行
		 */
		virtual void Execute() = 0;

		inline void SetPriority(int _priority)
		{
			m_Priority = _priority;
		}

		inline int GetTaskId() const
		{
			return m_TaskId;
		}

		inline bool operator > (const TaskBase& _task) const
		{
			return (m_Priority > _task.m_Priority);
		}

		inline bool operator < (const TaskBase& _task) const
		{
			return (m_Priority < _task.m_Priority);
		}

	private:
		static int m_TaskMaxNum;
		int		   m_TaskId;
		int		   m_Priority;

	};
}


#endif

#ifndef UPDATETASK_H
#define UPDATETASK_H

#include "../TaskBase.h"
#include "../../../ObjectBase/ObjectBase.h"

namespace Lib
{
	class UpdateTask : public TaskBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _priority 優先レベル
		 */
		UpdateTask(int _priority = 0) :
			TaskBase(_priority)
		{}

		/**
		 * デストラクタ
		 */
		virtual ~UpdateTask(){};

		void Execute() override
		{
			m_pObject->Update();
		}

		void SetObject(ObjectBase* _object)
		{
			m_pObject = _object;
		}

	private:
		ObjectBase* m_pObject;

	};
}


#endif

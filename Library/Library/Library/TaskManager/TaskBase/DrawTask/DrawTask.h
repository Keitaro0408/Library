#ifndef DRAWTASK_H
#define DRAWTASK_H

#include "../TaskBase.h"
#include "../../../ObjectBase/ObjectBase.h"

namespace Lib
{
	class DrawTask : public TaskBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _priority 優先レベル
		 */
		DrawTask(int _priority = 0) :
			TaskBase(_priority)
		{}

		/**
		* デストラクタ
		*/
		virtual ~DrawTask(){};

		void Execute() override
		{
			m_pObject->Draw();
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

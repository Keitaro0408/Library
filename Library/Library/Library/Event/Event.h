/**
 * @file   Event.h
 * @brief  Eventクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <unordered_map>
#include "../Helper/Helper.h"

namespace Lib
{
	struct Event
	{
		Event(char* _eventName)
		{
			eventNameId = STRING_ID(_eventName);
		}

		union Data
		{
			int   m_Int;
			float m_Float;
			bool  m_Bool;
		};

		std::unordered_map<char*, Data> eventData; //!< 格納されているデータ
		StringId eventNameId; //!< イベントのID

	};
}


#endif

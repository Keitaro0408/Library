/**
 * @file   EventManager.h
 * @brief  EventManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include "Event.h"
#include "SingletonWrapper.h"

namespace Lib
{
	class EventManager
	{
		friend SingletonWrapper<EventManager>;
	public:
		bool AddEvent(std::string _eventName, Event* _pEvent);
		bool CallEvent(std::string _eventName,int _eventId);

	private:
		EventManager(){};
		~EventManager(){};
		std::map<std::string,Event*> m_pEvent;
	};
}


#endif

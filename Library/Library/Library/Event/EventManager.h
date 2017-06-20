/**
 * @file   EventManager.h
 * @brief  EventManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <functional>
#include "EventListnerBase.h"
#include "..\Singleton.h"

namespace Lib
{
	class EventManager
	{
		friend Singleton<EventManager>;
	public:
		bool AddEvent(std::string _eventName, EventListnerBase* _pEvent);
		bool CallEvent(std::string _eventName);

	private:
		EventManager(){};
		~EventManager(){};
		std::map<std::string, std::function<void()> > m_pEvent;
	};
}


#endif

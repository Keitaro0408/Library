#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include "Event.h"

namespace Lib
{
	class EventManager
	{
	public:
		static EventManager* GetInstance()
		{
			static EventManager Instance;
			return &Instance;
		}

		bool AddEvent(std::string _eventName, Event* _pEvent);
		bool CallEvent(std::string _eventName,int _eventId);

	private:
		EventManager();
		~EventManager();
		std::map<std::string,Event*> m_pEvent;
	};
}


#endif

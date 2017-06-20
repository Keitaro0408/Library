/**
 * @file   EventManager.cpp
 * @brief  EventManagerクラスの実装
 * @author kotani
 */
#include "EventManager.h"
#include "EventListnerBase.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::EventManager::AddEvent(std::string _eventName, EventListnerBase* _pEvent)
{
	//m_pEvent[_eventName] = _pEvent;
	m_pEvent[_eventName] = std::bind(&EventListnerBase::Action,_pEvent);
	return true;
}

bool Lib::EventManager::CallEvent(std::string _eventName)
{
	if (m_pEvent.find(_eventName) == m_pEvent.end()){
		return false;
	}

	if (m_pEvent[_eventName] != NULL)
	{
		m_pEvent[_eventName]();
	}
	return true;
}

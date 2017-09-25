/**
 * @file   EventManager.h
 * @brief  EventManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <functional>
#include "..\Singleton.h"
#include "Event.h"
#include "EventListenerBase.h"

namespace Lib
{
	/**
	 * コールバックのイベントを管理する
	 */
	class EventManager
	{
		friend Singleton<EventManager>;
	public:
		/**
		 * イベントの追加
		 * @param[in] _pEventListnerBaseList イベント待受クラス
		 */
		void AddListener(EventListenerBase* _pEventListenerBaseList);

		/**
		 * イベントを送信する
		 * @param[in] _pEvent イベントクラス
		 */
		void SendEvent(Event& _pEvent);

		/**
		 * リストにイベントを追加する
		 * @param[in] _pEvent イベントクラス
		 */
		void AddEventList(Event* _pEvent);

		/**
		 * リストに登録しているイベントを実行して、リストを削除する。
		 */
		void Execute();

		/**
		 * 登録されている全てのイベントをリストから削除する
		 */
		void AllEventClear();

	private:
		EventManager(){};
		~EventManager(){};

		std::list<EventListenerBase*> m_pEventListenerBase;
		std::list<Event>			  m_pEventList;
	};
}


#endif

﻿/**
 * @file   EventManager.h
 * @brief  EventManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <vector>
#include <functional>
#include "EventListnerBase.h"
#include "..\Singleton.h"


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
		 * @param[in] _eventName イベントの名前
		 * @param[in] _pEvent 実行されるクラス
		 */
		void AddEvent(std::string _eventName, EventListnerBase* _pEvent);

		/**
		 * イベントの追加
		 * @param[in] _eventName イベントの名前
		 * @param[in] _event 実行される関数
		 */
		void AddEvent(std::string _eventName, std::function<void()> _event);

		/**
		 * イベントを呼ぶ
		 * @param[in] イベントの名前
		 */
		bool CallEvent(std::string _eventName);

		/**
		 * 登録されているイベントを解放する
		 */
		void AllEventRelease();

	private:
		EventManager(){};
		~EventManager(){};
		std::map<std::string, std::vector<std::function<void()> > > m_pEvent;
	};
}


#endif

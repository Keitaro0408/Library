﻿/**
 * @file   ObjectBase.cpp
 * @brief  ObjectBaseクラスの実装
 * @author kotani
 */
#include "ObjectBase.h"
#include "..\TaskManager\TaskManager.h"

namespace Lib
{
	void ObjectBase::InitializeTask(int _updatePriority, int _drawPriority, int _drawSetupPriority)
	{
		m_pUpdateTask = new Lib::UpdateTask(_updatePriority);
		m_pUpdateTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pUpdateTask);

		m_pDrawSetupTask = new Lib::DrawSetupTask(_drawPriority);
		m_pDrawSetupTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pDrawSetupTask);

		m_pDrawTask = new Lib::DrawTask(_drawPriority);
		m_pDrawTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(m_pDrawTask);
	}

	void ObjectBase::FinalizeTask()
	{
		Lib::SafeDelete(m_pDrawTask);
		Lib::SafeDelete(m_pDrawSetupTask);
		Lib::SafeDelete(m_pUpdateTask);
	}
}
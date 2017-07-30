﻿#ifndef SHARED_PTR_PRIVATE_H
#define SHARED_PTR_PRIVATE_H

template<typename Type>
Shared<Type>::Shared(Type* _type) :
m_pMutex(&m_Mutex)
{
	m_pRefCount = new unsigned int;
	*m_pRefCount = 1;

	m_pWeakCount = new unsigned int;
	*m_pWeakCount = 1;

	m_pInstance = _type;
}

template<typename Type>
Shared<Type>::Shared() :
m_pMutex(&m_Mutex)
{
	m_pRefCount = nullptr;
	m_pWeakCount = nullptr;
	m_pInstance = nullptr;
}

template<typename Type>
Shared<Type>::~Shared()
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	Release();
}
template<typename Type>
void Shared<Type>::Reset()
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	SafeDelete(m_pRefCount);
	SafeDelete(m_pWeakCount);
	delete m_pInstance;
	m_pInstance = nullptr;
}

template<typename Type>
void Shared<Type>::Reset(Type* _type)
{
	std::unique_lock<std::recursive_mutex> locker = Locker();

	SafeDelete(m_pRefCount);
	SafeDelete(m_pInstance);

	m_pRefCount = new unsigned int;
	*m_pRefCount = 1;

	m_pWeakCount = new unsigned int;
	*m_pWeakCount = 1;

	m_pInstance = _type;
}


template<typename Type>
Shared<Type>& Shared<Type>::operator=(const Shared& _obj)
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	m_pRefCount = _obj.m_pRefCount;
	m_pMutex = _obj.m_pMutex;

	/* 違うポインタなら参照カウンタを増やす */
	if (m_pInstance != _obj.m_pInstance)
	{
		AddRef();
		++m_pWeakCount;
		m_pInstance = _obj.m_pInstance;
	}
	return *this;
}

template<typename Type>
Type* Shared<Type>::operator->() const
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	return m_pInstance;
}

template<typename Type>
std::unique_lock<std::recursive_mutex> Shared<Type>::Locker() const
{
	return std::unique_lock<std::recursive_mutex>(*m_pMutex);
}

template<typename Type>
void Shared<Type>::AddRef()
{
	if (m_pRefCount != nullptr)
	{
		++(*m_pRefCount);
	}
}

template<typename Type>
void Shared<Type>::Release()
{
	if (m_pRefCount != nullptr)
	{
		--(*m_pRefCount);
		--(*m_pWeakCount);

		if (*m_pRefCount == 0)
		{
			SafeDelete(m_pInstance);
			//SafeDelete(m_pRefCount);
			//SafeDelete(m_pWeakCount);
		}

		if (*m_pWeakCount == 0)
		{
			SafeDelete(m_pWeakCount);
			SafeDelete(m_pRefCount);
		}
	}
}


#endif

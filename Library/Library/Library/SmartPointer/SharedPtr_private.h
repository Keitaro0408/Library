#ifndef SHARED_PTR_PRIVATE_H
#define SHARED_PTR_PRIVATE_H

template<typename Type>
Shared<Type>::Shared(Type* _type) :
m_pMutex(&m_Mutex)
{
	m_pRefCount = new unsigned int;
	*m_pRefCount = 0;
	(*m_pRefCount)++;

	m_Instance = _type;
}

template<typename Type>
Shared<Type>::Shared() :
m_pMutex(&m_Mutex)
{
	m_pRefCount = nullptr;
	m_Instance = nullptr;
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
	delete m_pRefCount;
	m_pRefCount = nullptr;

	delete m_Instance;
	m_Instance = nullptr;
}

template<typename Type>
void Shared<Type>::Reset(Type* _type)
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	delete m_pRefCount;
	m_pRefCount = nullptr;

	delete m_Instance;
	m_Instance = nullptr;

	m_pRefCount = new unsigned int;
	*m_pRefCount = 0;
	AddRef();
	m_Instance = _type;
}


template<typename Type>
Shared<Type>& Shared<Type>::operator=(const Shared& _obj)
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	m_pRefCount = _obj.m_pRefCount;
	m_pMutex = _obj.m_pMutex;

	/* 違うポインタなら参照カウンタを増やす */
	if (m_Instance != _obj.m_Instance)
	{
		AddRef();
		m_Instance = _obj.m_Instance;
	}
	return *this;
}

template<typename Type>
Type* Shared<Type>::operator->() const
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	return m_Instance;
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
		if (*m_pRefCount == 0)
		{
			delete m_Instance;
			m_Instance = nullptr;
			delete m_pRefCount;
			m_pRefCount = nullptr;
		}
	}
}


#endif

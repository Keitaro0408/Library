#ifndef SHARED_PTR_PRIVATE_H
#define SHARED_PTR_PRIVATE_H

template<typename Type>
SharedPtr<Type>::SharedPtr(Type* _type) :
Pointer(_type),
m_RefCount(1),
m_pRefCount(&m_RefCount),
m_pMutex(&m_Mutex)
{
}

template<typename Type>
SharedPtr<Type>::SharedPtr() :
m_RefCount(0),
m_pRefCount(&m_RefCount),
m_pMutex(&m_Mutex)
{
	m_Instance = nullptr;
}

template<typename Type>
SharedPtr<Type>::~SharedPtr()
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	(*m_pRefCount)--;
	if (*m_pRefCount == 0)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}
template<typename Type>
void SharedPtr<Type>::Reset()
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	(*m_pRefCount) = 0;
	delete m_Instance;
	m_Instance = nullptr;
}

template<typename Type>
void SharedPtr<Type>::Reset(Type* _type)
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	(*m_pRefCount)++;
	delete m_Instance;
	m_Instance = nullptr;
	m_Instance = _type;
}

template<typename Type>
Type* SharedPtr<Type>::Release()
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	Type* returnVal = m_Instance;
	m_Instance = nullptr;

	return returnVal;
}

template<typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator=(const SharedPtr& _obj)
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	m_pRefCount = _obj.m_pRefCount;
	m_pMutex = _obj.m_pMutex;
	if (m_Instance != _obj.m_Instance)
	{
		(*m_pRefCount)++;
		m_Instance = _obj.m_Instance;
	}
	return *this;
}

template<typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator=(Pointer<Type>& _obj)
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	this->Reset(_obj.Release());
	return *this;
}

template<typename Type>
Type* SharedPtr<Type>::operator->() const
{
	std::unique_lock<std::recursive_mutex> locker = Locker();
	return m_Instance;
}

template<typename Type>
std::unique_lock<std::recursive_mutex> SharedPtr<Type>::Locker()
{
	return  std::unique_lock<std::recursive_mutex>(*m_pMutex);
}


#endif

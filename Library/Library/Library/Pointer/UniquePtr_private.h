#ifndef UNIQUE_PTR_PRIVATE_H
#define UNIQUE_PTR_PRIVATE_H

template<typename Type>
UniquePtr<Type>::UniquePtr(Type* _type)
{
	m_Instance = _type;
}

template<typename Type>
UniquePtr<Type>::UniquePtr()
{
	m_Instance = nullptr;
}

template<typename Type>
UniquePtr<Type>::~UniquePtr()
{
	delete m_Instance;
	m_Instance = nullptr;
}

template<typename Type>
const Type* UniquePtr<Type>::GetPtr()
{
	return m_Instance;
}

template<typename Type>
void UniquePtr<Type>::Reset()
{
	delete m_Instance;
	m_Instance = nullptr;
}

template<typename Type>
void UniquePtr<Type>::Reset(Type* _type)
{
	delete m_Instance;
	m_Instance = nullptr;
	m_Instance = _type;
}

template<typename Type>
Type* UniquePtr<Type>::Release()
{
	Type* returnVal = m_Instance;
	m_Instance = nullptr;

	return returnVal;
}

template<typename Type>
Type* UniquePtr<Type>::operator->() const
{
	return m_Instance;
}

template<typename Type>
UniquePtr<Type>::operator bool() const
{
	if (m_Instance != nullptr)
	{
		return true;
	}

	return false;
}


#endif

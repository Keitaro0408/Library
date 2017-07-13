#ifndef UNIQUE_PTR_PRIVATE_H
#define UNIQUE_PTR_PRIVATE_H

template<typename Type>
Unique<Type>::Unique(Type* _type)
{
	m_Instance = _type;
}

template<typename Type>
Unique<Type>::Unique()
{
	m_Instance = nullptr;
}

template<typename Type>
Unique<Type>::~Unique()
{
	delete m_Instance;
	m_Instance = nullptr;
}

template<typename Type>
void Unique<Type>::Reset()
{
	delete m_Instance;
	m_Instance = nullptr;
}

template<typename Type>
void Unique<Type>::Reset(Type* _type)
{
	delete m_Instance;
	m_Instance = nullptr;
	m_Instance = _type;
}

template<typename Type>
Type* Unique<Type>::Release()
{
	Type* returnVal = m_Instance;
	m_Instance = nullptr;

	return returnVal;
}

template<typename Type>
Type* Unique<Type>::operator->() const
{
	return m_Instance;
}



#endif

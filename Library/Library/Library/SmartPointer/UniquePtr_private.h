#ifndef UNIQUE_PTR_PRIVATE_H
#define UNIQUE_PTR_PRIVATE_H

template<typename Type>
Unique<Type>::Unique(Type* _type)
{
	m_pInstance = _type;
}

template<typename Type>
Unique<Type>::Unique()
{
	m_pInstance = nullptr;
}

template<typename Type>
Unique<Type>::~Unique()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

template<typename Type>
void Unique<Type>::Reset()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

template<typename Type>
void Unique<Type>::Reset(Type* _type)
{
	delete m_pInstance;
	m_pInstance = nullptr;
	m_pInstance = _type;
}

template<typename Type>
Type* Unique<Type>::operator->() const
{
	return m_pInstance;
}



#endif

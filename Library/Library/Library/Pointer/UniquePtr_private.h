#ifndef UNIQUE_PTR_PRIVATE_H
#define UNIQUE_PTR_PRIVATE_H

template<typename Type>
UniquePtr<Type>::UniquePtr(Type* _type) : 
Pointer(_type)
{
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


#endif

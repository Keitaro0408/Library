#ifndef POINTER_PRIVATE_H
#define POINTER_PRIVATE_H

template<typename Type>
Pointer<Type>::Pointer(Type* _type)
{
	m_Instance = _type;
}

template<typename Type>
Pointer<Type>::Pointer()
{
	m_Instance = nullptr;
}

template<typename Type>
Pointer<Type>::~Pointer()
{
}

template<typename Type>
const Type* Pointer<Type>::GetPtr()
{
	return m_Instance;
}

template<typename Type>
void Pointer<Type>::Reset()
{
	delete m_Instance;
	m_Instance = nullptr;
}

template<typename Type>
void Pointer<Type>::Reset(Type* _type)
{
	delete m_Instance;
	m_Instance = nullptr;
	m_Instance = _type;
}

template<typename Type>
Type* Pointer<Type>::Release()
{
	Type* returnVal = m_Instance;
	m_Instance = nullptr;

	return returnVal;
}

template<typename Type>
Type* Pointer<Type>::operator->() const
{
	return m_Instance;
}

template<typename Type>
Pointer<Type>::operator bool() const
{
	if (m_Instance != nullptr)
	{
		return true;
	}

	return false;
}


#endif

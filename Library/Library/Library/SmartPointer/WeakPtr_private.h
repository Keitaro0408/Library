#ifndef WEAK_PTR_PRIVATE_H
#define WEAK_PTR_PRIVATE_H
#include "../Helper/Helper.h"

template<typename Type>
Weak<Type>::Weak() :
m_pWeakCount(nullptr)
{
}

template<typename Type>
Weak<Type>::~Weak()
{
	--(*m_pWeakCount);
	if (*m_pWeakCount == 0)
	{
		SafeDelete(m_pWeakCount);
		SafeDelete(m_pRefCount);
	}
}

template<typename Type>
Weak<Type>& Weak<Type>::operator=(const Shared<Type>& _obj)
{
	m_pWeakCount = _obj.m_pWeakCount;
	m_pRefCount = _obj.m_pRefCount;
	++(*m_pWeakCount);
	m_pInstance = _obj.m_pInstance;

	return *this;
}


#endif

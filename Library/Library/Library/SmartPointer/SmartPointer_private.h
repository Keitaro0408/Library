#ifndef POINTER_PRIVATE_H
#define POINTER_PRIVATE_H

template<typename Type, template <typename Type> class Policy>
SmartPtr<Type, Policy>::SmartPtr(Type* _type) :
Policy<Type>(_type)
{
}

template<typename Type, template <typename Type> class Policy>
SmartPtr<Type, Policy>::SmartPtr()
{
}

template<typename Type, template <typename Type> class Policy>
SmartPtr<Type, Policy>::~SmartPtr()
{
}

template<typename Type, template <typename Type> class Policy>
const Type* SmartPtr<Type, Policy>::GetPtr()
{
	return m_Instance;
}

template<typename Type, template <typename Type> class Policy>
void SmartPtr<Type, Policy>::Reset()
{
	Policy<Type>::Reset();
}

template<typename Type, template <typename Type> class Policy>
void SmartPtr<Type, Policy>::Reset(Type* _type)
{
	Policy<Type>::Reset(_type);
}

//template<typename Type, template <typename Type> class Policy>
//Pointer<Type, Policy>& Pointer<Type, Policy>::operator = (const Pointer& _obj)
//{
//	return Policy<Type>::operator=(_obj);
//}

template<typename Type, template <typename Type> class Policy>
Type* SmartPtr<Type, Policy>::operator->() const
{
	return Policy<Type>::operator->();
}

template<typename Type, template <typename Type> class Policy>
SmartPtr<Type, Policy>::operator bool() const
{
	if (m_Instance != nullptr)
	{
		return true;
	}

	return false;
}


#endif

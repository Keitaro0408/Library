/**
 * @file   SmartPtr.h
 * @brief  SmartPtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H
#include "UniquePtr.h"
#include "SharedPtr.h"
#include "WeakPtr.h"

#define EMPTY_POINTER(ptr) \
		!ptr


namespace Lib
{

	template<typename Type, template <typename Type> class Policy = Unique>
	/**
	 * スマートポインタのホストクラス
	 *
	 * デフォルトではユニークのポリシーが使われる
	 */
	class SmartPtr : public Policy<Type>
	{
	public:
		SmartPtr(Type* _type);
		SmartPtr();

		virtual ~SmartPtr();

		/**
		 * ポインタを取得する
		 */
		const Type* GetPtr();

		/**
		 * メンバにアクセスする
		 */
		Type* operator->() const;

		/* 暗黙的にアップキャストさせる */
		SmartPtr& operator = (const Policy<Type>&);

		Policy<Type>& operator = (Policy<Type>&& _obj)
		{
			return Policy<Type>::operator=(static_cast<Policy<Type>&&>(_obj));
		}

		/**
		 * 中身が空かチェック
		 */
		operator bool() const;

	};

	template<typename Type, template <typename Type> class Policy = Unique, class... Args>
	Policy<Type> MakeSmartPtr(Args&&... args)
	{
		return Policy<Type>(new Type(std::forward<Args>(args)...));
	}


#include "SmartPointer_private.h"

}

#endif

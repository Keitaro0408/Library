/**
 * @file   UniquePtr.h
 * @brief  UniquePtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include "Pointer.h"

namespace Lib
{
	/**
	 * 所有権が1つしか持てない様に振る舞うスマートポインタ
	 * カスタムデリータも実装予定
	 */
	template<typename Type>
	class UniquePtr : public Pointer<Type>
	{
	public:
		UniquePtr(Type* _type);
		UniquePtr();

		virtual ~UniquePtr();

		/**
		 * 直接代入の禁止
		 */
		UniquePtr& operator=(const UniquePtr&) = delete;

	private:

	};


#include "UniquePtr_private.h"
}

#endif

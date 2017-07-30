/**
 * @file   UniquePtr.h
 * @brief  UniquePtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
//#include "Pointer.h"

namespace Lib
{
	/**
	 * 所有権が1つしか持てない様に振る舞うスマートポインタのポリシー
	 * カスタムデリータと配列の生成の実装予定
	 */
	template<typename Type>
	class Unique
	{
	public:
		Unique(Type* _type);
		Unique();

		virtual ~Unique();

		/**
		 * メモリを解放する
		 */
		void Reset();

		/**
		 * メモリを解放した後に引数のポインタを扱う
		 * @param[in] _type 新しく管理するポインタ
		 */
		void Reset(Type* _type);

		/**
		 * メンバにアクセスする
		 */
		Type* operator->() const;

		/**
		 * 直接代入の禁止 
		 */
		Unique& operator=(const Unique&) = delete;
		Unique& operator=(Unique<Type>&& _obj)
		{
			this->m_pInstance = _obj.m_pInstance;
			_obj.m_pInstance = nullptr;
			return *this;
		}

	protected:
		Type* m_pInstance;

	};

#include "UniquePtr_private.h"
}

#endif

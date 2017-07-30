/**
 * @file   SharedPtr.h
 * @brief  SharedPtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include "UniquePtr.h"
#include "../Helper/Helper.h"
#include <mutex>

namespace Lib
{
	template<typename Type>
	class Shared
	{
	public:
		Shared(Type* _type);
		
		Shared();

		virtual ~Shared();

		/**
		 * メモリを解放する
		 */
		void Reset();

		/**
		 * メモリを解放した後に引数のポインタを扱う
		 * @param[in] _type 新しく管理するポインタ
		 */
		void Reset(Type* _type);


		Shared& operator=(const Shared&);

		Shared& operator=(Shared<Type>&& _obj)
		{
			m_pRefCount = _obj.m_pRefCount;
			m_pWeakCount = _obj.m_pWeakCount;
			++(*m_pWeakCount);
			++(*m_pRefCount);
			this->m_pInstance = _obj.m_pInstance;
			return *this;
		}

		Type* operator->() const;

		Type& operator*()
		{
			return *m_pInstance;
		}

	private:
		/* 同一スレッドからの再帰的なロック取得を許可する(今後普通のmutexにする可能性あり) */
		std::unique_lock<std::recursive_mutex> Locker() const;

		/**
		 * 参照カウンタ増加
		 */
		void AddRef();

		/**
		 * 参照カウンタを減少させて0なら持っている
		 * オブジェクトをdeleteする
		 */
		void Release();

		unsigned int* m_pRefCount;
		unsigned int* m_pWeakCount;

		std::recursive_mutex m_Mutex;
		std::recursive_mutex* m_pMutex;

		Type* m_pInstance;

	};

#include "SharedPtr_private.h"

}

#endif

/**
 * @file   SharedPtr.h
 * @brief  SharedPtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include "UniquePtr.h"
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

		/**
		 * リソースの管理を放棄する
		 * @return 管理を破棄したポインタ
		 */
		Type* Release();

		Shared& operator=(const Shared&);
		Shared& operator=(const Unique<Type>&);
		
		Type* operator->() const;

	private:
		/* 同一スレッドからの再帰的なロック取得を許可する(今後普通のmutexにする可能性あり) */
		std::unique_lock<std::recursive_mutex> Locker() const;

		unsigned int m_RefCount;
		unsigned int* m_pRefCount;
		std::recursive_mutex m_Mutex;
		std::recursive_mutex* m_pMutex;

		Type* m_Instance;

	};

#include "SharedPtr_private.h"

}

#endif

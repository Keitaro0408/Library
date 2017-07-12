/**
* @file   UniquePtr.h
* @brief  UniquePtrクラスのヘッダファイル
* @author kotani
*/
#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#define EMPTY_POINTER(ptr) \
		!ptr


namespace Lib
{
	/**
	 * 所有権が1つしか持てない様に振る舞うスマートポインタ
	 * カスタムデリータも実装予定
	 */
	template<typename Type>
	class UniquePtr
	{
	public:
		UniquePtr(Type* _type);
		UniquePtr();

		~UniquePtr();

		/**
		 * ポインタを取得する
		 */
		const Type* GetPtr();

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

		/**
		 * 直接代入の禁止
		 */
		UniquePtr& operator=(const UniquePtr&) = delete;

		/**
		 * メンバにアクセスする
		 */
		Type* operator->() const;

		/**
		 * 中身が空かチェック
		 */
		operator bool() const;

	private:
		Type* m_Instance;

	};


#include "UniquePtr_private.h"
}

#endif

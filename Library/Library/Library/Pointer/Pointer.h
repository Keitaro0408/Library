/**
 * @file   Pointer.h
 * @brief  Pointerクラスのヘッダファイル
 * @author kotani
 */
#ifndef POINTER_H
#define POINTER_H

#define EMPTY_POINTER(ptr) \
		!ptr


namespace Lib
{
	template<typename Type>
	class Pointer
	{
	public:
		Pointer(Type* _type);
		Pointer();

		virtual ~Pointer();

		/**
		 * ポインタを取得する
		 */
		const Type* GetPtr();

		/**
		 * メモリを解放する
		 */
		virtual void Reset();

		/**
		 * メモリを解放した後に引数のポインタを扱う
		 * @param[in] _type 新しく管理するポインタ
		 */
		virtual void Reset(Type* _type);

		/**
		 * リソースの管理を放棄する
		 * @return 管理を破棄したポインタ
		 */
		Type* Release();

		/**
		 * メンバにアクセスする
		 */
		Type* operator->() const;

		/**
		 * 中身が空かチェック
		 */
		operator bool() const;

	protected:
		Type* m_Instance;

	};


#include "Pointer_private.h"
}

#endif

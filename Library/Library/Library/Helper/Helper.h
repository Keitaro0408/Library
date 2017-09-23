/**
 * @file   Helper.h
 * @brief  便利関数のヘッダファイル
 * @author kotani
 */
#ifndef HELPER_H
#define HELPER_H
#include <functional>
/* コピー禁止マクロ */
#define NON_COPYABLE(Class) Class(const Class &); \
                        void operator=(const Class &)

/* 文字列をハッシュ値に変換する(最終的には自分で作りたい) */
#define STRING_ID(str) std::hash<char*>()(str)
typedef size_t StringId;

namespace Lib
{
	/**
	 * delete処理
	 */
	template <class Type>
	inline void SafeDelete(Type*& p)
	{
		delete p;
		p = nullptr;
	}

	/**
	 * delete処理(配列版)
	 */
	template <class Type>
	inline void SafeArrayDelete(Type*& p)
	{
		delete[] p;
		p = nullptr;
	}
}


#endif

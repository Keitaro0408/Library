/**
 * @file   ObjectBase.h
 * @brief  ObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

namespace Lib
{
	/**
	 * タスクの実行等に使用されるオブジェクトの基底クラス
	 */
	class ObjectBase
	{
	public:
		ObjectBase(){};
		virtual ~ObjectBase(){};

		virtual void Update() = 0;
		virtual void Draw() = 0;

	};
}


#endif

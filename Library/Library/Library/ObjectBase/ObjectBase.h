/**
 * @file   ObjectBase.h
 * @brief  ObjectBaseクラスのヘッダファイル(未実装)
 * @author kotani
 */
#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

namespace Lib
{
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

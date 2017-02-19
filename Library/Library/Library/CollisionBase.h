﻿/**
 * @file   CollisionBase.h
 * @brief  CollisionBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef COLLISIONBASE_H
#define COLLISIONBASE_H
#include <D3DX10.h>
#include <string>

namespace Lib
{
	enum COLLISION_TYPE
	{
		COLLISION_SQUARE,	//矩形で判定を取る
		COLLISION_DISTANCE
	};

	struct SQUARE
	{
		D3DXVECTOR2 LeftTop;
		D3DXVECTOR2 RightDown;
	};

	class CollisionBase
	{
	public:
		CollisionBase();
		virtual ~CollisionBase();

		virtual void HitAction() = 0;

	protected:
		D3DXVECTOR2		m_Position;
		COLLISION_TYPE  m_CollisionType;
		SQUARE			m_Square;
		std::string		m_CollisionName; //当たり判定の名前
		bool			m_isEnable;

	};
}


#endif

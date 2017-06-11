/**
 * @file   Math.cpp
 * @author kotani
 */
#include "Math.h"
#include <math.h>

namespace Lib
{
	namespace Math
	{
		float GetDistance(const D3DXVECTOR2& _pos1, const D3DXVECTOR2& _pos2)
		{
			return sqrt(pow(_pos2.x - _pos1.x, 2) + pow(_pos2.y - _pos1.y, 2));
		}

		float GetDistance(const D3DXVECTOR3& _pos1, const D3DXVECTOR3& _pos2)
		{
			return sqrt(pow(_pos2.x - _pos1.x, 2) + pow(_pos2.y - _pos1.y, 2) + pow(_pos2.z - _pos1.z, 2));
		}

		float GetAngle(const D3DXVECTOR2& _pos1, const D3DXVECTOR2& _pos2)
		{
			return atan2(_pos2.y - _pos1.y, _pos2.x - _pos1.x);
		}

		D3DXVECTOR2 GetAngleMovePos(float _movement, float _angle)
		{
			D3DXVECTOR2 returnVar = {0.f,0.f};
			returnVar.x = _movement * cos(ToRadian(_angle));
			returnVar.y = _movement * sin(ToRadian(_angle));
			return returnVar;
		}
	}
}

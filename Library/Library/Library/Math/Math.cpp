﻿/**
 * @file   Math.cpp
 * @author kotani
 */
#include "Math.h"
#include <math.h>

namespace Lib
{
	namespace Math
	{
		float GetDistance(const VECTOR2& _pos1, const VECTOR2& _pos2)
		{
			return sqrt(pow(_pos2.x - _pos1.x, 2) + pow(_pos2.y - _pos1.y, 2));
		}

		float GetDistance(const VECTOR3& _pos1, const VECTOR3& _pos2)
		{
			return sqrt(pow(_pos2.x - _pos1.x, 2) + pow(_pos2.y - _pos1.y, 2) + pow(_pos2.z - _pos1.z, 2));
		}

		float GetAngle(const VECTOR2& _pos1, const VECTOR2& _pos2)
		{
			return ToDegree(atan2(_pos2.y - _pos1.y, _pos2.x - _pos1.x));
		}

		VECTOR2 GetAngleMovePos(float _movement, float _angle)
		{
			VECTOR2 returnVar = {0.f,0.f};
			returnVar.x = _movement * cos(ToRadian(_angle));
			returnVar.y = _movement * sin(ToRadian(_angle));
			return returnVar;
		}


		MATRIX* MatrixIdentity(MATRIX* _pMatrix)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_11 = 1.f;
			_pMatrix->_22 = 1.f;
			_pMatrix->_33 = 1.f;
			_pMatrix->_44 = 1.f;
			return _pMatrix;
		}

		MATRIX* MatrixTranspose(MATRIX* _pMatrix)
		{
			MATRIX matrix;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix.m_Matrix[i][j] = _pMatrix->m_Matrix[i][j];
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = matrix.m_Matrix[j][i];
				}
			}
			return _pMatrix;
		}

		MATRIX* MatrixTranslation(MATRIX* _pMatrix, float _x, float _y, float _z)
		{
			MatrixIdentity(_pMatrix);
			_pMatrix->_41 = _x;
			_pMatrix->_42 = _y;
			_pMatrix->_43 = _z;
			return _pMatrix;
		}

		MATRIX* MatrixScaling(MATRIX* _pMatrix, float _x, float _y, float _z)
		{
			_pMatrix->_11 = _x;
			_pMatrix->_22 = _y;
			_pMatrix->_33 = _z;
			return _pMatrix;
		}

		MATRIX* MatrixRotationX(MATRIX* _pMatrix, float _angle)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_11 = 1.f;
			_pMatrix->_44 = 1.f;
			_pMatrix->_22 = cos(ToRadian(_angle));
			_pMatrix->_23 = sin(ToRadian(_angle));
			_pMatrix->_32 = -sin(ToRadian(_angle));
			_pMatrix->_33 = cos(ToRadian(_angle));
			return _pMatrix;
		}

		MATRIX* MatrixRotationY(MATRIX* _pMatrix, float _angle)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_44 = 1.f;
			_pMatrix->_22 = 1.f;
			_pMatrix->_11 = cos(ToRadian(_angle));
			_pMatrix->_13 = -sin(ToRadian(_angle));
			_pMatrix->_31 = sin(ToRadian(_angle));
			_pMatrix->_33 = cos(ToRadian(_angle));
			return _pMatrix;
		}

		MATRIX* MatrixRotationZ(MATRIX* _pMatrix, float _angle)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_44 = 1.f;
			_pMatrix->_33 = 1.f;
			_pMatrix->_11 = cos(ToRadian(_angle));
			_pMatrix->_12 = sin(ToRadian(_angle));
			_pMatrix->_21 = -sin(ToRadian(_angle));
			_pMatrix->_22 = cos(ToRadian(_angle));
			return _pMatrix;
		}
	}
}

/**
* @file   MyMatrix.cpp
* @brief  MATRIX構造体の実装
* @author kotani
*/
#include "MyMatrix.h"

namespace Lib
{
	MATRIX::MATRIX(const float* _value)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_Matrix[i][j] = *_value;
			}
		}
	}

	MATRIX::MATRIX(const MATRIX& _obj)
	{
		*this = _obj;
	}

	MATRIX& MATRIX::operator *= (const MATRIX& _obj)
	{
		MATRIX matrix;
		for (int i = 0; i< 4; ++i)
		{
			for (int j = 0; j< 4; ++j)
			{
				matrix.m_Matrix[i][j] = 0;
				for (int k = 0; k< 4; ++k)
				{
					matrix.m_Matrix[i][j] += m_Matrix[i][k] * _obj.m_Matrix[k][j];
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_Matrix[i][j] = matrix.m_Matrix[i][j];
			}
		}
		return *this;
	}

	MATRIX& MATRIX::operator += (const MATRIX& _obj)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_Matrix[i][j] += _obj.m_Matrix[i][j];
			}
		}
		return *this;
	}

	MATRIX& MATRIX::operator -= (const MATRIX& _obj)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_Matrix[i][j] -= _obj.m_Matrix[i][j];
			}
		}
		return *this;
	}

	MATRIX MATRIX::operator * (const MATRIX& _obj) const
	{
		MATRIX matrix;
		for (int i = 0; i< 4; ++i)
		{
			for (int j = 0; j< 4; ++j)
			{
				matrix.m_Matrix[i][j] = 0;
				for (int k = 0; k< 4; ++k)
				{
					matrix.m_Matrix[i][j] += m_Matrix[i][k] * _obj.m_Matrix[k][j];
				}
			}
		}
		return matrix;
	}

	MATRIX MATRIX::operator + (const MATRIX& _obj) const
	{
		MATRIX matrix;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				matrix.m_Matrix[i][j] = m_Matrix[i][j];
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				matrix.m_Matrix[i][j] += _obj.m_Matrix[i][j];
			}
		}
		return matrix;
	}

	MATRIX MATRIX::operator - (const MATRIX& _obj) const
	{
		MATRIX matrix;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				matrix.m_Matrix[i][j] = m_Matrix[i][j];
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				matrix.m_Matrix[i][j] -= _obj.m_Matrix[i][j];
			}
		}
		return matrix;
	}

	bool MATRIX::operator == (const MATRIX& _obj) const
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_Matrix[i][j] != _obj.m_Matrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool MATRIX::operator != (const MATRIX& _obj) const
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_Matrix[i][j] == _obj.m_Matrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
}

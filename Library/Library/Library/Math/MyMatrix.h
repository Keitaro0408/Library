/**
 * @file   MyMatrix.h
 * @brief  MATRIX�\���̂̃w�b�_�t�@�C��
 * @author kotani
 */
#ifndef MYMATRIX_H
#define MYMATRIX_H

namespace Lib
{
	/**
	 * 4*4�̍s��\����
	 */
	typedef struct MATRIX
	{
		MATRIX() {};
		MATRIX(const float *);
		MATRIX(const MATRIX&);

		MATRIX& operator *= (const MATRIX&);
		MATRIX& operator += (const MATRIX&);
		MATRIX& operator -= (const MATRIX&);


		MATRIX operator * (const MATRIX&) const;
		MATRIX operator + (const MATRIX&) const;
		MATRIX operator - (const MATRIX&) const;

		/* ��r���Z�q */
		bool operator == (const MATRIX&) const;
		bool operator != (const MATRIX&) const;

		union
		{
			struct 
			{
				float        _11, _12, _13, _14;
				float        _21, _22, _23, _24;
				float        _31, _32, _33, _34;
				float        _41, _42, _43, _44;
			};
			float m_Matrix[4][4];
		};
	} MATRIX;
}


#endif

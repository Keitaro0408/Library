﻿/**
 * @file   Math.h
 * @author kotani
 */
#ifndef MATH_H
#define MATH_H
#include "MyMatrix.h"
#include "MyVector.h"

#define MyLib_PI 3.14159265358979323846f

namespace Lib
{
	/**
	 * 計算系ライブラリ
	 */
	namespace Math
	{
		/**
		 * 2点間の距離を求める(2次元座標)
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 距離
		 */
		float GetDistance(const VECTOR2& _pos1, const VECTOR2& _pos2);

		/**
		 * 2点間の距離を求める(3次元座標)
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 距離
		 */
		float GetDistance(const VECTOR3& _pos1, const VECTOR3& _pos2);

		/**
		 * 2点間の角度を求める
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 角度(degree値)
		 */
		float GetAngle(const VECTOR2& _pos1, const VECTOR2& _pos2);

		/**
		 * radianをdegreeに変換する
		 * @param[in] _radian 角度(radian値)
		 */
		inline float ToDegree(float _radian)
		{
			return _radian * (180.0f / MyLib_PI);
		}

		/**
		 * degreeをradianに変換する
		 * @param[in] _degree 角度(_degree値)
		 */
		inline float ToRadian(float _degree)
		{
			return _degree * (MyLib_PI / 180.0f);
		}

		/**
		 * 設定した角度の距離分の移動量を求める
		 * @param[in] _movement 移動量
		 * @param[in] _angle 角度(degree値)
		 * @return 移動量
		 */
		VECTOR2 GetAngleMovePos(float _movement, float _angle);

		/**
		 * 単位行列を作成する
		 * @param[in,out] _pMatrix 単位行列の入るMATRIX構造体のポインタ
		 * @return 単位行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixIdentity(MATRIX* _pMatrix);

		/**
		 * 転置行列を返す
		 * @param[in,out] _pMatrix 転置行列の入るMATRIX構造体のポインタ
		 * @return 転置行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixTranspose(MATRIX* _pMatrix);

		/**
		 * 平行移動行列を作成する
		 * @param[in,out] _pMatrix 平行移動行列の入るMATRIX構造体のポインタ
		 * @param[in] _x x座標
		 * @param[in] _y y座標
		 * @param[in] _z z座標
		 * @return 平行移動行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixTranslation(MATRIX* _pMatrix, float _x, float _y, float _z);
		
		/**
		 * スケーリング行列を作成する
		 * @param[in,out] _pMatrix スケーリング行列の入るMATRIX構造体のポインタ
		 * @param[in] _x x座標
		 * @param[in] _y y座標
		 * @param[in] _z z座標
		 * @return スケーリング行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixScaling(MATRIX* _pMatrix, float _x, float _y, float _z);

		/**
		 * X軸を回転軸にして回転する行列を作成する
		 * @param[in,out] _pMatrix 計算結果の入るMATRIX構造体のポインタ
		 * @param[in] _angle 回転角度(degree値)
		 * @return 計算結果のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixRotationX(MATRIX* _pMatrix, float _angle);

		/**
		 * Y軸を回転軸にして回転する行列を作成する
		 * @param[in,out] _pMatrix 計算結果の入るMATRIX構造体のポインタ
		 * @param[in] _angle 回転角度(degree値)
		 * @return 計算結果のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixRotationY(MATRIX* _pMatrix, float _angle);

		/**
		 * Z軸を回転軸にして回転する行列を作成する
		 * @param[in,out] _pMatrix 計算結果の入るMATRIX構造体のポインタ
		 * @param[in] _angle 回転角度(degree値)
		 * @return 計算結果のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixRotationZ(MATRIX* _pMatrix, float _angle);

	}
}


#endif

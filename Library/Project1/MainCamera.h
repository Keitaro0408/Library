/**
* @file   MainCamera.h
* @brief  MainCameraクラスのヘッダファイル
* @author kotani
*/
#ifndef MAINCAMERA_H
#define MAINCAMERA_H
#include "Library\Camera\Camera.h"

#include <D3DX11.h>
#include "Library\ObjectBase\ObjectBase.h"
#include "Library\Math\Math.h"

/**
 * カメラを操作するクラス
 */
class MainCamera : public Lib::ObjectBase
{
public:
	/**
	 * MainCameraクラスのコンストラクタ
	 */
	MainCamera();

	/**
	 * MainCameraクラスのデストラクタ
	 */
	~MainCamera();

	/**
	 * MainCameraクラスの制御関数
	 */
	void Update() override;

	void Draw() override{};

private:
	MainCamera(const MainCamera&);
	void operator=(const MainCamera&);

	/**
	 * シェーダー用コンスタントバッファ
	 */
	struct SHADER_CONSTANT_BUFFER
	{
		Lib::MATRIX View;
		Lib::MATRIX Proj;
	};

	/**
	 * カメラを移動させる関数
	 */
	void Move();

	/**
	 * コンスタントバッファ初期化関数
	 */
	void InitConstantBuffer();

	/**
	 * コンスタントバッファの開放関数
	 */
	void ReleaseConstantBuffer();

	/**
	 * コンスタントバッファへの書き込み関数
	 */
	void WriteConstantBuffer();

	static const float		 m_NearPoint;   //!< カメラの最近点
	static const float		 m_FarPoint;    //!< カメラの最遠点
	static const float		 m_ViewAngle;   //!< カメラの視野角

	Lib::Camera*			 m_pCamera;
	Lib::VECTOR3			 m_LookPoint; //!< カメラの注視点
	Lib::VECTOR3			 m_Pos;
	ID3D11Buffer*			 m_pConstantBuffer;

};


#endif
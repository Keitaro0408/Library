/**
* @file   MainCamera.h
* @brief  MainCamera�N���X�̃w�b�_�t�@�C��
* @author kotani
*/
#ifndef MAINCAMERA_H
#define MAINCAMERA_H
#include "Library\Camera\Camera.h"

#include <D3DX11.h>
#include "Library\ObjectBase\ObjectBase.h"
#include "Library\Math\Math.h"

/**
 * �J�����𑀍삷��N���X
 */
class MainCamera : public Lib::ObjectBase
{
public:
	/**
	 * MainCamera�N���X�̃R���X�g���N�^
	 */
	MainCamera();

	/**
	 * MainCamera�N���X�̃f�X�g���N�^
	 */
	~MainCamera();

	/**
	 * MainCamera�N���X�̐���֐�
	 */
	void Update() override;

	void Draw() override{};

private:
	MainCamera(const MainCamera&);
	void operator=(const MainCamera&);

	/**
	 * �V�F�[�_�[�p�R���X�^���g�o�b�t�@
	 */
	struct SHADER_CONSTANT_BUFFER
	{
		Lib::MATRIX View;
		Lib::MATRIX Proj;
	};

	/**
	 * �J�������ړ�������֐�
	 */
	void Move();

	/**
	 * �R���X�^���g�o�b�t�@�������֐�
	 */
	void InitConstantBuffer();

	/**
	 * �R���X�^���g�o�b�t�@�̊J���֐�
	 */
	void ReleaseConstantBuffer();

	/**
	 * �R���X�^���g�o�b�t�@�ւ̏������݊֐�
	 */
	void WriteConstantBuffer();

	static const float		 m_NearPoint;   //!< �J�����̍ŋߓ_
	static const float		 m_FarPoint;    //!< �J�����̍ŉ��_
	static const float		 m_ViewAngle;   //!< �J�����̎���p

	Lib::Camera*			 m_pCamera;
	Lib::VECTOR3			 m_LookPoint; //!< �J�����̒����_
	Lib::VECTOR3			 m_Pos;
	ID3D11Buffer*			 m_pConstantBuffer;

};


#endif
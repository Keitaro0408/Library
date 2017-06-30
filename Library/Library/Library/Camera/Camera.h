/**
* @file   Camera.h
* @brief  Camera�N���X�̃w�b�_�t�@�C��
* @author kotani
*/
#ifndef CAMERA_H
#define CAMERA_H
#include "../Math/Math.h"

namespace Lib
{
	/**
	* �J���������Ǘ�����N���X
	*/
	class Camera
	{
	public:
		/**
		* Camera�N���X�̃R���X�g���N�^
		* @param[in] _windowWidth �E�B���h�E�̕�
		* @param[in] _windowHeight �E�B���h�E�̍���
		* @param[in] _nearZ �J�����̍ŋߓ_
		* @param[in] _farZ �J�����̍ŉ��_
		*/
		Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ);

		/**
		* Camera�N���X�̃f�X�g���N�^
		*/
		~Camera() = default;

		/**
		* ���W�ϊ��p�̍s����쐬����֐�
		* @param[in] _eyePos �J�����̍��W
		* @param[in] _lookPos �J�����̒������W
		* @param[in] _viewAngle �J�����̎���p
		*/
		void TransformView(VECTOR3 _eyePos, VECTOR3 _lookPos, float _viewAngle);

		/**
		* Camera�N���X�����r���[���W�ϊ��s����擾����֐�
		* @return �r���[���W�ϊ��p�s��
		*/
		inline MATRIX GetViewMatrix()
		{
			return m_MatView;
		}

		/**
		* Camera�N���X�����v���W�F�N�V�������W�ϊ��s����擾����֐�
		* @return �v���W�F�N�V�������W�ϊ��p�s��
		*/
		inline MATRIX GetProjectionMatrix()
		{
			return m_MatProj;
		}

	private:
		MATRIX	m_MatView;
		MATRIX	m_MatProj;
		float	m_WindowWidth;
		float	m_WindowHeight;
		float	m_NearZ;
		float	m_FarZ;

	};
}


#endif

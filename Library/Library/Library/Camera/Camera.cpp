/**
* @file   Camera.cpp
* @brief  Camera�N���X�̎���
* @author kotani
*/
#include "Camera.h"

namespace Lib
{
	Camera::Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ)
	{
		m_WindowWidth = _windowWidth;
		m_WindowHeight = _windowHeight;
		m_NearZ = _nearZ;
		m_FarZ = _farZ;
	}

	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	void Camera::TransformView(VECTOR3 _eyePos, VECTOR3 _lookPos, float _viewAngle)
	{
		// �r���[���W�ϊ��s��̍쐬
		Math::MatrixLookAtLH(&m_MatView, &_eyePos, &_lookPos);

		// �v���W�F�N�V�������W�ϊ��s��̍쐬
		float Aspect = m_WindowWidth / m_WindowHeight;
		Math::MatrixPerspectiveFovLH(&m_MatProj, static_cast<float>(Math::ToRadian(_viewAngle)), Aspect, m_NearZ, m_FarZ);
	}
}

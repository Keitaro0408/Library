/**
* @file   MainCamera.cpp
* @brief  MainCameraƒNƒ‰ƒX‚ÌŽÀ‘•
* @author kotani
*/
#include "MainCamera.h"
#include "Library\DX11\DX11Manager.h"

const float MainCamera::m_NearPoint = 1.f;
const float MainCamera::m_FarPoint = 5000.f;
const float MainCamera::m_ViewAngle = static_cast<float>(Lib::Math::ToRadian(50));


MainCamera::MainCamera() :
m_Pos(Lib::VECTOR3(0.5f, 0.f, -100.f)),
m_LookPoint(Lib::VECTOR3(0.f, 0.f, 0.f))
{
	RECT ClientRect;
	m_pCamera = new Lib::Camera(1280.f, 720.f, m_NearPoint, m_FarPoint);

	InitConstantBuffer();
	m_pCamera->TransformView(m_Pos, m_LookPoint, m_ViewAngle);
	WriteConstantBuffer();
	InitializeTask();
}

MainCamera::~MainCamera()
{
	FinalizeTask();
	ReleaseConstantBuffer();
	delete m_pCamera;
}

void MainCamera::Update()
{
	WriteConstantBuffer();
	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_pConstantBuffer);
	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_pConstantBuffer);
}

void MainCamera::Move()
{
}

void MainCamera::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ConstantBufferDesc.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;
	SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice()->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer);
}

void MainCamera::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}

void MainCamera::WriteConstantBuffer()
{
	D3D11_MAPPED_SUBRESOURCE SubResourceData;
	if (SUCCEEDED(SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResourceData)))
	{
		SHADER_CONSTANT_BUFFER ConstantBuffer;
		ConstantBuffer.Proj = m_pCamera->GetProjectionMatrix();
		ConstantBuffer.View = m_pCamera->GetViewMatrix();

		ConstantBuffer.View = *Lib::Math::MatrixTranspose(&ConstantBuffer.View);
		ConstantBuffer.Proj = *Lib::Math::MatrixTranspose(&ConstantBuffer.Proj);
		memcpy_s(SubResourceData.pData, SubResourceData.RowPitch, static_cast<void*>(&ConstantBuffer), sizeof(ConstantBuffer));
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->Unmap(m_pConstantBuffer, 0);
	}
}
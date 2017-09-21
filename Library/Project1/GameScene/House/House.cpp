#include "House.h"
#include "Library\Helper\Helper.h"
#include "Library\Shader\ShaderManager.h"
#include "Library\Fbx\FbxFileManager\FbxFileManager.h"


House::House()
{
	m_Scale = Lib::VECTOR3(1, 1, 1);
	m_Rotate = Lib::VECTOR3(0, 0, 0);
	m_Pos = Lib::VECTOR3(0, 0, 100);

	if (!SINGLETON_INSTANCE(Lib::ShaderManager).LoadVertexShader(
		TEXT("test.hlsl"),
		"VS",
		&m_VertexShaderIndex))
	{
	}

	if (!SINGLETON_INSTANCE(Lib::ShaderManager).LoadPixelShader(
		TEXT("test.hlsl"),
		"PS",
		&m_PixelShaderIndex))
	{
	}
	CreateVertexLayout();
	CreateDepthStencilState();
	CreateConstantBuffer();

	SINGLETON_INSTANCE(Lib::FbxFileManager).LoadFbxModel("house_red.fbx", &m_ModelIndex);

	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice()->CreateSamplerState(&SamplerDesc, &m_pSamplerState);

	InitializeTask();
}


House::~House()
{
	FinalizeTask();
	m_pSamplerState->Release();
	m_pSamplerState = nullptr;
	SINGLETON_INSTANCE(Lib::FbxFileManager).ReleaseFbxModel(m_ModelIndex);
	SINGLETON_INSTANCE(Lib::ShaderManager).ReleasePixelShader(m_PixelShaderIndex);
	SINGLETON_INSTANCE(Lib::ShaderManager).ReleaseVertexShader(m_VertexShaderIndex);
	ReleaseVertexLayout();
	ReleaseDepthStencilState();
	ReleaseConstantBuffer();
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void House::Update()
{

}

void House::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState);

	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->
		VSSetShader(SINGLETON_INSTANCE(Lib::ShaderManager).GetVertexShader(m_VertexShaderIndex), nullptr, 0);

	SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext()->
		PSSetShader(SINGLETON_INSTANCE(Lib::ShaderManager).GetPixelShader(m_PixelShaderIndex), nullptr, 0);

	WriteConstantBuffer();
	VertexLayoutSetup();
	DepthStencilStateSetup();
	ConstantBufferSetup();
	SINGLETON_INSTANCE(Lib::FbxFileManager).GetFbxModel(m_ModelIndex)->Draw();
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

bool House::WriteConstantBuffer()
{
	ID3D11DeviceContext* pContext = SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext();

	D3D11_MAPPED_SUBRESOURCE SubResourceData;
	if (SUCCEEDED(pContext->Map(
		m_pConstantBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&SubResourceData)))
	{
		Lib::MATRIX MatWorld, MatTranslate, MatRotateX, MatRotateY;
		Lib::Math::MatrixIdentity(&MatWorld);
		Lib::Math::MatrixScaling(&MatWorld, m_Scale.x, m_Scale.y, m_Scale.z);
		Lib::Math::MatrixRotationX(&MatRotateX, m_Rotate.x);
		MatWorld *= MatRotateX;
		Lib::Math::MatrixRotationY(&MatRotateY, m_Rotate.y);
		MatWorld *= MatRotateY;
		Lib::Math::MatrixTranslation(&MatTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
		MatWorld *= MatTranslate;
		CONSTANT_BUFFER ConstantBuffer;
		ConstantBuffer.World = MatWorld;
		Lib::Math::MatrixTranspose(&ConstantBuffer.World);

		memcpy_s(
			SubResourceData.pData,
			SubResourceData.RowPitch,
			reinterpret_cast<void*>(&ConstantBuffer),
			sizeof(ConstantBuffer));

		pContext->Unmap(m_pConstantBuffer, 0);

		return true;
	}

	return false;
}

bool House::CreateVertexLayout()
{
	Lib::ShaderManager& pShaderManager = SINGLETON_INSTANCE(Lib::ShaderManager);

	// 入力レイアウトの設定.
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	//// 入力レイアウトの生成.
	if (FAILED(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice()->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		pShaderManager.GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferPointer(),
		pShaderManager.GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferSize(),
		&m_pVertexLayout)))
	{
		return false;
	}

	return true;
}

bool House::CreateDepthStencilState()
{
	// 深度ステンシルステートの設定.
	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
	ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
	DepthStencilDesc.DepthEnable = TRUE;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencilDesc.StencilEnable = FALSE;

	// 深度ステンシルステートの生成.
	if (FAILED(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice()->CreateDepthStencilState(
		&DepthStencilDesc,
		&m_pDepthStencilState)))
	{
		return false;
	}

	return true;
}

bool House::CreateConstantBuffer()
{
	// 定数バッファの設定.
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ConstantBufferDesc.ByteWidth = sizeof(CONSTANT_BUFFER);
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;

	// 定数バッファの生成.
	if (FAILED(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice()->CreateBuffer(
		&ConstantBufferDesc,
		nullptr,
		&m_pConstantBuffer)))
	{
		return false;
	}

	return true;
}

void House::VertexLayoutSetup()
{
	ID3D11DeviceContext* pContext = SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext();
	pContext->IASetInputLayout(m_pVertexLayout);
}

void House::DepthStencilStateSetup()
{
	ID3D11DeviceContext* pContext = SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext();

	pContext->OMSetDepthStencilState(m_pDepthStencilState, 0);
}

void House::ConstantBufferSetup()
{
	ID3D11DeviceContext* pContext = SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext();

	pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	pContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

void House::ReleaseVertexLayout()
{
	m_pVertexLayout->Release();
	m_pVertexLayout = nullptr;
}
void House::ReleaseDepthStencilState()
{
	m_pDepthStencilState->Release();
	m_pDepthStencilState = nullptr;
}
void House::ReleaseConstantBuffer()
{
	m_pConstantBuffer->Release();
	m_pConstantBuffer = nullptr;
}

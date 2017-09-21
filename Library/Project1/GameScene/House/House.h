#include "Library\Dx11\DX11Manager.h"
#include "Library\Math\Math.h"
#include "Library\ObjectBase\ObjectBase.h"

class House : public Lib::ObjectBase
{
public:
	House();
	virtual ~House();

	void Update() override;
	void Draw() override;

private:
	struct CONSTANT_BUFFER
	{
		Lib::MATRIX World;	//!< ���[���h�ϊ��s��.
	};

	bool CreateVertexLayout();
	bool CreateDepthStencilState();
	bool CreateConstantBuffer();

	void VertexLayoutSetup();
	void DepthStencilStateSetup();
	void ConstantBufferSetup();

	void ReleaseVertexLayout();
	void ReleaseDepthStencilState();
	void ReleaseConstantBuffer();

	bool WriteConstantBuffer();

	int m_ModelIndex;
	int m_VertexShaderIndex;
	int m_PixelShaderIndex;

	Lib::VECTOR3				m_Pos;
	Lib::VECTOR3				m_Scale;
	Lib::VECTOR3				m_Rotate;

	ID3D11InputLayout*			m_pVertexLayout;		//!< ���_���̓��C�A�E�g.
	ID3D11DepthStencilState*	m_pDepthStencilState;	//!< �[�x�X�e���V���X�e�[�g.
	ID3D11Buffer*				m_pConstantBuffer;		//!< �萔�o�b�t�@.
	ID3D11SamplerState*			m_pSamplerState;

};


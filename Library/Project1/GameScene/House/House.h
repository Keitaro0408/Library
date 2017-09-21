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
		Lib::MATRIX World;	//!< ワールド変換行列.
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

	ID3D11InputLayout*			m_pVertexLayout;		//!< 頂点入力レイアウト.
	ID3D11DepthStencilState*	m_pDepthStencilState;	//!< 深度ステンシルステート.
	ID3D11Buffer*				m_pConstantBuffer;		//!< 定数バッファ.
	ID3D11SamplerState*			m_pSamplerState;

};


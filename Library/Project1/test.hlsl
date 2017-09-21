Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

struct pixcelIn
{
	float4 Pos : SV_POSITION;
	float4 Col : COLOR;
	float2 Tex : TEXCOORD0;
};

cbuffer camera : register(b1)
{
	matrix g_View;
	matrix g_Proj;
};

cbuffer model : register(b0)
{
	matrix g_World;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
	float2 Tex	: TEXCOORD;
};

//バーテックスシェーダー
VS_OUT VS(float4 Pos : POSITION, float4 Normal : NORMAL, float2 Tex : TEXCOORD)
{
	VS_OUT Out;
	Out.Pos = mul(Pos, g_World);
	Out.Pos = mul(Out.Pos, g_View);
	Out.Pos = mul(Out.Pos, g_Proj);
	Out.Normal = Normal;
	Out.Tex = Tex;
	return Out;
}

//ピクセルシェーダー
float4 PS(VS_OUT IN) : SV_Target
{
	pixcelIn OUT;

	//テクスチャーを貼る
	OUT.Col = txDiffuse.Sample(samLinear, IN.Tex);
	//return float4(1.0f, 0.5f, 0.0f, 1.0f);

	return OUT.Col;
}
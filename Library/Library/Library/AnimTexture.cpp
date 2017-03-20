/**
 * @file   AnimTexture.cpp
 * @brief  AnimTextureクラスの実装
 * @author kotani
 */
#include "AnimTexture.h"
#include "AnimFileParser.h"


Lib::AnimTexture::AnimTexture() : 
m_Count(0),
m_AnimCount(1)
{
	m_pAnimFileParser = new AnimFileParser();
}

Lib::AnimTexture::~AnimTexture()
{
	delete m_pAnimFileParser;
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::AnimTexture::LoadAnimation(LPCTSTR _pFileName, LPCTSTR _pAnimName)
{
	m_pAnimFileParser->FileLoad(_pFileName);
	std::vector<float> Data;
	std::vector<float> TextureSize;
	if (!m_pAnimFileParser->ReadData("TextureSize", &TextureSize))
	{
		OutputDebugString(TEXT("テクスチャのサイズが不明です"));
		return false;
	}

	if (!m_pAnimFileParser->ReadData(_pAnimName, &Data))
	{
		OutputDebugString(TEXT("指定のアニメーション名が存在しません"));
		return false;
	}

	// tu座標
	m_TextureSize.x = TextureSize[0];
	// tv座標
	m_TextureSize.y = TextureSize[1];

	m_AnimData.LeftUpX = Data[0];
	m_AnimData.LeftUpY = Data[1];
	m_AnimData.Width = Data[2];
	m_AnimData.Height = Data[3];
	m_AnimData.AnimNum = static_cast<int>(Data[4]);
	
	m_ScrollUV.x = (m_AnimData.LeftUpX + m_AnimData.Width) / m_TextureSize.x;
	m_ScrollUV.y = 0;

	m_UV[0].x = m_AnimData.LeftUpX / m_TextureSize.x;
	m_UV[0].y = m_AnimData.LeftUpY / m_TextureSize.y;
	
	m_UV[1].x = (m_AnimData.LeftUpX + m_AnimData.Width) / m_TextureSize.x;
	m_UV[1].y = m_UV[0].y;
	
	m_UV[2].x = m_UV[0].x;
	m_UV[2].y = (m_AnimData.LeftUpY + m_AnimData.Height) / m_TextureSize.y;
	
	m_UV[3].x = m_UV[1].x;
	m_UV[3].y = m_UV[2].y;

	for (int i = 0; i < 4; i++)
	{
		m_NowUV[i] = m_UV[i];
	}

	return true;
}

void Lib::AnimTexture::Control(bool _isReverse)
{
	m_Count++;
	if (_isReverse)
	{
		if (m_ScrollFrame < m_Count)
		{
			m_Count = 0;
		
			if (m_AnimCount >= m_AnimData.AnimNum)
			{
				m_AnimCount = 0;
			}

			for (int i = 0; i < 4; i++)
			{
				m_NowUV[i].x = m_UV[i].x + m_AnimCount * m_ScrollUV.x;
			}

			m_AnimCount++;
		}
	}
	else
	{
		if (m_ScrollFrame < m_Count)
		{
			m_Count = 0;

			if (m_AnimCount <= 1)
			{
				m_AnimCount = m_AnimData.AnimNum;
			}

			for (int i = 0; i < 4; i++)
			{
				m_NowUV[i].x = m_UV[i].x + m_AnimCount * m_ScrollUV.x;
			}

			m_AnimCount++;
		}
	}
}

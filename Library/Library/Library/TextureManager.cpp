/**
 * @file   TextureManager.cpp
 * @brief  TextureManagerクラスの実装
 * @author kotani
 */
#include "TextureManager.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Lib::TextureManager::ReleaseTexture(int _index)
{
	if (m_pTextureResourceView[_index] != NULL)
	{
		m_pTextureResourceView[_index]->Release();
		m_pTextureResourceView[_index] = NULL;
	}
}

void Lib::TextureManager::Add(ID3D11ShaderResourceView* _pTextureResourceView, int* _index)
{
	if (_pTextureResourceView != NULL)
	{
		*_index = m_pTextureResourceView.size();
		m_pTextureResourceView.push_back(_pTextureResourceView);
	}
}
/**
 * @file   DSoundContainer.cpp
 * @brief  DSoundContainerクラスの実装
 * @author kotani
 */
#include "DSoundContainer.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Lib::DSoundContainer::Add(LPDIRECTSOUNDBUFFER8 _pSound, int* _index)
{
	if (_pSound != NULL)
	{
		*_index = m_pSound.size();
		m_pSound.push_back(_pSound);
	}
}

void Lib::DSoundContainer::ReleaseSound(int _index)
{
	if (m_pSound[_index] != NULL)
	{
		m_pSound[_index]->Release();
		m_pSound[_index] = NULL;
	}
}

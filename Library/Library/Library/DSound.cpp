/**
 * @file   DSoundManager.cpp
 * @brief  DSoundManagerクラスの実装
 * @author kotani
 */
#include "DSound.h"
#include <mmsystem.h>


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DSound::Init(HWND _hWnd)
{
	if (m_pDSound8 != NULL)
	{
		MessageBox(_hWnd, TEXT("DSoundManagerはすでに初期化されています"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_hWnd = _hWnd;

	if (FAILED(DirectSoundCreate8(NULL, &m_pDSound8, NULL)))
	{
		MessageBox(m_hWnd, TEXT("サウンドデバイスの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDSound8->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL)))
	{
		MessageBox(m_hWnd, TEXT("協調レベルの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDSound8->Release();
		return false;
	}
	return true;
}

void Lib::DSound::Release()
{
	if (m_pDSound8 != NULL)
	{
		m_pDSound8->Release();
		m_pDSound8 = NULL;
	}
}

void Lib::DSound::SoundOperation(LPDIRECTSOUNDBUFFER8 _pSoundBuffer, SOUND_OPERATION _operation)
{
	switch (_operation)
	{
	case SOUND_PLAY:
		_pSoundBuffer->Play(0, 0, 0);
		break;
	case SOUND_LOOP:
		_pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case SOUND_STOP:
		_pSoundBuffer->Stop();
		break;
	case SOUND_RESET:
		_pSoundBuffer->SetCurrentPosition(0);
		break;
	case SOUND_STOP_RESET:
		_pSoundBuffer->Stop();
		_pSoundBuffer->SetCurrentPosition(0);
		break;
	}
}

void Lib::DSound::SetVolume(LPDIRECTSOUNDBUFFER8 _pSoundBuffer, int _volume)
{
	if (_volume > DSBVOLUME_MAX)
	{
		_volume = DSBVOLUME_MAX;
	}
	else if (_volume < DSBVOLUME_MIN)
	{
		_volume = DSBVOLUME_MIN;
	}
	_pSoundBuffer->SetVolume(_volume);
}

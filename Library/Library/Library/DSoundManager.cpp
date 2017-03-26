#include "DSoundManager.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DSoundManager::Init(HWND _hWnd)
{
	if (m_pDSound8 != NULL)
	{
		OutputDebugString(TEXT("DSoundManagerはすでに初期化されています"));
		return false;
	}

	m_hWnd = _hWnd;

	if (FAILED(DirectSoundCreate8(NULL, &m_pDSound8, NULL)))
	{
		OutputDebugString(TEXT("サウンドデバイスの生成に失敗しました"));
		return false;
	}

	if (FAILED(m_pDSound8->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL)))
	{
		OutputDebugString(TEXT("協調レベルの設定に失敗しました"));
		m_pDSound8->Release();
		return false;
	}
	SINGLETON_CREATE(DSoundContainer);
	return true;
}

void Lib::DSoundManager::Release()
{
	SINGLETON_DELETE(DSoundContainer);
	if (m_pDSound8 != NULL)
	{
		m_pDSound8->Release();
		m_pDSound8 = NULL;
	}
}

void Lib::DSoundManager::SoundOperation(int _index, SOUND_OPERATION _operation)
{
	switch (_operation)
	{
	case SOUND_PLAY:
		SINGLETON_INSTANCE(DSoundContainer).GetSound(_index)->Play(0, 0, 0);
		break;
	case SOUND_LOOP:
		SINGLETON_INSTANCE(DSoundContainer).GetSound(_index)->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case SOUND_STOP:
		SINGLETON_INSTANCE(DSoundContainer).GetSound(_index)->Stop();
		break;
	case SOUND_START_PLAY:
		SINGLETON_INSTANCE(DSoundContainer).GetSound(_index)->SetCurrentPosition(0);
		break;
	case SOUND_STOP_RESET:
		SINGLETON_INSTANCE(DSoundContainer).GetSound(_index)->Stop();
		SINGLETON_INSTANCE(DSoundContainer).GetSound(_index)->SetCurrentPosition(0);
		break;
	}
}

void Lib::DSoundManager::SetVolume(int _index, int _volume)
{
	if (_volume > DSBVOLUME_MAX)
	{
		_volume = DSBVOLUME_MAX;
	}
	else if (_volume < DSBVOLUME_MIN)
	{
		_volume = DSBVOLUME_MIN;
	}
	SINGLETON_INSTANCE(DSoundContainer).GetSound(_index)->SetVolume(_volume);
}

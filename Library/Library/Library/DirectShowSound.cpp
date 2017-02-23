/**
 * @file   DSound.cpp
 * @brief  DSoundクラスの実装
 * @author kotani
 */
#include "DirectShowSound.h"


bool Lib::DirectShowSound::LoadMediaSound(CString _fileName, int* _index)
{
	Sound* pSound = new Sound();
	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (LPVOID *)&pSound->pGraphBuilder);

	pSound->pGraphBuilder->QueryInterface(IID_IMediaPosition, (LPVOID *)&pSound->pMediaPosition);
	pSound->pGraphBuilder->QueryInterface(IID_IMediaControl, (LPVOID *)&pSound->pMediaControl);
	if (FAILED(pSound->pMediaControl->RenderFile(_fileName.AllocSysString())))
	{
		MessageBox(NULL, TEXT("音声の読み込みに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		pSound->pMediaControl->Release();
		pSound->pMediaControl = NULL;

		pSound->pMediaPosition->Release();
		pSound->pMediaPosition = NULL;

		pSound->pGraphBuilder->Release();
		pSound->pGraphBuilder = NULL;

		delete pSound;
		pSound = NULL;

		return false;
	}
	pSound->isLoop = false;
	*_index = m_pSound.size();
	m_pSound.push_back(pSound);
	return true;
}

void Lib::DirectShowSound::SoundOperation(int _index, SOUND_OPERATION _operation)
{
	switch (_operation)
	{
	case SOUND_PLAY:
		m_pSound[_index]->isLoop = false;
		m_pSound[_index]->pMediaControl->Run();
		break;
	case SOUND_LOOP:
		m_pSound[_index]->isLoop = true;
		m_pSound[_index]->pMediaControl->Run();
		break;
	case SOUND_STOP:
		m_pSound[_index]->isLoop = false;
		m_pSound[_index]->pMediaControl->Pause();
		break;
	case SOUND_START_PLAY:
		m_pSound[_index]->isLoop = false;
		m_pSound[_index]->pMediaPosition->put_CurrentPosition(0);
		m_pSound[_index]->pMediaControl->Run();
		break;
	case SOUND_STOP_RESET:
		m_pSound[_index]->isLoop = false;
		m_pSound[_index]->pMediaControl->Stop();
		m_pSound[_index]->pMediaPosition->put_CurrentPosition(0);
		break;
	}
}

void Lib::DirectShowSound::CheckLoop(int _index)
{
	if (m_pSound[_index]->isLoop)
	{
		REFTIME pos, end;
		m_pSound[_index]->pMediaPosition->get_CurrentPosition(&pos);
		m_pSound[_index]->pMediaPosition->get_StopTime(&end);
		if (pos >= end)
		{
			m_pSound[_index]->pMediaControl->Stop();
			m_pSound[_index]->pMediaPosition->put_CurrentPosition(0);
			m_pSound[_index]->pMediaControl->Run();
		}
	}
}

void Lib::DirectShowSound::ReleaseMediaSound(int _index)
{
	m_pSound[_index]->pMediaPosition->Release();
	m_pSound[_index]->pMediaPosition = NULL;

	m_pSound[_index]->pMediaControl->Release();
	m_pSound[_index]->pMediaControl = NULL;

	m_pSound[_index]->pGraphBuilder->Release();
	m_pSound[_index]->pGraphBuilder = NULL;
	
	CoUninitialize();

	delete m_pSound[_index];
	m_pSound[_index] = NULL;
}

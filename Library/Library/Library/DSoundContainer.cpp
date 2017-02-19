/**
 * @file   DSoundContainer.cpp
 * @brief  DSoundContainerクラスの実装
 * @author kotani
 */
#include "DSoundContainer.h"


void Lib::DSoundContainer::Init(HWND _hWnd, IDirectSound8& _pDSound8)
{
	m_hWnd = _hWnd;
	m_pDSound8 = &_pDSound8;
}

bool Lib::DSoundContainer::LoadSound(LPSTR _pFileName, int* _pIndex)
{
	WAVEFORMATEX WaveFormat;
	BYTE* pWaveData = NULL;
	DWORD WaveSize = 0;

	if (!ReadWave(_pFileName, &WaveFormat, &pWaveData, &WaveSize))
	{
		MessageBox(m_hWnd, TEXT("waveファイルが開けませんでした"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	DSBufferDesc.dwBufferBytes = WaveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &WaveFormat;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	LPDIRECTSOUNDBUFFER pTmpBufer = NULL;
	m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &pTmpBufer, NULL);
	pTmpBufer->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<void**>(&pDSBuffer));
	pTmpBufer->Release();

	if (pDSBuffer == NULL)
	{
		MessageBox(m_hWnd, TEXT("サウンドバッファ作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	LPVOID pWriteData = 0;
	DWORD WriteDataLength = 0;
	if (FAILED(pDSBuffer->Lock(0, 0, &pWriteData, &WriteDataLength, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
	{
		delete[] pWaveData;
		MessageBox(m_hWnd, TEXT("サウンドバッファのロックに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	memcpy(pWriteData, pWaveData, WriteDataLength);
	pDSBuffer->Unlock(pWriteData, WriteDataLength, NULL, 0);
	delete[] pWaveData;

	*_pIndex = m_pSound.size();
	m_pSound.push_back(pDSBuffer);

	return true;
}

void Lib::DSoundContainer::ReleaseSound(int _index)
{
	if (m_pSound[_index] != NULL)
	{
		m_pSound[_index]->Release();
		m_pSound[_index] = NULL;
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DSoundContainer::ReadWave(LPSTR _pFileName, WAVEFORMATEX* _pWaveFormat, BYTE** _pWaveData, DWORD* _pWaveSize)
{
	if (_pFileName == NULL)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO MmioInfo;
	ZeroMemory(&MmioInfo, sizeof(MMIOINFO));
	hMmio = mmioOpen(_pFileName, &MmioInfo, MMIO_READ);
	if (!hMmio)
	{
		return false;
	}

	// RIFFチャンク検索
	MMRESULT Result;
	MMCKINFO RiffChunk;
	RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	Result = mmioDescend(hMmio, &RiffChunk, NULL, MMIO_FINDRIFF);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	// fmtチャンク検索
	MMCKINFO FormatChunk;
	FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	Result = mmioDescend(hMmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	DWORD FormatSize = FormatChunk.cksize;
	DWORD WaveDataSize = mmioRead(hMmio, reinterpret_cast<HPSTR>(_pWaveFormat), FormatSize);
	if (WaveDataSize != FormatSize)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &FormatChunk, 0);

	// dataチャンク検索
	MMCKINFO DataChunk;
	DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	Result = mmioDescend(hMmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	*_pWaveData = new BYTE[DataChunk.cksize];
	WaveDataSize = mmioRead(hMmio, reinterpret_cast<HPSTR>(*_pWaveData), DataChunk.cksize);
	if (WaveDataSize != DataChunk.cksize)
	{
		delete[] * _pWaveData;
		mmioClose(hMmio, 0);
		return false;
	}

	*_pWaveSize = WaveDataSize;
	mmioClose(hMmio, 0);

	return true;
}

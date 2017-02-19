/**
 * @file   SoundContainer.h
 * @brief  SoundContainerクラスのヘッダファイル
 * @author kotani
 */
#ifndef SOUNDCONTAINER_H
#define SOUNDCONTAINER_H
#include <dsound.h>
#include <vector>
#include "Singleton.h"

namespace Lib
{
	class SoundContainer
	{
		friend Singleton<SoundContainer>;
	public:
		/**
		 * 初期化処理
		 * @param[in] _hWnd ウィンドウハンドル
		 * @param[in] _pDSound8 directsoundのインターフェイス
		 */
		void Init(HWND _hWnd,IDirectSound8* _pDSound8);

		/**
		 * 音声の読み込み
		 * @param[in] _pFileName 読み込むファイルの名前
		 * @param[out] _pIndex データの格納先のインデックス
		 * @return 成功したらtrue
		 */
		bool LoadSound(LPSTR _pFileName, int* _pIndex);

		/**
		 * 音声の開放
		 * @param[in] _index 開放先のインデックス
		 */
		void ReleaseSound(int _index);
		
		/**
		 * 音声の取得
		 * @param[in] _index 格納先のインデックス
		 * @return 読み込んだサウンドバッファー
		 */
		inline LPDIRECTSOUNDBUFFER8 GetSound(int _index) const
		{
			return m_pSound[_index];
		}

		/**
		 * サウンドのバッファーを開放する
		 */
		inline void ClearBuffer()
		{
			m_pSound.clear();
		}

	private:
		SoundContainer() :
			m_hWnd(NULL),
			m_pDSound8(NULL){};
		~SoundContainer(){};

		/**
		 * waveファイル内のデータを読み出す関数
		 * @param[in] _pFileName 開くファイルの名前
		 * @param[out] _pWaveFormat 読み込んだwaveファイルのフォーマット
		 * @param[out] _pWaveData 読み込んだwaveファイルのデータ
		 * @param[out] _pWaveSize 読み込んだwaveファイルのサイズ
		 */
		bool ReadWave(LPSTR _pFileName, WAVEFORMATEX* _pWaveFormat, BYTE** _pWaveData, DWORD* _pWaveSize);

		HWND m_hWnd;
		std::vector<LPDIRECTSOUNDBUFFER8> m_pSound;
		IDirectSound8* m_pDSound8;

	};
}

#endif

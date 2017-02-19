/**
 * @file   DSoundManager.h
 * @brief  DSoundManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef DXSOUNDMANAGER_H
#define DXSOUNDMANAGER_H
#include <windows.h>
#include <dsound.h>
#include <vector>
#include "Singleton.h"

namespace Lib
{
	/**
	 * サウンドを操作するためのenum
	 */
	enum SOUND_OPERATION
	{
		SOUND_PLAY,		//!< サウンドを再生する
		SOUND_STOP,		//!< サウンドを停止する
		SOUND_LOOP,		//!< サウンドをループ再生する
		SOUND_RESET,	//!< サウンドをリセットする
		SOUND_STOP_RESET//!< サウンドを停止してリセットする
	};

	/**
	 * サウンドの再生をするクラス
	 */
	class DSound
	{
		friend Singleton<DSound>;
	public:
		/**
		 * DSoundManagerクラスの初期化関数
		 * @param[in] _hWnd ウィンドウハンドル。コンストラクタ内で使う
		 * @return 成功したらtrue
		 */
		bool Init(HWND _hWnd);

		/**
		 * DSoundManagerクラスの解放関数
		 */
		void Release();

		/**
		 * サウンドの操作関数
		 * @param[in] _pSoundBuffer 操作するサウンドバッファー
		 * @param[in] _operation どのような操作をするか
		 */
		void SoundOperation(LPDIRECTSOUNDBUFFER8 _pSoundBuffer, SOUND_OPERATION _operation);

		/**
		 * サウンドの音量調節
		 * @param[in] _pSoundBuffer 操作するサウンドバッファー
		 * @param[in] _volume 音量の数値(0が最大音で-10000が無音)
		 */
		void SetVolume(LPDIRECTSOUNDBUFFER8 _pSoundBuffer, int _volume);


		/**
		 * directsoundのインターフェイスを取得する
		 * @return directsoundのインターフェイス
		 */
		inline IDirectSound8* const GetIDSound()  const
		{
			return m_pDSound8;
		}

	private:
		/**
		 * DSoundクラスのコンストラクタ
		 */
		DSound() :
			m_pDSound8(NULL),
			m_hWnd(NULL){};

		/**
		 * DSoundクラスのデストラクタ
		 */
		~DSound(){};

		IDirectSound8*					  m_pDSound8;
		HWND							  m_hWnd;

	};
}


#endif

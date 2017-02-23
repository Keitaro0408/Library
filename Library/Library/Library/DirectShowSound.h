/**
 * @file   DirectShowSound.h
 * @brief  DirectShowSoundクラスのヘッダファイル
 * @author kotani
 */
#ifndef DirectShowSound_H
#define DirectShowSound_H
#include <dshow.h>
#include <vector>
#include "Singleton.h"

namespace Lib
{
	class DirectShowSound
	{
		friend Singleton<DirectShowSound>;
	public:
		void LoadMediaFile(BSTR _fileName);

	private:
		DirectShowSound();
		~DirectShowSound();

		struct MediaSound
		{
			IGraphBuilder*  pGraphBuilder;
			IMediaControl*  pMediaControl;		//ファイルの読み込み、再生停止などを行う。
			IMediaPosition* pMediaPosition;	//再生位置を指定するのに使う。
		};

		std::vector<MediaSound*> m_pMediaSound;

	};
}

#endif

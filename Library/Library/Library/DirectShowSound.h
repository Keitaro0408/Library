/**
 * @file   DirectShowSound.h
 * @brief  DirectShowSound�N���X�̃w�b�_�t�@�C��
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
			IMediaControl*  pMediaControl;		//�t�@�C���̓ǂݍ��݁A�Đ���~�Ȃǂ��s���B
			IMediaPosition* pMediaPosition;	//�Đ��ʒu���w�肷��̂Ɏg���B
		};

		std::vector<MediaSound*> m_pMediaSound;

	};
}

#endif

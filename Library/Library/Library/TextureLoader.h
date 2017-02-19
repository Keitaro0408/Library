#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#include <D3DX11.h>
#include "Singleton.h" 

namespace Lib
{
	class TextureLoader
	{
		friend Singleton<TextureLoader>;
	public:
		void Init(ID3D11Device* _pDevice)
		{
			m_pDevice = _pDevice;
		}

		/**
		 * テクスチャを読み込む関数
		 * @param[in] _pFileName 読み込むテクスチャファイルのパス
		 * @return テクスチャの読み込みに失敗したらnull
		 */
		ID3D11ShaderResourceView* Load(LPCTSTR _pFileName);

	private:
		TextureLoader(){};
		~TextureLoader(){};
		ID3D11Device* m_pDevice;

	};
}


#endif

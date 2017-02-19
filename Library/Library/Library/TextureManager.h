/**
 * @file   TextureManager.h
 * @brief  TextureManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <D3DX11.h>
#include <vector>
#include "Singleton.h"

namespace Lib
{
	/**
	 * テクスチャの管理クラス
	 */
	class TextureManager
	{
		friend Singleton<TextureManager>;
	public:
		void Add(ID3D11ShaderResourceView* _pTextureResourceView, int* _index);

		/**
		 * 格納しているテクスチャを取得する関数
		 * @param[in] _index 取得したいテクスチャのインデックス
		 * @return テクスチャのリソースビュー
		 */
		inline ID3D11ShaderResourceView* GetTexture(int _index)
		{
			return m_pTextureResourceView[_index];
		}

		/**
		 * 格納しているテクスチャを解放する関数
		 * @param[in] _index 解放したいテクスチャのインデックス
		 */
		void ReleaseTexture(int _index);

		/**
		 * テクスチャを確保しているバッファをクリアする
		 *
		 * vectorを使用しているのでバッファ領域は解放されない。\n
		 * バッファ領域はTextureManagerのDelete()が呼ばれて破棄されたときに解放される。
		 */
		inline void ClearBuffer()
		{
			m_pTextureResourceView.clear();
		}

		static const int m_InvalidIndex;	//!< TextureManagerクラスがとるインデックスのエラー値

	private:
		/**
		 * TextureManagerクラスのコンストラクタ
		 * @param[in] _pDevice テクスチャの読み込みに使用するDirectX11のデバイス
		 */
		TextureManager(ID3D11Device* _pDevice);

		/**
		 * TextureManagerクラスのデストラクタ
		 */
		~TextureManager();

		static TextureManager*						m_pTextureManager;
		std::vector<ID3D11ShaderResourceView*>		m_pTextureResourceView;

	};
}


#endif

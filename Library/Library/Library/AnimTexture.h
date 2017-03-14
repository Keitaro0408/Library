﻿/**
 * @file   AnimTexture.h
 * @brief  AnimTextureクラスのヘッダファイル
 * @author kotani
 */
#ifndef TEXTUREANIM_H
#define TEXTUREANIM_H
#include <Windows.h>
#include <D3DX10.h>


namespace Lib
{
	class AnimFileParser;

	struct Anim
	{
		float LeftUpX;
		float LeftUpY;
		float Width;
		float Height;
		int	  AnimNum;
	};

	/**
	 * 1つのテクスチャアニメーションを管理するクラス(実装途中)
	 *
	 * ファイルの構造
	 * TextureSize // テクスチャのサイズ (名前固定)
	 * {
	 *		1, // テクスチャの横幅
	 *      2  // テクスチャの横幅
	 * }
	 *
	 * Test //アニメーションの名前
	 * {
	 *		1, // 左上のテクスチャX座標
	 *		2, // 左上のテクスチャY座標
	 *      3, // テクスチャの横幅
	 *      4, // テクスチャの立幅
	 *      5  // アニメーションの数
	 * }
	 */
	class AnimTexture
	{
	public:
		AnimTexture();
		~AnimTexture();
		
		/**
		 * アニメーションファイルの読み込み
		 * @param[in] _pFileName ファイルの名前
		 * @param[in] _pAnimName アニメーションの名前
		 * @return 成功したらtrue
		 */
		bool LoadAnimation(LPCTSTR _pFileName, LPCTSTR _pAnimName);

		/**
		 * 何フレームでアニメーションを進めるか設定する
		 */
		inline void SetAnimFrame(int _scrollFrame)
		{
			m_ScrollFrame = _scrollFrame;
		}

		inline D3DXVECTOR2 GetUV()
		{
			return D3DXVECTOR2(m_ScrollUV.x * m_AnimCount, m_ScrollUV.y);
		}

		/**
		 * アニメーション制御
		 */
		void Control();

	private:
		AnimFileParser* m_pAnimFileParser;
		Anim			m_AnimData;
		D3DXVECTOR2		m_TextureSize;
		D3DXVECTOR2		m_ScrollUV;
		D3DXVECTOR2		m_UV[4];
		int				m_AnimCount;
		int				m_ScrollFrame;
		int				m_Count;

	};

}


#endif

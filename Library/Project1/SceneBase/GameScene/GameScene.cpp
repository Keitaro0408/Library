/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include <Library\Window.h>
#include <Library\TextureLoader.h>
#include <Library\DX11Manager.h>
#include <Library\DSoundManager.h>
#include <Library\DSoundContainer.h>
#include <Library\DSoundLoader.h>
#include <Library\Singleton.h>
#include <Library\DXInputDevice.h>
#include <Library\TextureManager.h>
#include <Library\DirectShowSound.h>


GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
	SINGLETON_INSTANCE(Lib::DirectShowSound).LoadMediaSound("button01a.wav", &m_SoundIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("test.png", &m_TextureIndex);

	m_Vertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());

	D3DXVECTOR2 uv[] = 
	{
		D3DXVECTOR2(0, 0),
		D3DXVECTOR2(1, 0),
		D3DXVECTOR2(0, 1),
		D3DXVECTOR2(1, 1),
	};
	m_Vertex->Init(&D3DXVECTOR2(1280, 720), uv);
	m_Vertex->WriteConstantBuffer(&D3DXVECTOR2(640, 360));
	m_Vertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureContainer).GetTexture(m_TextureIndex));
	//SINGLETON_INSTANCE(Lib::DirectShowSound).SoundOperation(m_SoundIndex, Lib::SOUND_LOOP);

}

GameScene::~GameScene()
{
	m_Vertex->Release();
	SINGLETON_INSTANCE(Lib::DirectShowSound).ReleaseMediaSound(m_SoundIndex);
	delete m_Vertex;
	SINGLETON_INSTANCE(Lib::TextureContainer).ReleaseTexture(m_TextureIndex);
	int SoundMax = SINGLETON_INSTANCE(Lib::DSoundContainer).GetSoundMaxNum();
	for (int i = 0; i < SoundMax; i++)
	{
		SINGLETON_INSTANCE(Lib::DSoundContainer).ReleaseSound(i);
	}

}

SceneBase::SceneID GameScene::Control()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_P);
	static bool isPlay = true;
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_P] == Lib::KEY_PUSH)
	{
		isPlay =! isPlay;
		SINGLETON_INSTANCE(Lib::DirectShowSound).SoundOperation(m_SoundIndex, Lib::SOUND_START_PLAY);
	}
	SINGLETON_INSTANCE(Lib::DirectShowSound).CheckLoop(m_SoundIndex);

	return m_SceneID;
}

void GameScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	m_Vertex->Draw();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();

}

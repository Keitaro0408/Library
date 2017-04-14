﻿/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include <Library\Window.h>
#include <Library\DX11Manager.h>
#include <Library\DSoundManager.h>
#include <Library\Singleton.h>
#include <Library\DXInputDevice.h>
#include <Library\TextureManager.h>
#include <Library\DirectShowSound.h>
#include <Library\DebugTimer.h>
namespace
{
	Lib::DebugTimer g_Timer(60);
	RECT Rectvar = {0,0,0,0};
}

GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
	SINGLETON_INSTANCE(Lib::DirectShowSound).LoadMediaSound("button01a.wav", &m_SoundIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Character.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::DSoundManager).Load("button01a.wav", &m_SoundIndex);

	m_Animation = new Lib::AnimTexture();
	m_Animation->LoadAnimation("Character.anim", "Wait");
	m_Animation->SetAnimFrame(5);

	m_Vertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle());

	m_Vertex->Init(&D3DXVECTOR2(256, 256), m_Animation->GetUV());
	m_Vertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureContainer).GetTexture(m_TextureIndex));
	
	//SINGLETON_INSTANCE(Lib::DirectShowSound).SoundOperation(m_SoundIndex, Lib::SOUND_LOOP);
}

GameScene::~GameScene()
{
	m_Vertex->Release();
	SINGLETON_INSTANCE(Lib::DirectShowSound).ReleaseMediaSound(m_SoundIndex);
	delete m_Vertex;
	SINGLETON_INSTANCE(Lib::TextureContainer).ReleaseTexture(m_TextureIndex);
	delete m_Animation;
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
	m_Animation->Control(false, Lib::ANIM_LOOP);
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_P] == Lib::KEY_ON)
	{
		Rectvar.right -= 1;
	}
	else if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_P] == Lib::KEY_PUSH)
	{
	}
	SINGLETON_INSTANCE(Lib::DirectShowSound).CheckLoop(m_SoundIndex);

	return m_SceneID;
}

void GameScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	g_Timer.Begin();
	m_Vertex->Draw(&D3DXVECTOR2(640, 360), &Rectvar, m_Animation->GetUV());
	g_Timer.End();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();

	g_Timer.TimerShow();
}

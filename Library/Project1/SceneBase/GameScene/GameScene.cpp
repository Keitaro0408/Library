﻿/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include <Library\Window\Window.h>
#include <Library\Dx11\DX11Manager.h>
#include <Library\Sound\DSoundManager.h>
#include <Library\Singleton.h>
#include <Library\DxInput\DXInputDevice.h>
#include <Library\Texture\TextureManager.h>
#include <Library\DebugTool\DebugTimer.h>
#include "Library/Event/EventManager.h"
#include "Library/Math/Math.h"

namespace
{
	Lib::DebugTimer g_Timer(120);
	RECT Rectvar = {0,0,0,0};
	D3DXVECTOR2 Pos;
	float g_Angle = 0.f;
}

GameScene::GameScene() :
SceneBase(SCENE_GAME)
{
	Pos.x = 400.f;
	Pos.y = 400.f;
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Character.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("button01a.wav", &m_SoundIndex);
	//SINGLETON_CREATE(Lib::EventManager);
	m_Animation = new Lib::AnimUvController();
	m_Animation->LoadAnimation("Character.anim", "Wait");
	m_Animation->SetAnimFrame(10);

	m_Vertex = new Lib::Vertex2D(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());
	
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Vertex->Init(&D3DXVECTOR2(256, 256), m_Animation->GetUV());
	m_Vertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));


	//SINGLETON_INSTANCE(Lib::DirectShowSound).SoundOperation(m_SoundIndex, Lib::SOUND_LOOP);
}

GameScene::~GameScene()
{
	m_Vertex->Release();
	delete m_Vertex;
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_SoundIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
	delete m_Animation;
}

SceneBase::SceneID GameScene::Update()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_P);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_LEFTARROW);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheck(DIK_RIGHTARROW);
	//SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_SoundIndex,Lib::DSoundManager::SOUND_PLAY);
	static bool isPlay = true;
	//if (m_Animation->Control(false, Lib::ANIM_LOOP))
	//{
	//	int animCount = m_Animation->GetAnimCount();
	//	m_Animation->GetAnimCount();
	//}

	float test = Lib::Math::GetAngle(Pos,D3DXVECTOR2(400,400));

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_LEFTARROW] == Lib::KEY_PUSH)
	{
		SINGLETON_INSTANCE(Lib::Window).ChangeWindowSize(1920,1080);
	}
	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_RIGHTARROW] == Lib::KEY_PUSH)
	{
		SINGLETON_INSTANCE(Lib::Window).ChangeWindowSize(1280, 720);
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).GetKeyState()[DIK_P] == Lib::KEY_ON)
	{
		Pos += Lib::Math::GetAngleMovePos(2.f, g_Angle - 90.f);
	}
	//SINGLETON_INSTANCE(Lib::DirectShowSound).CheckLoop(m_SoundIndex);

	return m_SceneID;
}

void GameScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	g_Timer.Begin();
	m_Vertex->Draw(&Pos, m_Animation->GetUV(),1.f,&D3DXVECTOR2(1.f,1.f),g_Angle);
	g_Timer.End();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();

	g_Timer.TimerShow();
}

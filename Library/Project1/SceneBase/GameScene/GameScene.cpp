/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include "Library/Math/Math.h"
#include <Library\Window\Window.h>
#include <Library\Dx11\DX11Manager.h>
#include <Library\Sound\DSoundManager.h>
#include <Library\Singleton.h>
#include <Library\DxInput\DXInputDevice.h>
#include <Library\Texture\TextureManager.h>
#include <Library\DebugTool\DebugTimer.h>
#include "Library/Event/EventManager.h"

namespace
{
	Lib::DebugTimer g_Timer(120);
	RECT Rectvar = {0,0,0,0};
	Lib::VECTOR2 Pos;
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
	m_Animation.Reset(new Lib::AnimUvController());

	m_Animation->LoadAnimation("Character.anim", "Wait");
	m_Animation->SetAnimFrame(10);

	m_Vertex.Reset(new Lib::Vertex2D(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize()));

	
	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Vertex->Init(Lib::VECTOR2(256, 256), m_Animation->GetUV());
	m_Vertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("front", DIK_W);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("front", DIK_UPARROW);

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("left", DIK_A);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("left", DIK_LEFTARROW);

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("right", DIK_D);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("right", DIK_RIGHTARROW);

	//SINGLETON_INSTANCE(Lib::DirectShowSound).SoundOperation(m_SoundIndex, Lib::SOUND_LOOP);
}

GameScene::~GameScene()
{
	m_Vertex->Release();
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_SoundIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}

SceneBase::SceneID GameScene::Update()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("front",Lib::KEY_ON))
	{
		Pos += Lib::Math::GetAngleMovePos(2.f, g_Angle - 90.f);
	}
	
	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("left", Lib::KEY_ON))
	{
		g_Angle -= 2.f;
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("right", Lib::KEY_ON))
	{
		g_Angle += 2.f;
	}
	return m_SceneID;
}

void GameScene::Draw()
{
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	g_Timer.Begin();
	m_Vertex->Draw(Pos, m_Animation->GetUV(), 1.f, Lib::VECTOR2(1.f, 1.f), g_Angle);
	g_Timer.End();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();

	g_Timer.TimerShow();
}

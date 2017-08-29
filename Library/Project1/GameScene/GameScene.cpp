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
#include "Library\SmartPointer\WeakPtr.h"
#include "Library\SmartPointer\UniquePtr.h"
#include "Library\SmartPointer\SharedPtr.h"
#include "Library\ObjectBase\ObjectBase.h"
#include "Library\TaskManager\TaskManager.h"
#include "Library\SceneManager\SceneManager.h"

namespace
{
	Lib::DebugTimer g_Timer(120);
	RECT Rectvar = {0,0,0,0};
	Lib::VECTOR2 Pos;
	float g_Angle = 0.f;
}

class Test : Lib::ObjectBase
{
public:
	Test()
	{
		draw = new Lib::DrawTask(3);
		draw1 = new Lib::DrawTask(4);
		draw2 = new Lib::DrawTask(2);
		draw3 = new Lib::DrawTask(7);

		draw->SetObject(this);
		draw1->SetObject(this);
		draw2->SetObject(this);
		draw3->SetObject(this);

		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(draw);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(draw1);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(draw2);
		SINGLETON_INSTANCE(Lib::TaskManager).AddTask(draw3);

	}
	~Test()
	{
		delete draw;
		delete draw1;
	}

	void Update() override
	{

	}
	void Draw() override
	{

	}

private:
	Lib::DrawTask* draw;
	Lib::DrawTask* draw1;
	Lib::DrawTask* draw2;
	Lib::DrawTask* draw3;
};

GameScene::GameScene() :
SceneBase("GameScene")
{
}

GameScene::~GameScene()
{
}

bool GameScene::Initialize()
{
	Test test2;
	Pos.x = 400.f;
	Pos.y = 400.f;
	SINGLETON_INSTANCE(Lib::TextureManager).Load("Character.png", &m_TextureIndex);
	SINGLETON_INSTANCE(Lib::DSoundManager).LoadSound("button01a.wav", &m_SoundIndex);

	Lib::SharedPtr<int> test = Lib::MakeShared<int>(10);
	*test = 10;

	Lib::WeakPtr<int> test1;
	test1 = test;

	if (!test1)
	{
		int var = 0;
		var++;
	}
	SINGLETON_INSTANCE(Lib::TaskManager).AllExecute();
	m_Animation = Lib::MakeUnique<Lib::AnimUvController>();
	m_Animation->LoadAnimation("Character.anim", "Wait");
	m_Animation->SetAnimFrame(10);

	m_Vertex = Lib::MakeUnique<Lib::Vertex2D>(SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

	RECT ClientRect;
	GetClientRect(SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(), &ClientRect);
	m_Vertex->Initialize(Lib::VECTOR2(256, 256), m_Animation->GetUV());
	m_Vertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("front", DIK_W);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("front", DIK_UPARROW);

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("left", DIK_A);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("left", DIK_LEFTARROW);

	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("right", DIK_D);
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("right", DIK_RIGHTARROW);

	//SINGLETON_INSTANCE(Lib::DirectShowSound).SoundOperation(m_SoundIndex, Lib::SOUND_LOOP);
	return true;
}

void GameScene::Finalize()
{
	m_Vertex->Finalize();
	SINGLETON_INSTANCE(Lib::DSoundManager).ReleaseSound(m_SoundIndex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}
int vol = 100;
void GameScene::Execute()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("front",Lib::KEY_PUSH))
	{
		SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_SoundIndex,Lib::DSoundManager::SOUND_PLAY);
		//Pos += Lib::Math::GetAngleMovePos(2.f, g_Angle - 90.f);
	}
	
	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("left", Lib::KEY_PUSH))
	{
		vol -= 10;
		SINGLETON_INSTANCE(Lib::DSoundManager).SetSoundVolume(m_SoundIndex,vol);
	}

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("right", Lib::KEY_PUSH))
	{
		vol += 10;
		SINGLETON_INSTANCE(Lib::DSoundManager).SetSoundVolume(m_SoundIndex, vol);
	}

	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	g_Timer.Begin();
	m_Vertex->Draw(Pos, m_Animation->GetUV(), 1.f, Lib::VECTOR2(1.f, 1.f), g_Angle);
	g_Timer.End();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();

	g_Timer.TimerShow();

}
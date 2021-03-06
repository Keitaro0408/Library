﻿/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include "../MainCamera.h"
#include "House\House.h"
#include "Ground\Ground.h"

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
#include "Library\Fbx\FbxFileManager\FbxFileManager.h"
#include "Library\Helper\Helper.h"
#include "Library\Shader\ShaderManager.h"
#include "Library\Event\EventListenerBase.h"

class Test
{
	friend class TestListener;
public:
	Test(){}
	~Test(){}

private:
	int m_val;
};

class TestListener : public Lib::EventListenerBase
{
public:
	TestListener(Test* _test)
	{
		test = _test;
	}
	virtual ~TestListener(){}

	virtual void OnEvent(Lib::Event& _event)
	{
		test->m_val;
	}
private:
	Test* test;

};
namespace
{
	Lib::DebugTimer g_Timer(120);
	TestListener* testListener;
}
GameScene::GameScene() :
SceneBase("GameScene")
{
}

GameScene::~GameScene()
{
}

bool GameScene::Initialize()
{
	m_pCamera = new MainCamera;
	m_pHouse = Lib::MakeUnique<House>();
	m_pGround = Lib::MakeUnique<Ground>();
	SINGLETON_INSTANCE(Lib::EventManager).AddListener(testListener,"test");
	return true;
}

void GameScene::Finalize()
{
	SINGLETON_INSTANCE(Lib::TaskManager).AllRemove();
}

void GameScene::Execute()
{
	SINGLETON_INSTANCE(Lib::KeyDevice).Update();

	if (SINGLETON_INSTANCE(Lib::KeyDevice).AnyMatchKeyCheck("front",Lib::KEY_PUSH))
	{
		int test = 0;
		//SINGLETON_INSTANCE(Lib::DSoundManager).SoundOperation(m_SoundIndex,Lib::DSoundManager::SOUND_PLAY);
	}
	
	SINGLETON_INSTANCE(Lib::DX11Manager).SetDepthStencilTest(true);
	SINGLETON_INSTANCE(Lib::DX11Manager).BeginScene();
	g_Timer.Begin();
	SINGLETON_INSTANCE(Lib::TaskManager).AllExecute();
	g_Timer.End();
	SINGLETON_INSTANCE(Lib::DX11Manager).EndScene();

	g_Timer.TimerShow();
}

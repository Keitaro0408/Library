#include "App.h"
#include "Library/Application/ApplicationBase.h"
#include "Library/Window/Window.h"
#include "Library\Helper\Helper.h"
#include "Library\Fbx\FbxFileManager\FbxFileManager.h"
#include "Library\DxInput\KeyBoard\KeyDevice.h"
#include "Library\Dx11\DX11Manager.h"
#include <memory>
#include <vector>
#include <assert.h>

void App::Initialize()
{
	SINGLETON_CREATE(Lib::FbxFileManager);
	SINGLETON_INSTANCE(Lib::FbxFileManager).Initialize(
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDevice(),
		SINGLETON_INSTANCE(Lib::DX11Manager).GetDeviceContext());

	m_pGameScene = Lib::MakeUnique<GameScene>();
	m_pTitleScene = Lib::MakeUnique<TitleScene>();
	SINGLETON_INSTANCE(Lib::KeyDevice).KeyCheckEntry("front",DIK_W);
	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("GameScene");
}

void App::Finalize()
{
	m_pTitleScene.Reset();
	m_pGameScene.Reset();
	SINGLETON_INSTANCE(Lib::FbxFileManager).Finalize();
	SINGLETON_DELETE(Lib::FbxFileManager);
}

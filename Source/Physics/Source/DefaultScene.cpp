#include "DefaultScene.h"
#include "GenericSubject.h"
#include "AudioObserver.h"
#include "AudioManager.h"
#include "RenderComponent.h"

#define PLAYER_HEALTH 200
DefaultScene::DefaultScene()
{
}

DefaultScene::~DefaultScene()
{
}
void DefaultScene::Init()
{
	/// INIT ///
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	DataContainer* dataContainer = DataContainer::GetInstance();
	/// INIT ///
	/// Layers================================================================================
	m_GOM.CreateLayer(dataContainer->GetShader("Default"), "default");
	/// End Layers================================================================================
	/// Misc Data================================================================================
	/// End Misc Data================================================================================
	/// Observers================================================================================
	GenericSubject::GetInstance()->AddObserver(new AudioObserver);
	/// End Observers================================================================================
	/// Audio================================================================================
	/// End Audio================================================================================
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("fps"), "UI");
	go->TRANS->SetPosition(1920 - 40, 1080 - 20, 25);
	go->RENDER->SetRenderDistance(-1);
	go->SetDisableDistance(-1);
	/// EndUI================================================================================
}
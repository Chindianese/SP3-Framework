#include "DefaultScene.h"
#include "GenericSubject.h"
#include "AudioObserver.h"
#include "AudioManager.h"
#include "RenderComponent.h"
#include "CameraScript.h"
#include "Utility.h"

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
	GameObject* target = nullptr;
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
	/// Misc================================================================================
	target = m_GOM.AddGameObject();
	/// EndMisc================================================================================
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraScript(target));
	m_CameraGO->AddComponent(new CameraComponent);
	m_CameraGO->SetDisableDistance(-1);
	// m_CameraGO->AddChild(go2);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 5);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_ORTHO);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 200;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(true);
	/// End Create Camera================================================================================
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("fps"), "UI");
	go->TRANS->SetPosition(1920 - 40, 1080 - 20, 25);
	go->RENDER->SetRenderDistance(-1);
	go->SetDisableDistance(-1);
	/// EndUI================================================================================
}
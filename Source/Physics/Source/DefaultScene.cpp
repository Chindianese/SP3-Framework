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
	/// Init================================================================================
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	/// Observers================================================================================
	/// EndObservers================================================================================
	/// Layers================================================================================
	/// End Layers================================================================================
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("fps"), "UI");
	go->TRANS->SetPosition(1920 - 40, 1080 - 20, 25);
	/// Background--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("QuadCentered")));
	go->TRANS->SetPosition(1920 / 2, 1080 / 2);
	go->TRANS->SetScale(1920, 1080, 1);
	go->RENDER->SetColor(0.2f, 0.2f, 0.2f);
	// Title--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(1920 / 2 + 200, 10, 120);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "SUSUcubed"));
	go->RENDER->SetColor({ 0.4f,1.f,0.8f });
	go->SetDisableDistance(-1);
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraComponent);
	// m_CameraGO->AddChild(go2);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_CUSTOM_ORTHO);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 100;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(true);
}
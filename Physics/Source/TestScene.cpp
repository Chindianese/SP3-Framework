#include "TestScene.h"
#include "PlayerScript.h"
#include "WeaponScript.h"
#include "AudioManager.h"
#include "Constrain.h"
#include "WeaponSniperRifleScript.h"
#include "WeaponRocketLauncherScript.h"
#include "PhysicsScript.h"
TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init()
{
	// Create Camera
	m_CameraGO = new GameObject;
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	//m_GameObjectManager.AddGameObject(CameraGO);
	SetCursorEnabled(false);
	//
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Layers
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Water"), "Water");
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	this->m_Camera->InitOrtho({ 100,100,1000 });
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

	// ui
	GameObject* ui = m_GameObjectManager.AddGameObject("UI");
	ui->TRANS->SetPosition(0, 1000, 5);
	ui->TRANS->SetScale(100.f, 100.f, 1.f);
	ui->TRANS->SetRotation(90, 0, 1, 0);
	ui->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	ui->RENDER->SetLightEnabled(true);
	ui->RENDER->SetActive(true);
	ui->SetActive(true);
	//

	// text
	GameObject* text = m_GameObjectManager.AddGameObject("UI");
	text->TRANS->SetPosition(10, 10, 50);
	text->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "oof"));
	text->RENDER->SetLightEnabled(false);
	text->SetActive(true);
	//

	GameObject* cube = m_GameObjectManager.AddGameObject();
	cube->GetComponent<TransformComponent>()->SetPosition(0, 10, 0);
	cube->GetComponent<TransformComponent>()->SetScale(10, 1, 10);
	cube->GetComponent<TransformComponent>()->SetRotation(45, 0, 1, 0);
	cube->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	cube->GetComponent<RenderComponent>()->SetLightEnabled(true);
	cube->GetComponent<RenderComponent>()->SetBillboard(false);

	// Skyplane
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANS->SetPosition(0, 100, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	SkyPlane->RENDER->SetLightEnabled(false);
	SkyPlane->SetActive(true);
	//

	// Terrain
	GameObject* terrain = m_GameObjectManager.AddGameObject();
	//terrain->TRANSFORM->SetScale(500, 20, 500);
	terrain->AddComponent(new RenderComponent(dataContainer->GetHeightMap("Terrain")->GetMesh()));
	terrain->RENDER->SetLightEnabled(true);
	terrain->SetActive(true);
	//

	// water
	GameObject* water = m_GameObjectManager.AddGameObject("Water");
	water->AddComponent(new RenderComponent(dataContainer->GetMesh("Water")));
	water->RENDER->SetLightEnabled(true);
	//

	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANS->SetRotation(-90, 1, 0, 0);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("Ground")));
	ground->RENDER->SetLightEnabled(true);
	ground->SetActive(false);
	//

	// depth
	GameObject* depth = m_GameObjectManager.AddGameObject();
	depth->TRANS->SetScale(1, 1, 1);
	depth->TRANS->SetPosition(20, 10, 1);
	//depth->TRANSFORM->SetRotation(-90, 1, 0, 0);
	depth->AddComponent(new RenderComponent(dataContainer->GetMesh("QuadScope")));
	depth->RENDER->SetLightEnabled(true);
	depth->SetActive(true);
	//

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANS->SetPosition(0, 15, 50);
	PlayerScript* p = new PlayerScript(text);
	player->AddComponent(p);
	p->AddWeapon(new WeaponSniperRifleScript());
	p->AddWeapon(new WeaponScript());
	p->AddWeapon(new WeaponRocketLauncherScript());
	player->AddChild(m_CameraGO);
	player->AddComponent(new Constrain(dataContainer->GetHeightMap("Terrain"), Constrain::LIMIT, 0.1f));
	player->AddComponent(new PhysicsScript());
	//AudioManager::GetInstance()->PlayBGM("despacito.wav");

	// Cat
	GameObject* cat = m_GameObjectManager.AddGameObject();
	cat->TRANS->SetPosition(0, 21, 0);
	cat->TRANS->SetScale(20.f, 20.f, 20.f);
	cat->AddComponent(new RenderComponent(dataContainer->GetAnimation("Cat")));
	cat->RENDER->SetBillboard(true);
	cat->RENDER->SetActive(true);
}
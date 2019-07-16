#include "ChengAssignmentScene.h"
#include "ChengPlayerScript.h"
#include "GunScript.h"
#include "ParticleSpawnerScript.h"

ChengAssignmentScene::ChengAssignmentScene()
{
}

ChengAssignmentScene::~ChengAssignmentScene()
{
}
void ChengAssignmentScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Layers
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Water"), "Water");
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Smoke"), "Smoke");
	// Set up camera
	m_CameraGO->TRANSFORM->SetPosition(0, 0, 0);
	m_CameraGO->TRANSFORM->SetRelativePosition(0, 10, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

	// Crosshair
	GameObject* Crosshair = m_GameObjectManager.AddGameObject("UI");
	Crosshair->TRANSFORM->SetPosition(1920 / 2, 1080 / 2, 5);
	Crosshair->TRANSFORM->SetScale(100.f, 100.f, 1.f);
	// ui->TRANSFORM->SetRotation(90, 0, 1, 0);
	Crosshair->AddComponent(new RenderComponent(dataContainer->GetMesh("Crosshair")));
	Crosshair->RENDER->SetLightEnabled(false);
	Crosshair->SetActive(true);
	//

	// Skyplane
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANSFORM->SetPosition(0, 100, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	//SkyPlane->RENDER->SetLightEnabled(true);
	//SkyPlane->SetActive(false);
	//

	// Terrain
	GameObject* terrain = m_GameObjectManager.AddGameObject();
	terrain->TRANSFORM->SetScale(500, 50, 500);
	terrain->TRANSFORM->SetPosition(0, -20, 0);
	terrain->AddComponent(new RenderComponent(dataContainer->GetMesh("Terrain")));
	terrain->RENDER->SetLightEnabled(true);
	terrain->SetActive(true);
	//
	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANSFORM->SetScale(1, 1, 1);
	ground->TRANSFORM->SetRotation(-90, 1, 0, 0);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("Ground")));
	ground->RENDER->SetLightEnabled(true);
	ground->SetActive(false);
	//

	// depth
	GameObject* depth = m_GameObjectManager.AddGameObject();
	depth->TRANSFORM->SetScale(1, 1, 1);
	depth->TRANSFORM->SetPosition(20, 10, 1);
	//depth->TRANSFORM->SetRotation(-90, 1, 0, 0);
	depth->AddComponent(new RenderComponent(dataContainer->GetMesh("Depth")));
	//depth->RENDER->SetLightEnabled(true);
	depth->SetActive(false);
	depth->RENDER->SetBillboard(true);
	//

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 0, 50);
	// Gun
	GameObject* gun = m_GameObjectManager.AddGameObject("UI");
	gun->TRANSFORM->SetPosition(1900, 80, 0);
	gun->AddComponent(new RenderComponent(dataContainer->GetMesh("Gun")));
	gun->RENDER->SetBillboard(false);
	gun->RENDER->SetLightEnabled(false);
	gun->AddComponent(new GunScript(dataContainer->GetGameObject("Bullet"), m_CameraGO, 0.1f, true));

	player->AddComponent(new ChengPlayerScript(gun));
	player->AddChild(m_CameraGO);

	// Spawner
	GameObject* Spawner = m_GameObjectManager.AddGameObject();
	Spawner->TRANSFORM->SetPosition(0, 50, 0);
	Spawner->AddComponent(new ParticleSpawnerScript(dataContainer->GetGameObject("Rain"), 0.0002f, { 100,100,100 }, .8f));
	Spawner->SetActive(true);
	//

	// Fish Spawner
	GameObject* FishSpawner = m_GameObjectManager.AddGameObject();
	FishSpawner->TRANSFORM->SetPosition(55, 0, 0);
	FishSpawner->AddComponent(new ParticleSpawnerScript(dataContainer->GetGameObject("Fish"), 0.3f, { 2,2,2 }, .6f));
	FishSpawner->SetActive(true);
	//

	// water
	GameObject* water = m_GameObjectManager.AddGameObject("Water");
	water->AddComponent(new RenderComponent(dataContainer->GetMesh("WaterPlane")));
	water->TRANSFORM->SetPosition(0, -1, 0);
	water->RENDER->SetLightEnabled(false);
	water->SetActive(true);
	//
	// Leaf Spawner
	GameObject* LeafSpawner = m_GameObjectManager.AddGameObject();
	LeafSpawner->TRANSFORM->SetRelativePosition(0, 60, 0);
	LeafSpawner->AddComponent(new ParticleSpawnerScript(dataContainer->GetGameObject("Leaf"), 0.7f, { 30,0,30 }, .4f));
	LeafSpawner->SetActive(true);
	//

	// Tree
	GameObject* Tree = m_GameObjectManager.AddGameObject();
	Tree->AddComponent(new RenderComponent(dataContainer->GetMesh("Tree")));
	Tree->TRANSFORM->SetPosition(-30, -1, 0);
	Tree->RENDER->SetLightEnabled(true);
	Tree->AddChild(LeafSpawner);
	//
}
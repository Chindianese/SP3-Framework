#include "DefaultScene.h"
#include "GenericSubject.h"
#include "AudioObserver.h"
#include "AudioManager.h"
#include "ChunkCollider.h"
#include "InteractablesObserver.h"
#include "InteractableObCom.h"
#include "PlayerScript.h"
#include "Utility.h"
#include "CameraScript.h"
#include "MapSpawningScript.h"
#include "InventoryScript.h"
#include "WeaponScript.h"
#include "PlayerStatsScript.h"
#include "MiscellaneousPartScript.h"
#include "ReticleScript.h"
#include "ParticleObserver.h"
DefaultScene::DefaultScene()
{
}

DefaultScene::~DefaultScene()
{
}
void DefaultScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	/// Observers================================================================================
	GenericSubject::GetInstance()->AddObserver(new AudioObserver);
	GenericSubject::GetInstance()->AddObserver(new InteractablesObserver);
	GenericSubject::GetInstance()->AddObserver(new ParticleObserver);

	AudioManager::GetInstance()->PlayBGM("bgm_01.ogg", "low_synth");
	AudioManager::GetInstance()->SetBGMVolume(0, "low_synth");
	AudioManager::GetInstance()->QueueFade(1, 0.05f, "low_synth");
	AudioManager::GetInstance()->PlayBGM("bgm_02.ogg", "low_pad");
	AudioManager::GetInstance()->PlayBGM("bgm_03.ogg", "low_piano");
	AudioManager::GetInstance()->PlayBGM("bgm_04.ogg", "high_piano");
	AudioManager::GetInstance()->SetBGMVolume(0, "high_piano");
	/// Layers================================================================================
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------

	go = m_GOM.AddGameObject(dataContainer->GetGameObject("FPS"), "UI");
	go->TRANS->SetPosition(1920 - 40, 1080 - 20, 25);
	/// Inventory--------------------------------------------------------------------------------
	// slots--------------------------------------------------------------------------------
	GameObject** InventorySlots;
	InventorySlots = new GameObject*[INVENTORY_SIZE];
	float height0 = 100;
	float height1 = 220;
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100, height0);
	InventorySlots[0] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110, height0);
	InventorySlots[1] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110 - 110, height0);
	InventorySlots[2] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100, height1);
	InventorySlots[3] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110, height1);
	InventorySlots[4] = go;
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110 - 110, height1);
	InventorySlots[5] = go;
	// customise--------------------------------------------------------------------------------
	std::vector<GameObject*> CustoSlots;
	Vector3 CustoPos(1920 - 200, 600);
	float fCustoDist = 100;
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos - Vector3(-fCustoDist, 0, 0));
	CustoSlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos - Vector3(0, fCustoDist, 0));
	CustoSlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos - Vector3(fCustoDist, 0, 0));
	CustoSlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("CustomiseSlot"), "UI");
	go->TRANS->SetPosition(CustoPos - Vector3(0, -fCustoDist, 0));
	CustoSlots.push_back(go);
	// Stamina--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(50, 50, 0);
	go->TRANS->SetScale(200, 50, 1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->RENDER->SetColor(0.7f, 0.7f, 0.7f);

	GameObject* StaminaBar = m_GOM.AddGameObject("UI");
	StaminaBar->TRANS->SetPosition(50, 50, 0);
	StaminaBar->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	StaminaBar->RENDER->SetColor(1, 1, 0);

	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(50, 1030, 0);
	go->TRANS->SetScale(200, 50, 1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->RENDER->SetColor(0.7f, 0.7f, 0.7f);

	GameObject* HealthBar = m_GOM.AddGameObject("UI");
	HealthBar->TRANS->SetPosition(50, 1030, 0);
	HealthBar->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	HealthBar->RENDER->SetColor(1, 0.2f, 0.2f);

	/// Player================================================================================
	// Reticle
	GameObject* ret = m_GOM.AddGameObject();
	ret->AddComponent(new RenderComponent(dataContainer->GetMesh("Reticle")));
	ret->RENDER->SetColor(0, 1, 1);
	ret->AddComponent(new ReticleScript());
	//Gun------------------------------------------------------------------------------------
	GameObject* Gun = dataContainer->GetGameObject("Gun");
	Gun->TRANS->SetRelativePosition(1, 1, 1);
	// Grenade-------------------------------------------------------------------------------
	GameObject* grenade = dataContainer->GetGameObject("Grenade");
	grenade->TRANS->SetRelativePosition(0, 1, 1);
	// Player--------------------------------------------------------------------------------
	GameObject* Player = m_GOM.AddGameObject();
	m_Player = Player;
	Player->AddComponent(new PlayerScript(dataContainer->GetBehaviour("Player"), ret, Gun, grenade));
	Player->AddChild(Gun);
	Player->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	Player->AddComponent(new RenderComponent(dataContainer->GetMesh("Player")));
	Player->RENDER->SetActive(true);
	Player->TRANS->SetPosition(0, 18, 0);
	Player->TRANS->SetScale(0.5f);
	Player->AddComponent(new InventoryScript(Gun, InventorySlots, CustoSlots, ret));
	Player->AddComponent(new PlayerStatsScript(Player, StaminaBar, HealthBar, Gun, GetGO("BulletUI")));
	Player->AddComponent(new MapSpawningScript());
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraScript(Player));
	m_CameraGO->AddComponent(new CameraComponent);
	// m_CameraGO->AddChild(go2);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 100;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(false);
	// Enemy--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("Cow"));
	go->TRANS->SetPosition(5, 18.5f, 0);
	// --
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("Cow"));
	go->TRANS->SetPosition(20, 18.5f, 26);
	///interactable test

	go = m_GOM.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainPlains")->GetPos() - Vector3(200, 0, 0));
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainPlains")->GetMeshBiomed()));
	go->AddComponent(new BiomeComponent(BiomeComponent::BIOME_PLAINS));

	//go = m_GOM.AddGameObject(dataContainer->GetGameObject("plaintree"));
	//go->GetComponent<EntityScript>()->GetValues()->SetHealth(1);
	//go->AddComponent(new BiomeComponent(BiomeComponent::BIOME_PLAINS));
	//go->TRANS->SetPosition(20, 18.5, 20);

	go = m_GOM.AddGameObject(dataContainer->GetGameObject("treasurebox"));
	go->TRANS->SetPosition(20, 18.5, 20);

	go = m_GOM.AddGameObject(dataContainer->GetGameObject("boulder"));
	go->TRANS->SetPosition(10, 19, 20);

	go = m_GOM.AddGameObject(dataContainer->GetGameObject("ItemInfo"));
	go->TRANS->SetPosition(0, 16, 0);
	go->SetActive(false);

	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(0, 16, 0);
	go->TRANS->SetScale(1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "oof", false));
	go->RENDER->Set3DBillboard(true);
	go->RENDER->SetColor(0, 1, 1);
}
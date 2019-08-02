#include "RojakScene2.h"
#include "AudioManager.h"
#include "GunScript.h"
#include "ChengPlayerScript.h"
#include "MeshController.h"
#include "Blackhole.h"
#include "GauntletScript.h"
#include "SunBrightnessScript.h"
#include "Constrain.h"
#include "Utility.h"
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "ChargeBarScript.h"
#include "WorldValues.h"
#include "AmmoDumpScript.h"
#include "ChengRigidbody.h"
RojakScene2::RojakScene2()
{
}

RojakScene2::~RojakScene2()
{
}
void RojakScene2::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObject* go;
	GameObject* go2;
	WorldValues::GravityExponent.z = 0;
	/// Create Camera================================================================================
	m_CameraGO = new GameObject;
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	//m_GameObjectManager.AddGameObject(CameraGO);
	/// Layers================================================================================
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Water"), "Water");
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Smoke"), "Smoke");
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("HeatWave"), "HeatWave");
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Snow"), "Snow");
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 600;
	this->m_Camera->InitOrtho({ size, 0,10000 });
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("FPS"), "UI");
	// Crosshair--------------------------------------------------------------------------------
	GameObject* Crosshair = m_GameObjectManager.AddGameObject("UI");
	Crosshair->TRANS->SetPosition(1920 / 2, 1080 / 2, 5);
	Crosshair->TRANS->SetScale(100.f, 100.f, 1.f);
	Crosshair->AddComponent(new RenderComponent(dataContainer->GetMesh("Crosshair")));
	Crosshair->RENDER->SetLightEnabled(false);
	Crosshair->SetActive(true);
	//ScoreText--------------------------------------------------------------------------------
	go = dataContainer->GetGameObject("scoreboard");
	m_GameObjectManager.AddGameObject(go, "UI");
	// Gauntlet--------------------------------------------------------------------------------
	GameObject* Gaunt = dataContainer->GetGameObject("Gauntlet");
	m_GameObjectManager.AddGameObject(Gaunt, "UI");
	go2 = dataContainer->GetGameObject("Text");
	m_GameObjectManager.AddGameObject(go2, "UI");
	GauntletScript* gs = new GauntletScript(dataContainer->GetGameObject("bullet"), go2);
	Gaunt->AddComponent(gs);
	// ChargeBar--------------------------------------------------------------------------------
	// Text--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject("UI");
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Gauntlet Charge: "));
	go->TRANS->SetPosition(50, 980, 30);
	go->RENDER->SetColor({ 0, 1, 1 });
	// Part--------------------------------------------------------------------------------
	go2 = m_GameObjectManager.AddGameObject("UI");
	go2->TRANS->SetPosition(50 + 400, 960, 0);
	go2->AddComponent(new ParticleSpawnerScript(dataContainer->GetGameObject("Particle"), 0.05f, 0, 0, "UI", -1.f));
	go2->SetActive(false);
	// Main--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject("UI");
	go->TRANS->SetPosition(50, 960, 0);
	//go->TRANS->SetScale(100, 100, 1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->AddComponent(new ChargeBarScript(gs, go2));
	//Player================================================================================
	// Gun--------------------------------------------------------------------------------
	GameObject* gun = m_GameObjectManager.AddGameObject("UI");
	gun->TRANS->SetPosition(1900, 80, 0);
	gun->AddComponent(new RenderComponent(dataContainer->GetMesh("Gun")));
	gun->RENDER->SetBillboard(false);
	gun->RENDER->SetLightEnabled(false);
	gun->AddComponent(new GunScript(dataContainer->GetGameObject("bullet"), m_CameraGO, 0.1f, GunScript::CHARGE, dataContainer->GetGameObject("SmokeParticle"), 150, 3, 3));
	// Player--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->AddChild(m_CameraGO);
	go->TRANS->SetPosition({});
	go->AddComponent(new ChengPlayerScript(gun, Crosshair, Gaunt));
	go->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	go->GetComponent<ChengRigidbody>()->SetMat(0.9f, 0);
	go->TRANS->SetScale(10, 10, 10);
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::FIXED));
	//GameObject* child = dataContainer->GetGameObject("playerPillar");
	//go->AddChild(child);
	/// WORLD================================================================================
	// Skyplane--------------------------------------------------------------------------------
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANS->SetPosition(0, 340, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	SkyPlane->RENDER->SetLightEnabled(true);
	// Sun--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->AddComponent(new SunBrightnessScript);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("sun")));
	go->RENDER->SetColor({ 1, 1, 0 });
	go->TRANS->SetScale(10);
	// Rain--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("RainSpawner"));
	go->TRANS->SetPosition(100, 100, 100);
	// Snow--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("SnowSpawner"));
	go->TRANS->SetPosition(100, 100, -100);
	/// Plains================================================================================
	// Terrain================================================================================
	go = m_GameObjectManager.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainPlains")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainPlains")->GetMesh()));
	// Trees--------------------------------------------------------------------------------
	// Tree 1--------------------------------------------------------------------------------
	//go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("Tree"));
	//go->TRANS->SetPosition(100, 0, 100);
	//go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::FIXED));
	//go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("LeafSpawner"));
	//go->TRANS->SetPosition(100, 100, 100);
	//go->SetActive(false);
	//// Tree 2--------------------------------------------------------------------------------
	//go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("Tree"));
	//go->TRANS->SetPosition(150, 0, 100);
	//go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::FIXED));
	//go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("LeafSpawner"));
	//go->TRANS->SetPosition(150, 100, 100);
	//go->SetActive(false);
	// Water--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject("Water");
	go->TRANS->SetPosition(100, -5, 100);
	go->TRANS->SetScale(200, 1, 200);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("WaterPlane")));
	/// Terrace--------------------------------------------------------------------------------
	// Terrain================================================================================
	go = m_GameObjectManager.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainTerrace")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainTerrace")->GetMesh()));
	/// Snow--------------------------------------------------------------------------------
	// Terrain================================================================================
	go = m_GameObjectManager.AddGameObject("Snow");
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainSnow")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainSnow")->GetMesh()));
	// Ammo--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->TRANS->SetPosition(20, 0, -20);
	go->TRANS->SetScale(10, 10, 10);
	go->AddComponent(new ChengRigidbody(ChengRigidbody::PILLAR));
	//go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainSnow"), Constrain::FIXED));
	go->AddComponent(new AmmoDumpScript());
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("pillar")));
	/// Desert--------------------------------------------------------------------------------
	// Terrain================================================================================
	go = m_GameObjectManager.AddGameObject("HeatWave");
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainDesert")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainDesert")->GetMesh()));
	// Pillar--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar"));
	go->TRANS->SetPosition(-150, 0, -100);
	go->TRANS->SetScale(5, 100, 5);
	go->RENDER->SetColor({ 0.01f, 0.01f, 0.01f });
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainDesert"), Constrain::eConstrainTypes::FIXED));
	go->SetActive(false);
}
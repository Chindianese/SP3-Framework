#include "WeaponRocketLauncherScript.h"
#include "InputManager.h"
#include "PhysicsScript.h"
#include "PlayerScript.h"
#include "Application.h"
#include "AudioManager.h"
#include "RocketScript.h"
#include "Constrain.h"

WeaponRocketLauncherScript::WeaponRocketLauncherScript()
{

	m_fFireRate = 1.2;
	m_fProjectileSpeed = 100;
	m_fReloadTime = 0.9;
	m_fUseCooldown = 0;
	m_iClipSize = 1;
	m_iHeldBullets = 1;
	m_iHeldClips = 5;
	m_iMaxClips = 5;


	SceneManager* sm = SceneManager::GetInstance();
	Scene* scene = sm->GetScene();
	GameObjectManager* gom = scene->GetGameObjectManager();

	m_screenOverlay = gom->AddGameObject("UI");
	m_screenOverlay->SetActive(false);
	RenderComponent* rc1 = new RenderComponent(DataContainer::GetInstance()->GetMesh("QuadRPG"));
	rc1->SetLightEnabled(false);
	m_screenOverlay->AddComponent(rc1);
	m_screenOverlay->TRANS->SetScale(Application::GetWindowWidth() / 4, Application::GetWindowHeight() / 4, 1);
	m_screenOverlay->TRANS->SetPosition(Application::GetWindowWidth() * 3 / 4, Application::GetWindowHeight() * 1 / 4);
}

void WeaponRocketLauncherScript::Fire()
{
	AudioManager::GetInstance()->Play2D("explosion.wav");
	SceneManager* sm = SceneManager::GetInstance();
	Scene* scene = sm->GetScene();
	GameObjectManager* gom = scene->GetGameObjectManager();
	GameObject* bullet = gom->AddGameObject();
	TransformComponent* tc = GetComponent<TransformComponent>();
	bullet->AddComponent(new RenderComponent(DataContainer::GetInstance()->GetMesh("Cube")));
	bullet->GetComponent<TransformComponent>()->SetPosition(tc->GetPosition());
	bullet->AddComponent(new PhysicsScript(GetCamera()->GetDir() * m_fProjectileSpeed));
	Constrain* c = new Constrain(DataContainer::GetInstance()->GetHeightMap("Terrain"), Constrain::LIMIT, 0);
	bullet->AddComponent(c);
	bullet->AddComponent(new RocketScript(c));
	GetCamera()->AddTorque(Math::RandFloatMinMax(-20, 20), Math::RandFloatMinMax(60, 80));
}


void WeaponRocketLauncherScript::SetActive(bool b)
{
	ComponentBase::SetActive(b);
	m_screenOverlay->SetActive(b);
	GetCamera()->SetCamSpeed(12);
	GetCameraGO()->CAMERA->SetFOV(45);
}
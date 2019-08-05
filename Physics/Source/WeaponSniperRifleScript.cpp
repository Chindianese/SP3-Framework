#include "WeaponSniperRifleScript.h"
#include "InputManager.h"
#include "PhysicsScript.h"
#include "PlayerScript.h"
#include "Application.h"
#include "AudioManager.h"

WeaponSniperRifleScript::WeaponSniperRifleScript()
{
	m_fFireRate = 0.09f;
	m_fProjectileSpeed = 400;
	m_fReloadTime = 0.9;
	m_fUseCooldown = 0;
	m_iClipSize = 40;
	m_iHeldBullets = 40;
	m_iHeldClips = 16;
	m_iMaxClips = 16;
	SceneManager* sm = SceneManager::GetInstance();
	Scene* scene = sm->GetScene();
	GameObjectManager* gom = scene->GetGameObjectManager();
	scopeOverlay = gom->AddGameObject("UI");
	scopeOverlay->SetActive(false);
	RenderComponent* rc = new RenderComponent(DataContainer::GetInstance()->GetMesh("QuadScope"));
	rc->SetLightEnabled(false);
	scopeOverlay->AddComponent(rc);
	scopeOverlay->TRANS->SetScale(Application::GetWindowWidth() / 2, Application::GetWindowHeight() / 2, 1);
	scopeOverlay->TRANS->SetPosition(Application::GetWindowWidth() / 2, Application::GetWindowHeight() / 2);
	
	m_screenOverlay = gom->AddGameObject("UI");
	m_screenOverlay->SetActive(false);
	RenderComponent* rc1 = new RenderComponent(DataContainer::GetInstance()->GetMesh("QuadSniper"));
	rc1->SetLightEnabled(false);
	m_screenOverlay->AddComponent(rc1);
	m_screenOverlay->TRANS->SetScale(Application::GetWindowWidth() / 4, Application::GetWindowHeight() / 4, 1);
	m_screenOverlay->TRANS->SetPosition(Application::GetWindowWidth() * 3 / 4, Application::GetWindowHeight() * 1 / 4);
}

void WeaponSniperRifleScript::Update(double dt)
{
	WeaponScript::Update(dt);
	if (InputManager::GetInstance()->GetInputStrength("PlayerWeaponSecondary") > 0)
	{
		m_bScoped = true;
		scopeOverlay->SetActive(true);
		m_screenOverlay->SetActive(false);
		GetCamera()->SetCamSpeed(3);
		GetCameraGO()->CAMERA->SetFOV(15);
	}
	else
	{
		scopeOverlay->SetActive(false);
		m_screenOverlay->SetActive(true);
		GetCamera()->SetCamSpeed(12);
		GetCameraGO()->CAMERA->SetFOV(45);
	}
}

void WeaponSniperRifleScript::Fire()
{
	WeaponScript::Fire();
	AudioManager::GetInstance()->Play2D("gunshot.wav");
	GetCamera()->AddTorque(Math::RandFloatMinMax(-32, 32), Math::RandFloatMinMax(-32, 32));
}

void WeaponSniperRifleScript::SetActive(bool b)
{
	ComponentBase::SetActive(b);
	m_bScoped = false;
	scopeOverlay->SetActive(false);
	m_screenOverlay->SetActive(b);
	GetCamera()->SetCamSpeed(12);
	GetCameraGO()->CAMERA->SetFOV(45);
}
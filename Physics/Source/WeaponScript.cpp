#include "WeaponScript.h"
#include "InputManager.h"
#include "PhysicsScript.h"
#include "PlayerScript.h"
#include "Collider.h"
#include "BulletCollisionResponse.h"

WeaponScript::WeaponScript()
{
	// placeholder weapon fire rate
	m_fFireRate = 0.3;
	m_fProjectileSpeed = 400;
	m_fReloadTime = 0.9;
	m_fUseCooldown = 0;
	m_iClipSize = 20;
	m_iHeldBullets = 20;
	m_iHeldClips = 5;
	m_iMaxClips = 5;
}

WeaponScript::~WeaponScript()
{

}

void WeaponScript::Update(double dt)
{
	TransformComponent* tc = GetComponent<TransformComponent>();
	m_fUseCooldown -= dt;
	if (m_fUseCooldown < 0 && InputManager::GetInstance()->GetInputStrength("PlayerFireWeapon") > 0 && m_iHeldBullets > 0)
	{
		m_fUseCooldown = m_fFireRate;
		m_iHeldBullets--;
		Fire();
	}
	if (m_fUseCooldown < 0 && InputManager::GetInstance()->GetInputStrength("PlayerReloadWeapon") > 0 && m_iHeldBullets < m_iClipSize && m_iHeldClips > 0)
	{
		m_fUseCooldown = m_fReloadTime;
		m_iHeldBullets = m_iClipSize;
		m_iHeldClips--;
	}
}

void WeaponScript::Fire()
{
	SceneManager* sm = SceneManager::GetInstance();
	Scene* scene = sm->GetScene();
	GameObjectManager* gom = scene->GetGameObjectManager();
	GameObject* bullet = gom->AddGameObject();
	TransformComponent * tc = GetComponent<TransformComponent>();
	bullet->AddComponent(new RenderComponent(DataContainer::GetInstance()->GetMesh("Cube")));
	bullet->GetComponent<TransformComponent>()->SetPosition(tc->GetPosition() + GetCamera()->GetDir() - GetCamera()->GetUp() + 2 * GetCamera()->GetDir().Cross(GetCamera()->GetUp()));
	bullet->AddComponent(new PhysicsScript(GetCamera()->GetDir()* m_fProjectileSpeed));
	bullet->AddComponent(new Collider(Vector3(0.2, 0.2)));
	bullet->AddComponent(new BulletCollisionResponse());
}

void WeaponScript::PickUpAmmo(int ammoCount)
{
	m_iHeldClips += ammoCount;
	if (m_iHeldClips > m_iMaxClips) m_iHeldClips = m_iMaxClips;
}

int WeaponScript::GetHeldBullets()
{
	return m_iHeldBullets;
}

int WeaponScript::GetHeldClips()
{
	return m_iHeldClips;
}

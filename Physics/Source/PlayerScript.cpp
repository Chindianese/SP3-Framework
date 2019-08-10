#include "PlayerScript.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "Constrain.h"
#include "PhysicsScript.h"
#include <sstream>
PlayerScript::PlayerScript(GameObject* ammoText)
{
	weaponIndex = 0;
	m_ammoText = ammoText; 
	walkCameraDelay = 0;
	currentState = WALK;
}

PlayerScript::~PlayerScript()
{
}
void PlayerScript::AddWeapon(WeaponScript* w)
{
	m_vec_RefList->push_back(w);
	w->Init(m_vec_RefList);
	m_weapons.push_back(w);
}

void PlayerScript::Start()
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetTarget();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
}
void PlayerScript::Update(double dt)
{
	walkCameraDelay -= dt;
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();

	float fSpeed = (float)dt * 3.0f;
	Vector3 vRight = m_vCameraFront.Cross(m_vCameraUp);
	if (InputManager::GetInstance()->GetInputStrength("PlayerSprint") > 0)
	{
		currentState = WALK;
		GetComponent<Constrain>()->SetHeight(0.f);
		fSpeed *= 2.5;
	}
	if (currentState == CROUCH) fSpeed *= 0.4;
	if (currentState == PRONE) fSpeed *= 0.1;
	Vector3 vForward = m_vCameraFront;
	vForward.y = 0;
	SceneManager* SceneManager = SceneManager::GetInstance();
	Scene* CurrentScene = SceneManager->GetScene();
	Camera* Cam = CurrentScene->GetCamera();

	if (vForward.IsZero()) vForward = Vector3(1, 0, 0);
	else vForward.Normalize();
	trans->Translate(Math::Clamp(InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") * fSpeed, -100.f * fSpeed, 100.f * fSpeed) * vForward);
	if ((InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") != 0 || InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") != 0))
	{
		if (GetComponent<Constrain>()->IsOnGround())
		{
			float totalStrengthOfMovement = InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") * InputManager::GetInstance()->GetInputStrength("PlayerMoveForwardBack") + InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") * InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft");
			totalStrengthOfMovement = sqrt(totalStrengthOfMovement) / 30;
			totalStrengthOfMovement *= (currentState == WALK ? 1 : (currentState == CROUCH ? 0.8 : 3.2));
			Cam->AddTorque(0, 0, totalStrengthOfMovement * sin(walkCameraDelay * 6.28));
		}
	}
	if ((InputManager::GetInstance()->GetInputStrength("PlayerCrouchProne") > 0) && !crouchBounce)
	{
		crouchBounce = true;
		if (currentState == WALK)
		{
			currentState = CROUCH;
			GetComponent<Constrain>()->SetHeight(-5.f);
			trans->Translate(Vector3(0, -5, 0));
		}
		else if (currentState == CROUCH)
		{
			currentState = PRONE;
			GetComponent<Constrain>()->SetHeight(-15.f);
			trans->Translate(Vector3(0, -10, 0));
		}
	}
	if ((InputManager::GetInstance()->GetInputStrength("PlayerCrouchProne") < 0) && !crouchBounce)
	{
		crouchBounce = true;
		if (currentState == CROUCH)
		{
			currentState = WALK;
			GetComponent<Constrain>()->SetHeight(0.f);
			trans->Translate(Vector3(0, 5, 0));
		}
		if (currentState == PRONE)
		{
			currentState = CROUCH;
			GetComponent<Constrain>()->SetHeight(-5.f);
			trans->Translate(Vector3(0, 10, 0));
		}
	}
	if (crouchBounce && InputManager::GetInstance()->GetInputStrength("PlayerCrouchProne") == 0)
	{
		crouchBounce = false;
	}
	trans->Translate(Math::Clamp(InputManager::GetInstance()->GetInputStrength("PlayerMoveRightLeft") * fSpeed, -100.f * fSpeed, 100.f * fSpeed) * vRight);
	if (InputManager::GetInstance()->GetInputStrength("PlayerJump") > 0)
	{
		if (GetComponent<Constrain>()->IsOnGround())
			GetComponent<PhysicsScript>()->SetVelocity(Vector3(0, 42, 0));
		if (currentState == PRONE)
		{
			currentState = WALK;
			trans->Translate(Vector3(0,15,0));
			GetComponent<Constrain>()->SetHeight(0.f);
		}
	}

	Cam->UpdateYawPitchMouse(InputManager::GetInstance()->GetInputStrength("PlayerLookLeftRight"), InputManager::GetInstance()->GetInputStrength("PlayerLookUpDown"));
	Cam->Update(dt);

	weaponIndex = weaponIndex + InputManager::GetInstance()->GetInputStrength("PlayerChangeWeapon");
	int weaponIndexTruncated = ((((int)weaponIndex) % m_weapons.size()) + m_weapons.size()) % m_weapons.size();
	std::stringstream str;
	str << m_weapons[weaponIndexTruncated]->GetHeldBullets() << " / " << m_weapons[weaponIndexTruncated]->GetHeldClips();
	m_ammoText->GetComponent<RenderComponent>()->SetText(str.str());

	for (int i = 0; i < m_weapons.size(); i++)
	{
		m_weapons[i]->SetActive(i == weaponIndexTruncated);
	}
	// TODO Constrain to terrain===============
	//=================================================================
	//Vector3 pos = trans->GetPosition();
	//trans->SetPosition(pos.x, 30.f * ReadHeightMap(DataContainer::GetInstance()->heightMap, pos.x / 500, pos.z / 500), pos.z);
}

WeaponScript* PlayerScript::GetWeapon()
{
	int weaponIndexTruncated = ((((int)weaponIndex) % m_weapons.size()) + m_weapons.size()) % m_weapons.size();
	return m_weapons[weaponIndexTruncated];
}
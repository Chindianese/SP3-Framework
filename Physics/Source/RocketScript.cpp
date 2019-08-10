#include "RocketScript.h"
#include "AudioManager.h"
#include "PlayerScript.h"
#include "EnemyScript.h"
RocketScript::RocketScript(Constrain* c)
{
	m_constrain = c;
}

void RocketScript::Update(double dt)
{
	if (m_constrain->IsOnGround())
	{
		AudioManager::GetInstance()->Play3D("rocketExplosion.wav", (GetCameraGO()->TRANS->GetPosition() - TRANS->GetPosition()) * 0.001);
		m_parent->SetActive(false);
		SetActive(false);
		float distance = (GetComponent<TransformComponent>()->GetPosition() - GetCameraGO()->GetComponent<TransformComponent>()->GetPosition()).LengthSquared() * 25;
		GetCamera()->AddTorque(Math::RandFloatMinMax(-200.f / distance, 200.f / distance), Math::RandFloatMinMax(-200.f / distance, 200.f / distance), Math::RandFloatMinMax(-200.f / distance, 200.f / distance));
	}
}

void RocketScript::CollisionResponse(Collider* c)
{
	if (c->GetComponent<PlayerScript>() != nullptr) return;
	if (c->GetComponent<EnemyScript>() != nullptr)
	{
		c->GetComponent<EnemyScript>()->HealthModify(-20);
	}
	AudioManager::GetInstance()->Play3D("rocketExplosion.wav", (GetCameraGO()->TRANS->GetPosition() - TRANS->GetPosition()) * 0.001);
	m_parent->SetActive(false);
	SetActive(false);
	float distance = (GetComponent<TransformComponent>()->GetPosition() - GetCameraGO()->GetComponent<TransformComponent>()->GetPosition()).LengthSquared() * 25;
	GetCamera()->AddTorque(Math::RandFloatMinMax(-200.f / distance, 200.f / distance), Math::RandFloatMinMax(-200.f / distance, 200.f / distance), Math::RandFloatMinMax(-200.f / distance, 200.f / distance));
}

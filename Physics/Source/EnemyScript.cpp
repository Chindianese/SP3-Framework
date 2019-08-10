#include "EnemyScript.h"
#include "PhysicsScript.h"

EnemyScript::EnemyScript(float hp)
{
	m_fHp = hp;
}

void EnemyScript::Update(double dt)
{
	m_fWalkDelay -= dt;
	if (m_fWalkDelay < 0)
	{
		m_fWalkDelay = 0.7;
		GetComponent<PhysicsScript>()->SetVelocity(GetComponent<PhysicsScript>()->GetVelocity() + Vector3(Math::RandFloatMinMax(-6, 6), 1, Math::RandFloatMinMax(-6, 6)));
		HealthModify(-0.5);
	}
}

void EnemyScript::HealthModify(float hp)
{
	m_fHp += hp;
	if (m_fHp < 0)
	{
		this->GetParent()->SetActive(false);
	}
}

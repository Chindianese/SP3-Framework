#pragma once
#include "ScriptComponent.h"

class EnemyScript : public ScriptComponent
{
	float m_fHp;
	float m_fWalkDelay;
public:
	EnemyScript();
	EnemyScript(float hp);
	virtual void Update(double dt);
	void HealthModify(float hp);
	virtual ComponentBase* Clone()
	{
		return new EnemyScript(*this);
	}
};
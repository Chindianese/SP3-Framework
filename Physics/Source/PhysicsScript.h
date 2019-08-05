#pragma once
#include "ScriptComponent.h"
class PhysicsScript : public ScriptComponent
{
	Vector3 m_vVelocity;
	Vector3 m_vAcceleration;
public:
	PhysicsScript();
	PhysicsScript(Vector3 velocity);
	virtual void Update(double dt);
	void SetVelocity(Vector3 velocity);
	Vector3 GetVelocity();
	virtual ComponentBase* Clone()
	{
		return new PhysicsScript(*this);
	}
};
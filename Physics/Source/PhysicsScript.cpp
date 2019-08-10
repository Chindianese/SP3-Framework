#include "PhysicsScript.h"

PhysicsScript::PhysicsScript()
{
	m_vVelocity = Vector3(0, 0, 0);
	m_vAcceleration = Vector3(0, -16.1, 0);
}

PhysicsScript::PhysicsScript(Vector3 velocity)
{
	m_vVelocity = velocity;
	m_vAcceleration = Vector3(0, -16.1, 0);
}

void PhysicsScript::Update(double dt)
{
	TransformComponent * tc = GetComponent<TransformComponent>();
	tc->Translate(m_vVelocity * dt);
	m_vVelocity += m_vAcceleration * dt;
	m_vVelocity = m_vVelocity * 0.98;
}

void PhysicsScript::SetVelocity(Vector3 velocity)
{
	m_vVelocity = velocity;
}

Vector3 PhysicsScript::GetVelocity()
{
	return m_vVelocity;
}

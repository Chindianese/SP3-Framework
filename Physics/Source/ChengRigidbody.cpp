#include "ChengRigidbody.h"
#include "TransformComponent.h"
ChengRigidbody::ChengRigidbody(ePhysicsTypes e, bool Grav)
{
	m_eType = e;
	m_fMass = 1;
	m_vGravity = { 0,-40.8f,40.8f };
	m_bLockXAxis = false;
	m_bLockYAxis = false;
	m_bLockZAxis = false;
	m_bGravityAffected = Grav;
}

ChengRigidbody::~ChengRigidbody()
{
}
void ChengRigidbody::Update(double dt)
{
	Vector3 m_vAccel = m_vForce * (1 / m_fMass);
	m_vForce.SetZero();
	if (m_bGravityAffected)
		m_vAccel += m_vGravity;
	this->m_vVel += m_vAccel * (float)dt;
	if (m_bLockXAxis)
		m_vVel.x = 0;
	if (m_bLockYAxis)
		m_vVel.y = 0;
	if (m_bLockZAxis)
		m_vVel.z = 0;
	TransformComponent* Trans = this->GetComponent<TransformComponent>();
	Trans->Translate(m_vVel * (float)dt);
	float deg = Trans->GetDegrees();
	deg += m_vAVel.y;
	if (m_vAVel.y != 0)
		Trans->SetRotation(deg, 0, 1, 0);
	m_vAVel.SetZero();
}
void ChengRigidbody::SetVel(Vector3 v)
{
	this->m_vVel = v;
}
void ChengRigidbody::SetAVel(Vector3 v)
{
	this->m_vAVel = v;
}
void ChengRigidbody::IncrementForce(Vector3 v)
{
	m_vForce += v;
}
Vector3 ChengRigidbody::GetVel()
{
	return m_vVel;
}
Vector3 ChengRigidbody::GetAVel()
{
	return m_vAVel;
}
float ChengRigidbody::GetMass()
{
	return m_fMass;
}
void ChengRigidbody::SetMass(float f)
{
	m_fMass = f;
}
ChengRigidbody::ePhysicsTypes ChengRigidbody::GetType()
{
	return m_eType;
}
// Grav
void ChengRigidbody::SetGravityX(float x)
{
	this->m_vGravity.x = x;
}
void ChengRigidbody::LockXAxis(bool b)
{
	m_bLockXAxis = b;
}
void ChengRigidbody::LockYAxis(bool b)
{
	m_bLockYAxis = b;
}
void ChengRigidbody::LockZAxis(bool b)
{
	m_bLockZAxis = b;
}
#include "BulletScript.h"
#include "TransformComponent.h"

BulletScript::BulletScript(const float fLifeTime)
	:m_fLifeTime(fLifeTime)
{
	m_vDir = { 0,0,-1 };
	m_fCurrentLife = 0;
}

BulletScript::~BulletScript()
{
}

void BulletScript::Update(double dt)
{
	GetComponent<TransformComponent>()->Translate(100 * (float)dt * m_vDir);
	//--------------------------------------------------------------------------------
	m_fCurrentLife += (float)dt;
	if (m_fCurrentLife >= m_fLifeTime)
		DestroySelf();
}
void BulletScript::SetDirection(Vector3 vDir)
{
	m_vDir = vDir;
}
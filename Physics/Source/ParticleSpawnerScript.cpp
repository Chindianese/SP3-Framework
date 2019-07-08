#include "ParticleSpawnerScript.h"

ParticleSpawnerScript::ParticleSpawnerScript(GameObject* ParticleRef, const float fSpawnRate, const Vector3 vSpawnRadius, const float fSizeOffset, std::string sLayer)
	: m_ParticleRef(ParticleRef)
	, m_fSpawnRate(fSpawnRate)
	, m_vSpawnRadius(vSpawnRadius)
	, m_fSizeOffset(fSizeOffset)
	, m_sLayer(sLayer)
{
	m_fCurrentTime = 0;
}

ParticleSpawnerScript::~ParticleSpawnerScript()
{
}

void ParticleSpawnerScript::Update(double dt)
{
	m_fCurrentTime += (float)dt;
	//--------------------------------------------------------------------------------
	if (m_fCurrentTime <= m_fSpawnRate)
		return;
	m_fCurrentTime = 0;
	TransformComponent* Trans = GetComponent<TransformComponent>();
	Vector3 vScale;
	vScale.x = Math::RandFloatMinMax((1 - m_fSizeOffset), (1 + m_fSizeOffset));
	vScale.y = Math::RandFloatMinMax((1 - m_fSizeOffset), (1 + m_fSizeOffset));
	vScale.z = Math::RandFloatMinMax((1 - m_fSizeOffset), (1 + m_fSizeOffset));

	float fXPos = Trans->GetPosition().x + Math::RandFloatMinMax(-m_vSpawnRadius.x, m_vSpawnRadius.x);
	float fYPos = Trans->GetPosition().y + Math::RandFloatMinMax(-m_vSpawnRadius.y, m_vSpawnRadius.y);
	float fZPos = Trans->GetPosition().z + Math::RandFloatMinMax(-m_vSpawnRadius.z, m_vSpawnRadius.z);
	Vector3 SpawnPosition = Vector3{ fXPos, fYPos, fZPos };
	Instantiate(m_ParticleRef, SpawnPosition, vScale, m_sLayer);
}
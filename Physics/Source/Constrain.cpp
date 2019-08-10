#include "Constrain.h"
#include "LoadHmap.h"
#include "TransformComponent.h"
#include "PhysicsScript.h"
Constrain::Constrain(HeightMapData* data, eConstrainTypes type, float distance)
	: m_Data(data)
	, m_ConstrainType(type)
	, m_fDistance (distance)
{
}

Constrain::~Constrain()
{
}

void Constrain::Update(double dt)
{
	TransformComponent* trans = TRANS;
	Vector3 Scale = m_Data->GetScale();
	_heightmap* heightMap = m_Data->GetHeightMap();
	Vector3 pos = trans->GetPosition();
	Vector3 terrainPos = { pos.x, Scale.y * ReadHeightMap(*heightMap, pos.x / Scale.x, pos.z / Scale.z), pos.z };
	terrainPos.y += m_fDistance;
	switch (m_ConstrainType)
	{
	case Constrain::FIXED:
		trans->SetPosition(terrainPos);
		break;
	case Constrain::LIMIT:
		if (pos.y < terrainPos.y)
		{
			trans->SetPosition(terrainPos);
			PhysicsScript* phys = GetComponent<PhysicsScript>();
			if(phys != nullptr && phys->GetVelocity().y < 0) phys->SetVelocity(Vector3(0, 0, 0));
		}
		break;
	default:
		break;
	}
	Vector3 pos2 = trans->GetPosition();
	pos2.x = Math::Clamp(pos2.x, -120.f, 120.f);
	pos2.z = Math::Clamp(pos2.z, -120.f, 120.f);
	trans->SetPosition(pos2);
}

bool Constrain::IsOnGround()
{
	TransformComponent* trans = TRANS;
	Vector3 Scale = m_Data->GetScale();
	_heightmap* heightMap = m_Data->GetHeightMap();
	Vector3 pos = trans->GetPosition();
	float ground = Scale.y * ReadHeightMap(*heightMap, pos.x / Scale.x, pos.z / Scale.z) +  m_fDistance + 0.02f;
	return pos.y < ground;

}

void Constrain::SetHeight(float distance)
{
	m_fDistance = distance;
}
#include "Collider.h"
#include "TransformComponent.h"
#include "CollisionManager.h"

Collider::Collider(Vector3 radiusHeight)
{
	CollisionManager::GetInstance()->AddCollider(this);
	m_radiusHeight = radiusHeight;
}

Collider::~Collider()
{
}

void Collider::Update(double dt)
{
}

bool Collider::CheckCollision(Collider* c)
{
	Vector3 position1 = GetComponent<TransformComponent>()->GetPosition();
	Vector3 position2 = c->GetComponent<TransformComponent>()->GetPosition();
	Vector3 rh1 = m_radiusHeight;
	Vector3 rh2 = c->m_radiusHeight;
	Vector3 posXZ1 = position1;
	Vector3 posXZ2 = position2;
	posXZ1.y = 0;
	posXZ2.y = 0;
	if ((posXZ1 - posXZ2).Length() < rh1.x + rh2.x)
	{
		if (abs(position1.y - position2.y) < rh1.y + rh2.y)
			return true;
	}
	return false;
}

Vector3 Collider::GetRadiusHeight()
{
	return m_radiusHeight;
}
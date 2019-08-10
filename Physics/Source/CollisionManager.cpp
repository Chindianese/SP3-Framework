#include "CollisionManager.h"
#include "TransformComponent.h"
#include "Collider.h"
#include "CollisionResponseScript.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update(double dt)
{
	for (auto it = m_colliders.begin(); it != m_colliders.end(); ++it)
	{
		for (auto it2 = m_colliders.begin(); it2 != it; ++it2)
		{
			if ((*it)->CheckCollision((*it2)))
			{
				Collider* c1 = *it;
				Collider* c2 = *it2;
				Vector3 pos1 = c1->GetComponent<TransformComponent>()->GetPosition();
				Vector3 pos2 = c2->GetComponent<TransformComponent>()->GetPosition();
				Vector3 pos1new = (pos1 + pos2) * 0.5 + (pos1 - pos2).Normalized() * (c2->GetRadiusHeight().x + 2);
				Vector3 pos2new = (pos1 + pos2) * 0.5 + (pos2 - pos1).Normalized() * (c1->GetRadiusHeight().x + 2);
				pos1new.y = pos1.y;
				pos2new.y = pos2.y;
				c1->GetComponent<TransformComponent>()->SetPosition(pos1new);
				c2->GetComponent<TransformComponent>()->SetPosition(pos2new);
				if(c1->GetParent()->GetComponent<CollisionResponseScript>() != nullptr) c1->GetParent()->GetComponent<CollisionResponseScript>()->CollisionResponse(c2);
				if(c2->GetParent()->GetComponent<CollisionResponseScript>() != nullptr) c2->GetParent()->GetComponent<CollisionResponseScript>()->CollisionResponse(c1);
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* c)
{
	m_colliders.push_back(c);
}

void CollisionManager::RemoveCollider(Collider* c)
{
}

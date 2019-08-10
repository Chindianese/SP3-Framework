#pragma once
#include "Singleton.h"
#include "Collider.h"
#include <vector>
class CollisionManager : public Singleton<CollisionManager>
{
	friend Collider;
private:
	std::vector<Collider*> m_colliders;
public:
	CollisionManager();
	~CollisionManager();
	void Update(double dt);
	void AddCollider(Collider* c);
	void RemoveCollider(Collider* c);
};
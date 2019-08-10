#pragma once
#include "CollisionResponseScript.h"

class BulletCollisionResponse : public CollisionResponseScript
{
public:
	BulletCollisionResponse();
	virtual ~BulletCollisionResponse();
	virtual void Update(double dt);
	virtual void CollisionResponse(Collider* c);
	virtual ComponentBase* Clone()
	{
		return new BulletCollisionResponse(*this);
	}
};
#pragma once
#include "ScriptComponent.h"
#include "Constrain.h"
#include "CollisionResponseScript.h"
class RocketScript : public CollisionResponseScript
{
	Constrain* m_constrain;
public:
	RocketScript(Constrain* c);
	virtual void Update(double dt);
	virtual void CollisionResponse(Collider* c);
	virtual ComponentBase* Clone()
	{
		return new RocketScript(*this);
	}

};
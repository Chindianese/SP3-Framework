#pragma once
#include "ScriptComponent.h"
#include "Collider.h"

class CollisionResponseScript : public ScriptComponent
{
public:
	CollisionResponseScript();
	virtual ~CollisionResponseScript();
	virtual void Update(double dt);
	virtual void CollisionResponse(Collider* c) = 0;

};
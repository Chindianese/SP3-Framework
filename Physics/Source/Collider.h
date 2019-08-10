#pragma once
#include "ComponentBase.h"

class Collider : public ComponentBase
{
private:
	Vector3 m_radiusHeight;
public:
	Collider(Vector3 radiusHeight);
	virtual ~Collider();
	virtual void Update(double dt);
	virtual ComponentBase* Clone()
	{
		return new Collider(*this);
	};
	bool CheckCollision(Collider* c);
	Vector3 GetRadiusHeight();
};
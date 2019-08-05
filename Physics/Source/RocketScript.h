#pragma once
#include "ScriptComponent.h"
#include "Constrain.h"
class RocketScript : public ScriptComponent
{
	Constrain* m_constrain;
public:
	RocketScript(Constrain* c);
	virtual void Update(double dt);
	virtual ComponentBase* Clone()
	{
		return new RocketScript(*this);
	}

};
#pragma once
#include "ScriptComponent.h"
class CreeperSpawnerScript : public ScriptComponent
{
private:
	float timeout;
public:
	CreeperSpawnerScript();
	~CreeperSpawnerScript();
	void Update(double dt);
	ComponentBase* Clone()
	{
		return new CreeperSpawnerScript(*this);
	}
};
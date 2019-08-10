#pragma once
#include "ScriptComponent.h"
class AmmoBoxScript : public ScriptComponent
{
private:
	float m_fDelay;
public:
	AmmoBoxScript();
	virtual ~AmmoBoxScript();
	virtual void Update(double dt);
	virtual ComponentBase* Clone()
	{
		return new AmmoBoxScript(*this);
	}
};
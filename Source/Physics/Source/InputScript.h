#pragma once
#include "ScriptComponent.h"
class InputScript :
	public ScriptComponent
{
private:
	bool m_bTriggered;
public:
	void Start() override;
	void Update(double dt) override;
	virtual Component* Clone() { return new InputScript(*this); };
};

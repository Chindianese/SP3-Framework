#pragma once
#include "AbilityBase.h"
class AbilityGrenade :
	public AbilityBase
{
public:
	AbilityGrenade();
	AbilityGrenade(const float cooldowntime, const float cost);
	virtual ~AbilityGrenade();
	virtual void Use(Component* com);
	virtual void StopUse(Component* com);
};

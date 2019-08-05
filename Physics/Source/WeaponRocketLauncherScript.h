#pragma once
#include "WeaponScript.h"

class WeaponRocketLauncherScript : public WeaponScript
{
public:
	WeaponRocketLauncherScript();
	virtual void Fire();
	virtual void SetActive(bool b);
	virtual ComponentBase* Clone()
	{
		return new WeaponRocketLauncherScript(*this);
	}
};
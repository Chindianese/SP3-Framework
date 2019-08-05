#pragma once
#include "WeaponScript.h"

class WeaponSniperRifleScript : public WeaponScript
{
protected:
	bool m_bScoped;
	GameObject* scopeOverlay;
public:
	WeaponSniperRifleScript();
	virtual void Update(double dt);
	virtual ComponentBase* Clone()
	{
		return new WeaponSniperRifleScript(*this);
	}
	virtual void SetActive(bool b);
	virtual void Fire();

};
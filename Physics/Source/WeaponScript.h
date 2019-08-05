#pragma once
#include "ScriptComponent.h"
class WeaponScript : public ScriptComponent
{
protected:
	float m_fFireRate;
	float m_fReloadTime;
	float m_fUseCooldown;
	float m_fProjectileSpeed;
	int m_iHeldBullets;
	int m_iClipSize;
	int m_iHeldClips;
	int m_iMaxClips;
	GameObject* m_screenOverlay;
public:
	WeaponScript();
	virtual ~WeaponScript();
	virtual void Update(double dt);
	virtual void Fire();
	virtual ComponentBase* Clone()
	{
		return new WeaponScript(*this);
	}
	int GetHeldBullets();
	int GetHeldClips();
};
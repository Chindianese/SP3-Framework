#pragma once
#include "ScriptComponent.h"
#include "GameObject.h"
#include <string>
class GunScript : public ScriptComponent
{
public:
	enum eFIRE_TYPES
	{
		SEMI_AUTO,
		FULL_AUTO,
		CHARGE,
	};
private:
	GameObject* m_Bullet;;
	float m_fTimer;
	const float m_fFireRate;
	GameObject* m_Player;
	//bool m_bSemi;
	eFIRE_TYPES m_eFireType;
	int m_iNumClips;
	int m_iClipAmmo;
	int m_iClipAmmoMax;
	bool m_bTriggerDown;

	float m_fChargeTime;
	float m_fMaxChargeTime;
	float m_fMinChargeTime;

	float m_fMaxScale;
public:
	GunScript(GameObject* bullet, GameObject* player, const float fFireRate, eFIRE_TYPES eFireType);
	~GunScript();
	virtual ComponentBase* Clone()
	{
		return new GunScript(*this);
	}

	void Update(double dt) override;
	void Fire(Vector3 vDir);
	void PullTrigger(Vector3 vDir, double dt);
	void Reload();
	void ReleaseTrigger(Vector3 vDir);
};
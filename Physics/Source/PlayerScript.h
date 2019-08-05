#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
#include "WeaponScript.h"
class PlayerScript : public ScriptComponent
{
private:
	Vector3 m_vCameraFront;
	Vector3 m_vCameraUp;
	std::vector<WeaponScript*> m_weapons; 
	GameObject* m_ammoText;
	int weaponIndex;
	float walkCameraDelay;
	bool cameraSwayDirection;
public:
	void AddWeapon(WeaponScript* weapon);
	PlayerScript(GameObject* ammoText);
	virtual ~PlayerScript();
	virtual ComponentBase* Clone()
	{
		return new PlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;
};

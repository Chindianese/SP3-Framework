#pragma once
#include "ComponentBase.h"
#include "GameObject.h"
#include <string>
#include "Time.h"
#include "ComponentMacros.h"

#include "LightManager.h"
#include "Camera.h"
class ScriptComponent : public ComponentBase
{
protected:
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer = "Default") const;
	GameObject* Instantiate(const GameObject* goRef, std::string sLayer = "Default") const;
	void Destroy(GameObject* go);
	void DestroySelf();
	// QoL
	Camera* GetCamera();
	GameObject* GetCameraGO();
	LightManager* GetLightManager();
	TransformComponent* GetTransform();
	Vector3 GetPosition();
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt);
	virtual void Collide(GameObject*);
	virtual ComponentBase* Clone() = 0;
};

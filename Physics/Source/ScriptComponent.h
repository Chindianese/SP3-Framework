#pragma once
#include "ComponentBase.h"
#include "GameObject.h"
#include <string>
#include "Time.h"
class ScriptComponent :
	public ComponentBase
{
protected:
	GameObject* Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer = "Default");
	GameObject* Instantiate(GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer = "Default");
	GameObject* Instantiate(GameObject* goRef, Vector3 pos, std::string sLayer = "Default");
	GameObject* Instantiate(GameObject* goRef, std::string sLayer = "Default");
	void Destroy(GameObject* go);
	void DestroySelf();
public:
	ScriptComponent();
	virtual ~ScriptComponent();

	virtual void Update(double dt);
	virtual void Start();
	virtual void Collide(GameObject*);
	virtual ComponentBase* Clone() = 0;
};

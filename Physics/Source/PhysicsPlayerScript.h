#pragma once
#include "ScriptComponent.h"
#include "CameraComponent.h"
class PhysicsPlayerScript : public ScriptComponent
{
private:
	Vector3 m_vCameraFront;
	Vector3 m_vCameraUp;
	GameObject* m_RefBall;
	GameObject* m_RefBall2;
	GameObject* m_RefBall3;
public:
	PhysicsPlayerScript(GameObject* goRef, GameObject* goRef2, GameObject* goRef3);
	virtual ~PhysicsPlayerScript();
	virtual ComponentBase* Clone()
	{
		return new PhysicsPlayerScript(*this);
	}

	void Update(double dt) override;
	virtual void Start() override;
};
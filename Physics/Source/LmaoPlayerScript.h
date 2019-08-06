#pragma once
#include "ScriptComponent.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "RojakScene2.h"
class LmaoPlayerScript :
	public ScriptComponent
{
private:
public:
	LmaoPlayerScript();
	virtual ~LmaoPlayerScript();
	virtual ComponentBase* Clone() { return new LmaoPlayerScript(*this); };
	virtual void Update(double dt)
	{
		if (KeyboardManager::GetInstance()->GetKeyTriggered("SwitchMap"))
		{
			SceneManager::GetInstance()->ChangeScene(new RojakScene2());
		}
	}
};

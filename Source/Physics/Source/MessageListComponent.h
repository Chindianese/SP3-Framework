#pragma once
#include "ScriptComponent.h"
#include <vector>
#include <string>
#include "GameObject.h"
class MessageListComponent :
	public ScriptComponent
{
private:
	std::vector<std::string> messageList;
	std::vector<GameObject*> messageGOList;
	GameObject* msgRef;
public:
	MessageListComponent(GameObject* messageRef);
	virtual Component* Clone() { return new MessageListComponent(*this); };
	void AddMessage(std::string s);
	virtual void Update(double dt) override;
};

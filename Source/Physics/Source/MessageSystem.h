#pragma once
#include "Singleton.h"
#include "GameObject.h"
class MessageSystem : public Singleton<MessageSystem>
{
private:
	GameObject* messageList;
public:
	void Init(GameObject* go);
	void ReceiveMessage(std::string s);
};

#include "MessageListComponent.h"
#include "ComponentMacros.h"
#include "RenderComponent.h"
MessageListComponent::MessageListComponent(GameObject* messageRef)
{
	msgRef = messageRef;
}

void MessageListComponent::AddMessage(std::string s)
{
	messageList.push_back(s);
	Vector3 pos = { 1920 / 2, 1080 / 2, 100 };
	GameObject* msg = Instantiate(this->msgRef, pos, "UI");
	msg->RENDER->SetText(s);
	for (auto go : messageGOList)
	{
		go->TRANS->Translate(0, 110, 0);
	}
	messageGOList.push_back(msg);
}

void MessageListComponent::Update(double dt)
{
}
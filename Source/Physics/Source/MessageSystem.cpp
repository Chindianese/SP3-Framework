#include "MessageSystem.h"
#include "MessageListComponent.h"
void MessageSystem::Init(GameObject* go)
{
	messageList = go;
}

void MessageSystem::ReceiveMessage(std::string s)
{
	if (!messageList)
		__debugbreak();
	messageList->GetComponent<MessageListComponent>()->AddMessage(s);
}
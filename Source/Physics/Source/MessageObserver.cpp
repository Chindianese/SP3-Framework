#include "MessageObserver.h"
#include "Component.h"
#include "MessageSystem.h"
MessageObserver::MessageObserver()
{
}

MessageObserver::~MessageObserver()
{
}

void MessageObserver::Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList)
{
	if (msg == "INIT_CLIENT")
	{
		clientSystem.Init();
	}
	int index = msg.find(":");
	std::string sub = msg.substr(0, index);
	if (sub == "SEND")
	{
		std::string m = msg.substr(index + 1, msg.size() - 1);
		clientSystem.Send(m);
		DEFAULT_LOG(msg);
	}
	if (sub == "RECV")
	{
		std::string m = msg.substr(index + 1, msg.size() - 1);
		// clientSystem.Send(m);
		MessageSystem::GetInstance()->ReceiveMessage(m);
		// DEFAULT_LOG(msg);
	}
}
#pragma once
#include <vector>
#include "ObserverBase.h"
#include "ComponentBase.h"
#include "Singleton.h"
#include "Message.h"
#include "GameObject.h"
class GenericSubject : public Singleton<GenericSubject>
{
private:
	std::vector<ObserverBase*> m_List;
	std::vector<Message*> m_Messages;
	void ClearMessages();
public:
	GenericSubject();
	~GenericSubject();

	void NotifySubject(ComponentBase* com, std::string msg);
	void NotifyObservers(std::vector<GameObject*>* OBComList);
};


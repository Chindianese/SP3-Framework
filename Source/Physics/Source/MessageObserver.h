#pragma once
#include "ObserverBase.h"
#include "ComponentBase.h"
#include "ClientSystem.h"
class MessageObserver :
	public ObserverBase
{
private:
	ClientSystem clientSystem;
public:
	MessageObserver();
	virtual ~MessageObserver();

	virtual void Notify(ComponentBase* com, std::string msg, std::vector<GameObject*>* OBComList) override;
};
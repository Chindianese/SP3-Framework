#pragma once
#include "ComponentBase.h"
#include "Utility.h"
/**********************************************************8*********************/
/*!
\author Hao Cheng
\brief
base observer component. During engine update. GO with this component is sent to
Generic subject to be updated
/*!
/********************************************************************************/
class ObserverComponent :
	public Component
{
public:
	ObserverComponent();
	virtual ~ObserverComponent();
	virtual void Notify(Component* com, std::string msg);
};

#pragma once
#include "ComponentBase.h"
/********************************************************************************/
/*!
\author Hao Cheng
\brief
UI Button interaction. Collision with button is based on mesh with 1x1 aspect
/*!
/********************************************************************************/
class UIButtonComponent :
	public ComponentBase
{
private:
	bool m_bIsHover;
public:
	UIButtonComponent();
	virtual ~UIButtonComponent();
	virtual ComponentBase* Clone() { return new UIButtonComponent(*this); };

	virtual void Update(double dt) override;
};


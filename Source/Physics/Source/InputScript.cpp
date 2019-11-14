#include "InputScript.h"
#include "Application.h"
#include "InputManager.h"

void InputScript::Start()
{
	m_bTriggered = true;
}

void InputScript::Update(double dt)
{
	if (Application::Key == ' ')
		m_bTriggered = false;
	else if (!m_bTriggered)
	{
		this->m_GO->RENDER->AddText(toupper(Application::Key));
	}
	if (InputManager::GetInstance()->GetInputStrength("Back"))
	{
		this->m_GO->RENDER->RemoveText();
	}
	if (InputManager::GetInstance()->GetInputStrength("Enter"))
	{
		if (this->m_GO->RENDER->GetText() != "")
		{
			this->Notify("SEND:" + this->m_GO->RENDER->GetText());
			this->m_GO->RENDER->SetText("");
		}
	}
}
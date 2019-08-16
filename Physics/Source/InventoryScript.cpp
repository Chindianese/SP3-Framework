#include "InventoryScript.h"
#include "InputManager.h"
#include "UIButtonComponent.h"
#include "WeaponScript.h"
#include "Application.h"
InventoryScript::InventoryScript(GameObject* weapon, std::vector<GameObject*> list, std::vector<GameObject*> wlist)
	: m_WeaponSlotList(wlist)
{
	m_Weapon = weapon;
	m_SlotList = list;
	m_Holding = nullptr;
	m_iHoldingIndex = -1;
}

InventoryScript::~InventoryScript()
{
}
void InventoryScript::Update(double dt)
{
	// Check if inventory click
	if (InputManager::GetInstance()->GetInputStrength("Click"))
	{
		if (m_Holding)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (m_WeaponSlotList[i]->GetComponent<UIButtonComponent>()->GetHover())
				{
					switch (i)
					{
					case 0:
						Attach();
						m_Holding = nullptr;
						break;
					case 1:
						Attach();
						m_Holding = nullptr;
						break;
					case 2:
						Attach();
						m_Holding = nullptr;
						break;
					case 3:
						Attach();
						m_Holding = nullptr;
						break;
					default:
						break;
					}
					CHENG_LOG("Part added");
					break;
				}
			}
		}
		else
		{
			for (unsigned i = 0; i < m_InventoryItems.size(); ++i)
			{
				if (m_SlotList[i]->GetComponent<UIButtonComponent>()->GetHover())
				{
					if (!m_InventoryItems[i])
						return;
					GameObject* Part = m_InventoryItems[i];
					m_Holding = Part;
					m_iHoldingIndex = i;
					CHENG_LOG("Part added");
					break;
				}
			}
		}
		
	}
	if (m_Holding)
	{
		double x, y;
		Application::GetCursorPosRelative(&x, &y);

		Vector3 ScreenMousePos(x * 1920, (1-y) * 1080);

		m_Holding->TRANS->SetPosition(ScreenMousePos);
	}
}
void InventoryScript::AddItem(GameObject* go)
{
	if (m_InventoryItems.size() < INVENTORY_SIZE)
	{
		Vector3 pos = m_SlotList.at(m_InventoryItems.size())->TRANS->GetPosition();
		Vector3 scal = { 20,20,1 };
		GameObject* go2 = Instantiate(go, pos, scal, "UI");
		go2->RIGID->SetAffectedByGravity(false);
		m_InventoryItems.push_back(go2);
		Destroy(go);
	}
}

void InventoryScript::Attach()
{
	GameObject* go = m_InventoryItems[m_iHoldingIndex];
	GameObject* cpy = Instantiate(go, Vector3{ 0,0,0 }, Vector3{ 1,1,1 }, "Default", true);
	cpy->RIGID->SetAffectedByGravity(false);
	m_Weapon->AddChild(cpy);
	m_Weapon->GetComponent<WeaponScript>()->AddPart(cpy);
	Destroy(go);
	m_InventoryItems.erase(m_InventoryItems.begin() + m_iHoldingIndex);
}

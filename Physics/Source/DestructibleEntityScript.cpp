#include "DestructibleEntityScript.h"
#include "RenderComponent.h"

DestructibleEntityScript::DestructibleEntityScript()
	: EntityScript(),
	m_sMessage(""),
	m_iHealth(50)

{
}

DestructibleEntityScript::DestructibleEntityScript(std::string s)
	: EntityScript(),
	m_sMessage(s),
	m_iHealth(50)
{
}

DestructibleEntityScript::~DestructibleEntityScript()
{
	// delete m_particleSpawnerRef;
}

void DestructibleEntityScript::Update(double dt)
{
	// Check death
	if (m_iHealth <= 0)
	{
		if (m_sMessage == "")
		{
			Notify("DestructibleEntityDied");
		}
		else
			Notify(m_sMessage);

		//destroy self
		return;
	}
	if (m_SW.Stop()->GetTime() >= DAMAGE_TIME && m_bDamageAnim)
	{
		m_bDamageAnim = false;

		auto childrenderer = TRANS;
		if (!childrenderer)
		{
			if (GetChild(0) != nullptr)
				GetChild(0)->RENDER->ResetColor();

			else
				RENDER->ResetColor();
		}
	}
	if (IsDamageAnim())
	{
	}
}

void DestructibleEntityScript::Collide(GameObject *)
{
}

void DestructibleEntityScript::SetMessage(std::string s)
{
	m_sMessage = s;
}

void DestructibleEntityScript::SetHealth(int i)
{
	m_iHealth = i;
}

int DestructibleEntityScript::GetHealth()
{
	return m_iHealth;
}

void DestructibleEntityScript::Damage(int damage)
{
		m_bDamageAnim = true;

		auto childrenderer = TRANS;
		if (childrenderer == nullptr)
		{
			if (GetChild(0) != nullptr)
				GetChild(0)->RENDER->SetColor(50, 50, 50);
		}
		else
			RENDER->SetColor(50, 50, 50);
		m_SW.Start();
		m_iHealth -= damage;
}

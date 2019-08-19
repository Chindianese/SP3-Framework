#include "WanderState.h"
#include "EntityScript.h"
#include "IdleState.h"
#include "SceneManager.h"

#define MIN_TIME 1
#define MAX_TIME 5

WanderState::WanderState(State* Combat)
	: AIState(Combat)
{
	m_fTime = 0;
}

WanderState::~WanderState()
{
}

State * WanderState::HandleState(ComponentBase * com)
{
	// Check for player
	if (PlayerInRange(com))
	{
		m_Combat->OnEnter(com);
		return m_Combat;
	}
	if (m_SW.Stop()->GetTime() < m_fTime)
	{
		com->GetComponent<EntityScript>()->RotateTowards(m_vDir);
		com->GetComponent<EntityScript>()->MoveForwards();
		this->OnEnter(com);
		return this;
	}
	else
	{
		State* s = new IdleState(m_Combat);
		s->OnEnter(com);
		return s;
	}
}

void WanderState::OnEnter(ComponentBase * com)
{
	m_SW.Start();
	m_fTime = Math::RandFloatMinMax(MIN_TIME, MAX_TIME);
	// Rand dir
	while (m_vDir.IsZero())
	{
		m_vDir.x = Math::RandFloatMinMax(-1, 1);
		m_vDir.z = Math::RandFloatMinMax(-1, 1);
	}
	m_vDir.Normalize();
}

void WanderState::OnExit(ComponentBase * com)
{
}
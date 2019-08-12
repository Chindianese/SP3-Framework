#include "StandingState.h"
#include "CrouchingState.h"
#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "InputManager.h"

StandingState::StandingState()
{
	m_fBaseAccel = 300;
	m_fSprintMultiplier = 2.0f;
	m_fBaseMovementSpeed = 40;
}

StandingState::~StandingState()
{
}

PlayerState* StandingState::HandleInput(ComponentBase* com, double dt)
{
	// Sprint
	if (InputManager::GetInstance()->GetInputStrength("PlayerSprint"))
	{
		com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed * m_fSprintMultiplier, m_fBaseAccel * m_fSprintMultiplier);
	}
	else
	{
		com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, m_fBaseAccel);
	}
	// Crouch
	if (InputManager::GetInstance()->GetInputStrength("PlayerCrouch"))
	{
		return new CrouchingState;
	}

	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, STANDING_HEIGHT, 0);
	return nullptr;
}
void StandingState::OnEnter(ComponentBase* com)
{
	SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<TransformComponent>()->SetRelativePosition(0, STANDING_HEIGHT, 0);
	com->GetComponent<PlayerScript>()->SetMovementSpeed(m_fBaseMovementSpeed, m_fBaseAccel);
}
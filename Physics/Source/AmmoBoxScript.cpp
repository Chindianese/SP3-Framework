#include "AmmoBoxScript.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "PlayerScript.h"

AmmoBoxScript::AmmoBoxScript()
{
}

AmmoBoxScript::~AmmoBoxScript()
{
}

void AmmoBoxScript::Update(double dt)
{
	m_fDelay -= dt;
	if (InputManager::GetInstance()->GetInputStrength("PlayerUseObject") != 0 && m_fDelay < 0)
	{
		TransformComponent* trans = TRANS;
		TransformComponent* playerTrans = GetCameraGO()->TRANS;
		if ((trans->GetPosition() - playerTrans->GetPosition()).Length() < 30)
		{
			m_fDelay = 0.3;
			GetCameraGO()->GetParent()->GetComponent<PlayerScript>()->GetWeapon()->PickUpAmmo(1);
		}
	}
}

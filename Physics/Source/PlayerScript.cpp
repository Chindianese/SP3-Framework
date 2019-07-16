#include "PlayerScript.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
PlayerScript::PlayerScript(GameObject* goRef)
	:m_GORef(goRef)
{
}

PlayerScript::~PlayerScript()
{
}
void PlayerScript::Start()
{
}
void PlayerScript::Update(double dt)
{
	Vector3 vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	Vector3 vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();

	float fSpeed = 50 * (float)dt;
	Vector3 vRight = vCameraFront.Cross(vCameraUp);
	static bool triggered = false;
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
	{
		trans->Translate(fSpeed * vCameraUp);
		if (!triggered)
		{
			Instantiate(m_GORef);
			triggered = true;
		}
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
	{
		trans->Translate(-fSpeed * vCameraFront);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
	{
		trans->Translate(-fSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
	{
		trans->Translate(fSpeed * vRight);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveUp"))
	{
		trans->Translate(fSpeed * vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveDown"))
	{
		trans->Translate(-fSpeed * vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("Susu"))
	{
		//AudioManager::GetInstance()->Play3D("susu.wav", Vector3(0, 0, 2));
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(false);
		GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
		trans->SetPosition(0, 0, 0);
		cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 200, 0);
		cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(0, -90);
	}
}
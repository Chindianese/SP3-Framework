#include "ChengPlayerScript.h"
#include "Application.h"
#include "SceneManager.h"
#include "GunScript.h"
#include "LoadHmap.h"
#include "KeyboardManager.h"
#include "MeshController.h"
#include "Mesh.h"
#include "Time.h"
#include "GauntletScript.h"
ChengPlayerScript::ChengPlayerScript(GameObject* gun, GameObject* cross, GameObject* gaunt)
	:m_Gun(gun)
	, m_CrossHair(cross)
	, m_Gaunt(gaunt)
{
	m_CurrentState = nullptr;
	m_bState = false;
	m_fMovementSpeed = 1;
	m_Light = SceneManager::GetInstance()->GetScene()->GetLightManager()->AddLight(Light::LIGHT_POINT);
	m_Light->power = 3;
	m_Light->color.r = 0;
	m_Light->color.g = 1;
}

ChengPlayerScript::~ChengPlayerScript()
{
	if (m_CurrentState)
		delete m_CurrentState;
}
void ChengPlayerScript::Start()
{
	SwitchView();
}
void ChengPlayerScript::Update(double dt)
{
	// Movement================================================================================
	UpdateMovement(dt);
	// Camera================================================================================
	if (KeyboardManager::GetInstance()->GetKeyTriggered("switchCamOrtho"))
		SwitchView();
	// Gauntlet================================================================================
	if (KeyboardManager::GetInstance()->GetKeyTriggered("triggerGauntlet"))
	{
		if (m_Gaunt->IsActive())
		{
			m_Gaunt->SetActive(false);
		}
		else
		{
			m_Gaunt->SetActive(true);
		}
	}
	if (m_Gaunt->IsActive())
	{
		if (KeyboardManager::GetInstance()->GetKeyTriggered("rotateGauntForward"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->RotateForward();
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("rotateGauntBackward"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->RotateBackward();
		}
		if (KeyboardManager::GetInstance()->GetKeyTriggered("useGauntlet"))
		{
			m_Gaunt->GetComponent<GauntletScript>()->Use();
		}
	}
	// TODO Constrain to terrain================================================================================
	//trans->SetPosition(pos.x, 50.f * ReadHeightMap(DataContainer::GetInstance()->heightMap, pos.x / 500, pos.z / 500) - 20, pos.z);
	//trans->SetPosition({ pos.x,0,pos.z });
}
void ChengPlayerScript::SetMovementSpeed(float f)
{
	m_fMovementSpeed = f;
}
void ChengPlayerScript::SwitchView()
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	if (m_bState)
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(true);
		GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
		//trans->SetPosition(0, 0, 0);
		cam->GetComponent<TransformComponent>()->SetRelativePosition(0, 20, 0);
		cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(0, 0);
		m_Gun->SetActive(true);
		m_CrossHair->SetActive(true);
		m_bState = false;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(false);
	}
	else
	{
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
		SceneManager::GetInstance()->GetScene()->GetCameraGameObject()->GetComponent<CameraComponent>()->SetMouseEnabled(false);
		GameObject* cam = SceneManager::GetInstance()->GetScene()->GetCameraGameObject();
		//trans->SetPosition(0, 0, 0);
		cam->GetComponent<TransformComponent>()->SetRelativePosition(-pos.x, 300, -pos.z);
		cam->GetComponent<CameraComponent>()->GetCamera()->SetDir(-90, -90);
		m_Gun->SetActive(false);
		m_CrossHair->SetActive(false);
		m_bState = true;
		SceneManager::GetInstance()->GetScene()->SetCursorEnabled(true);
	}
}
void ChengPlayerScript::UpdateMovement(double dt)
{
	TransformComponent* trans = GetComponent<TransformComponent>();
	Vector3 pos = trans->GetPosition();
	m_Light->position = { trans->GetPosition().x, trans->GetPosition().y, trans->GetPosition().z };
	m_Light->position.z += 30;
	if (!m_bState)
	{
		if (!m_CurrentState)
		{
			m_CurrentState = new StandingState;
			m_CurrentState->OnEnter(this);
		}
		PlayerState* state = m_CurrentState->HandleInput(this, dt);
		if (m_CurrentState != state && state != nullptr)
		{
			state->OnEnter(this);
			delete m_CurrentState;
			m_CurrentState = state;
		}

		Vector3 vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
		Vector3 vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();

		Vector3 vPlayerFront = vCameraFront;
		vPlayerFront.y = 0;
		//vPlayerFront.Normalize();
		Vector3 vRight = vCameraFront.Cross(vCameraUp);

		// Movement
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
		{
			trans->Translate(m_fMovementSpeed * vPlayerFront);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
		{
			trans->Translate(-m_fMovementSpeed * vPlayerFront);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveLeft"))
		{
			trans->Translate(-m_fMovementSpeed * vRight);
		}
		if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveRight"))
		{
			trans->Translate(m_fMovementSpeed * vRight);
		}
		// Gun================================================================================
		// Fire--------------------------------------------------------------------------------
		if (Application::IsMousePressed(0))
		{
			this->m_Gun->GetComponent<GunScript>()->PullTrigger(vCameraFront, dt);
		}
		else
		{
			this->m_Gun->GetComponent<GunScript>()->ReleaseTrigger(vCameraFront);
		}
		//Reload--------------------------------------------------------------------------------
		if (KeyboardManager::GetInstance()->GetKeyTriggered("reload"))
		{
			m_Gun->GetComponent<GunScript>()->Reload();
		}
		// Underwater================================================================================
		if (trans->GetPosition().y < -10)
		{
			// Trigger underwater
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Underwater"));
		}
		else
		{
			SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->GetLayerList()->at("Default")->SetShader(DataContainer::GetInstance()->GetShader("Default"));
		}
	}
}
#include "PhysicsPlayerScript.h"
#include "KeyboardManager.h"
#include "SceneManager.h"
#include "AudioManager.h"
#include "ChengRigidbody.h"
PhysicsPlayerScript::PhysicsPlayerScript(GameObject* goRef, GameObject* goRef2)
	:m_RefBall(goRef)
	, m_RefBall2(goRef2)
{
}

PhysicsPlayerScript::~PhysicsPlayerScript()
{
}
void PhysicsPlayerScript::Start()
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetTarget();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
}
void PhysicsPlayerScript::Update(double dt)
{
	m_vCameraFront = SceneManager::GetInstance()->GetScene()->GetCamera()->GetDir();
	m_vCameraUp = SceneManager::GetInstance()->GetScene()->GetCamera()->GetUp();
	TransformComponent* trans = GetComponent<TransformComponent>();

	float fSpeed = 50 * (float)dt;
	Vector3 vRight = m_vCameraFront->Cross(*m_vCameraUp);
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveForward"))
	{
		trans->Translate(fSpeed * *m_vCameraFront);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveBackward"))
	{
		trans->Translate(-fSpeed * *m_vCameraFront);
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
		trans->Translate(fSpeed * *m_vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyDown("PlayerMoveDown"))
	{
		trans->Translate(-fSpeed * *m_vCameraUp);
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("spawnBall"))
	{
		CHENG_LOG("spawned ball");
		GameObject* ball = Instantiate(m_RefBall, Vector3{ 0,0,-5 });
		ball->GetComponent<ChengRigidbody>()->SetVel({ 0,0,5 });
	}
	if (KeyboardManager::GetInstance()->GetKeyTriggered("spawnBall2"))
	{
		CHENG_LOG("spawned ball2");
		GameObject* ball = Instantiate(m_RefBall2, Vector3{ 0,0,5 });
		ball->GetComponent<ChengRigidbody>()->SetVel({ 0,0,-5 });
	}
}
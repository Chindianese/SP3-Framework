#include "CameraScript.h"
#include "Utility.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "Mtx44.h"
#include "Preferences.h"
#include "Resources.h"

#define LERP_RATE .05f
#define LERP_RATE_M .05f

Vector3 CameraScript::m_vFront;
Vector3 CameraScript::m_vRight;
Vector3 CameraScript::m_vOffset;
Vector3 CameraScript::m_vRotateOffset;
bool CameraScript::m_bIsTopDown;
bool CameraScript::m_bRotating;

CameraScript::CameraScript(GameObject* vTarget)
	:m_vTarget(vTarget)
{
	m_bRotating = false;
	m_fCamDist = std::stof(Preferences::GetPref(Resources::PreferencesTerm::CamDist));
	m_bIsTopDown = false;
}

CameraScript::~CameraScript()
{
}
void CameraScript::Start()
{
	GetComponent<CameraComponent>()->GetCamera()->SetDir({ -1, -1, -1 });
	m_vOffset = { m_fCamDist,m_fCamDist,m_fCamDist };
	m_vRotateOffset = { m_fCamDist,m_fCamDist,m_fCamDist };
	m_vFront = { -1,0,-1 };
	m_vFront.Normalize();
	m_vRight = { 1,0,-1 };
	m_vRight.Normalize();
}
void CameraScript::Update(double d)
{
	Vector3 Pos = m_vTarget->TRANS->GetPosition();
	GetCamera()->SetDir(m_vTarget->TRANS->GetPosition() - Pos);
}
Vector3 CameraScript::GetFront()
{
	return m_vFront;
}
Vector3 CameraScript::GetRight()
{
	return m_vRight;
}
Vector3 CameraScript::GetOffset()
{
	return m_vOffset;
}
Vector3 CameraScript::GetRotateOffset()
{
	return m_vRotateOffset;
}
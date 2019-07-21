#include "GauntletScript.h"
#include "MeshController.h"
#include "WorldValues.h"
#include "Time.h"
#include "ChengRigidbody.h"
#include "Application.h"
GauntletScript::GauntletScript(GameObject* ball)
	:m_Ball(ball)
{
	m_eStone = NONE;
	m_MC = nullptr;
	m_bInUse = false;
	m_fStartTime = 0;
	m_fDuration = 0;
}

GauntletScript::~GauntletScript()
{
}
void GauntletScript::Start()
{
	m_MC = GetComponent<MeshController<Mesh>>();
}
void GauntletScript::Update(double dt)
{
	if (m_bInUse)
	{
		if (m_fDuration != -1)
		{
			if (Time::GetInstance()->GetElapsedTimeF() > m_fStartTime + m_fDuration)
			{
				StopUse();
				m_fStartTime = 0;
				m_fDuration = 0;
			}
		}
	}
}
void GauntletScript::RotateForward()
{
	if (m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		m_MC->SetMesh("GauntSoul");
		break;
	case SOUL:
		m_MC->SetMesh("GauntReality");
		break;
	case REALITY:
		m_MC->SetMesh("GauntSpace");
		break;
	case SPACE:
		m_MC->SetMesh("GauntPower");
		break;
	case POWER:
		m_MC->SetMesh("GauntTime");
		break;
	case TIME:
		m_MC->SetMesh("GauntMind");
		break;
	case MIND:
		m_MC->SetMesh("Gaunt");
		break;
	default:
		break;
	}
	m_eStone = static_cast<eSTONES>((m_eStone + 1) % TOTAL);
}
void GauntletScript::RotateBackward()
{
	if (m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		m_MC->SetMesh("GauntMind");
		break;
	case SOUL:
		m_MC->SetMesh("Gaunt");
		break;
	case REALITY:
		m_MC->SetMesh("GauntSoul");
		break;
	case SPACE:
		m_MC->SetMesh("GauntReality");
		break;
	case POWER:
		m_MC->SetMesh("GauntSpace");
		break;
	case TIME:
		m_MC->SetMesh("GauntPower");
		break;
	case MIND:
		m_MC->SetMesh("GauntTime");
		break;
	default:
		break;
	}
	m_eStone = static_cast<eSTONES>((m_eStone - 1) % TOTAL);
	if (m_eStone == -1)
		m_eStone = static_cast<eSTONES>(TOTAL - 1);
}
void GauntletScript::Use()
{
	m_MC->SetMesh("GauntFist");
	if (m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		break;
	case SOUL:
		break;
	case REALITY:
		WorldValues::GravityExponent = { 0,0,0 };
		m_fStartTime = Time::GetInstance()->GetElapsedTimeF();
		m_fDuration = 5.f;
		break;
	case SPACE:
	{
		// Spawn ball
		float fScale = 2;
		float fBallSpeed = 120.f;
		//Vector3 ballDir = {};
		double x, y;
		Application::GetCursorPos(&x, &y);
		float posx = (float)x / Application::GetWindowWidth() * 300 - 150;
		float posz = (float)y / Application::GetWindowHeight() * 300 - 150;

		Vector3 pos = { posx, 10, posz };
		GameObject* bul = Instantiate(m_Ball, pos);
		if (!bul)
			return;
		bul->GetComponent<TransformComponent>()->SetScale(fScale, fScale, fScale);
		//bul->GetComponent<ChengRigidbody>()->SetVel(fBallSpeed * ballDir);
		bul->GetComponent<ChengRigidbody>()->SetMass(fScale);
		m_fStartTime = Time::GetInstance()->GetElapsedTimeF();
		m_fDuration = .5f;
	}
	break;
	case POWER:
		break;
	case TIME:
		break;
	case MIND:
		break;
	default:
		break;
	}

	m_bInUse = true;
}
void GauntletScript::StopUse()
{
	if (!m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		break;
	case SOUL:
		break;
	case REALITY:
		WorldValues::GravityExponent = WorldValues::DefaultGravityExponent;
		m_MC->SetMesh("GauntReality");
		break;
	case SPACE:
		m_MC->SetMesh("GauntSpace");
		break;
	case POWER:
		break;
	case TIME:
		break;
	case MIND:
		break;
	default:
		break;
	}

	m_bInUse = false;
}
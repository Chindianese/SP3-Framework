#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera()
{
	Reset();
	m_fCamSpeed.SetZero();
	m_fMaxCamSpeed = 1000.0f;
	m_fMinCamForce = 2.0f;
	m_fPitch = 0;
	m_fYaw = 270;
	m_bIsFirstMouseMove = true;

	m_fXOffset = 0;
	m_fYOffset = 0;
	m_bOrthoInit = false;

	m_fMass = 0.03f;
	m_fFriction = .85f;
}

Camera::~Camera()
{
}

void Camera::Init(const Vector3& target, const Vector3& up)
{
	this->m_vTarget = target;
	this->m_vUp = up;
}

void Camera::Reset()
{
	m_vTarget.Set(0, 0, 0);
	m_vUp.Set(0, 1, 0);
}
bool Camera::IsOrthoInit()
{
	return m_bOrthoInit;
}
void Camera::InitOrtho(Vector3 v)
{
	m_fOrthoSize = v;
	m_bOrthoInit = true;
}
void Camera::Update(double dt)
{
}
void Camera::UpdateView(double dt, Vector3 vPos, bool mouseEnabled)
{
	if (mouseEnabled)
	{
		// f = ma
		if (m_fXOffset < 0)
		{
			if (m_fXOffset > -m_fMinCamForce)
				m_fXOffset = -m_fMinCamForce;
		}
		if (m_fXOffset > 0)
		{
			if (m_fXOffset < -m_fMinCamForce)
				m_fXOffset = m_fMinCamForce;
		}
		if (m_fYOffset < 0)
		{
			if (m_fYOffset > -m_fMinCamForce)
				m_fYOffset = -m_fMinCamForce;
		}
		if (m_fYOffset > 0)
		{
			if (m_fYOffset < -m_fMinCamForce)
				m_fYOffset = m_fMinCamForce;
		}
		float fXAccel = m_fXOffset / m_fMass;
		float fYAccel = m_fYOffset / m_fMass;
		//fXAccel += m_fFriction * -m_fCamSpeed.x;
		//fYAccel += m_fFriction * -m_fCamSpeed.y;

		m_fCamSpeed.x += fXAccel * (float) dt;
		m_fCamSpeed.x = Math::Clamp(m_fCamSpeed.x, -m_fMaxCamSpeed, m_fMaxCamSpeed);
		

		m_fCamSpeed.y += fYAccel * (float) dt;
		m_fCamSpeed.y = Math::Clamp(m_fCamSpeed.y, -m_fMaxCamSpeed, m_fMaxCamSpeed);

		//m_fXOffset *= this->m_fCamSpeed * (float)dt;
		//m_fYOffset *= this->m_fCamSpeed * (float)dt;

		m_fYaw += m_fCamSpeed.x * (float)dt;
		m_fPitch += m_fCamSpeed.y * (float)dt;
		m_fCamSpeed.x *= m_fFriction;
		m_fCamSpeed.y *= m_fFriction;
		m_fXOffset = 0;
		m_fYOffset = 0;
	}
	if (m_fPitch > 89.0f)
		m_fPitch = 89.0f;
	if (m_fPitch < -89.0f)
		m_fPitch = -89.0f;

	m_vDir.x = cos(Math::DegreeToRadian(m_fPitch)) * cos(Math::DegreeToRadian(m_fYaw));
	m_vDir.y = sin(Math::DegreeToRadian(m_fPitch));
	m_vDir.z = cos(Math::DegreeToRadian(m_fPitch)) * sin(Math::DegreeToRadian(m_fYaw));

	m_vTarget = vPos + m_vDir;
}
void Camera::UpdateYawPitchMouse(float xpos, float ypos)
{
	if (m_bIsFirstMouseMove)
	{
		m_fLastX = xpos;
		m_fLastY = ypos;
		m_bIsFirstMouseMove = false;
	}

	m_fXOffset = xpos - m_fLastX;
	m_fYOffset = m_fLastY - ypos;

	m_fLastX = xpos;
	m_fLastY = ypos;
}
// Getters
Vector3 Camera::GetTarget()
{
	return m_vTarget;
}
Vector3 Camera::GetUp()
{
	return m_vUp;
}
Vector3 Camera::GetDir()
{
	return m_vDir;
}
void Camera::SetDir(float yaw, float pitch)
{
	m_fYaw = yaw;
	m_fPitch = pitch;
}
Vector3 Camera::GetOrthoSize()
{
	return m_fOrthoSize;
}
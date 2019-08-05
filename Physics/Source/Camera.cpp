#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

Camera::Camera()
{
	Reset();
	m_fCamSpeed = 45.0f;
	m_fPitch = 0;
	m_fYaw = 270;
	m_bIsFirstMouseMove = true;

	m_fXOffset = 0;
	m_fYOffset = 0;
	m_fYawTorque = 0;
	m_fPitchTorque = 0;
	m_fRollTorque = 0;
	m_fRoll = 0;
	m_bOrthoInit = false;
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
	m_fPitch += m_fPitchTorque * dt;
	m_fYaw += m_fYawTorque * dt;
	m_fRoll += m_fRollTorque * dt;
	m_fPitchTorque *= 0.8;
	m_fYawTorque *= 0.8;
	m_fRollTorque *= 0.8;
	m_fRollTorque -= m_fRoll * 0.4;
}
void Camera::UpdateView(double dt, Vector3 vPos, bool mouseEnabled)
{
	if (mouseEnabled)
	{
		m_fXOffset *= this->m_fCamSpeed * (float)dt;
		m_fYOffset *= this->m_fCamSpeed * (float)dt;

		m_fYawTorque += m_fXOffset;
		m_fPitchTorque += m_fYOffset;
	}
	if (m_fPitch > 89.0f)
		m_fPitch = 89.0f;
	if (m_fPitch < -89.0f)
		m_fPitch = -89.0f;

	m_vDir.x = cos(Math::DegreeToRadian(m_fPitch)) * cos(Math::DegreeToRadian(m_fYaw));
	m_vDir.y = sin(Math::DegreeToRadian(m_fPitch));
	m_vDir.z = cos(Math::DegreeToRadian(m_fPitch)) * sin(Math::DegreeToRadian(m_fYaw));

	m_vTarget = vPos + m_vDir;

	m_vUp.Set(0, 1, 0);
	Mtx44 rotation;
	rotation.SetToRotation(m_fRoll, m_vDir.x, m_vDir.y, m_vDir.z);
	m_vUp = rotation * m_vUp;
}
void Camera::UpdateYawPitchMouse(float xpos, float ypos)
{
	if (m_bIsFirstMouseMove)
	{
		m_fLastX = xpos;
		m_fLastY = ypos;
		m_bIsFirstMouseMove = false;
	}

	m_fXOffset = xpos;
	m_fYOffset = - ypos;

	m_fLastX = xpos;
	m_fLastY = ypos;
}
void Camera::SetCamSpeed(float speed)
{
	m_fCamSpeed = speed;
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

float Camera::GetYaw()
{
	return m_fYaw;
}
float Camera::GetPitch()
{
	return m_fPitch;
}

void Camera::AddTorque(float yaw, float pitch)
{
	m_fPitchTorque += pitch;
	m_fYawTorque += yaw;
}

void Camera::AddTorque(float yaw, float pitch, float roll)
{
	m_fPitchTorque += pitch;
	m_fYawTorque += yaw;
	m_fRollTorque += roll;
}
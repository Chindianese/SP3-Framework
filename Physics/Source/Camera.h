#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera
{
	friend class CameraComponent;
	friend class RenderingManager;
private:
	Vector3 m_vTarget;
	Vector3 m_vDir;
	Vector3 m_vUp;

	float m_fLastX;
	float m_fLastY;
	bool m_bIsFirstMouseMove;
	Vector3 m_fCamSpeed;
	float m_fMaxCamSpeed;
	float m_fMinCamForce;

	float m_fPitch;
	float m_fYaw;

	float m_fXOffset;
	float m_fYOffset;

	Vector3 m_fOrthoSize;
	bool m_bOrthoInit;

	float m_fMass;
	float m_fFriction;

	void UpdateView(double dt, Vector3 vPos, bool mouseEnabled);
public:

	Camera();
	~Camera();
	virtual void Init(const Vector3& target, const Vector3& up);
	void InitOrtho(Vector3);
	virtual void Reset();
	virtual void Update(double dt);
	void UpdateYawPitchMouse(float xpos, float ypos);
	bool IsOrthoInit();
	Vector3 GetOrthoSize();
	// Getters
	Vector3 GetTarget();
	Vector3 GetUp();
	Vector3 GetDir();
	void SetDir(float yaw, float pitch);
};

#endif
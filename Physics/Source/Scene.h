#pragma once
#include "GameObjectManager.h"

// Components================================================================================
#include "ComponentMacros.h"
// Camera--------------------------------------------------------------------------------
#include "Camera.h"
#include "CameraComponent.h"
#include "LightManager.h"
#include "TransformComponent.h"
#include "Rigidbody.h"
#include "Constrain.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;
	GameObject* GetCameraGameObject();
	Camera* GetCamera();
	GameObjectManager* GetGameObjectManager();
	LightManager* GetLightManager();
	void SetCursorEnabled(bool);
protected:
	GameObjectManager m_GOM;
	LightManager m_LightManager;
	GameObject* m_CameraGO;
	Camera* m_Camera;
};

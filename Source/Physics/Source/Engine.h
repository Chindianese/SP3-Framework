#pragma once
#include "Renderer.h"
#include "RenderingManager.h"
#include "LightManager.h"
#include "SceneManager.h"

#include "Scene.h"

#include "Logger.h"
#include "Locator.h"
#include "Preferences.h"

#include "CollisionManager.h"
#include "RenderingManagerBase.h"
#include <vector>
#include "ClientSystem.h"

//#define LOG_UPDATE_RATE 1

class Engine
{
	friend class Application;
	friend class Singleton<Engine>;
public:
	void SetMouseCallback(GLFWwindow* window);
private:
	Engine();
	~Engine();
	float m_fLogUpdateTimer;
	void Init();
	void Update(double dt);
	void Exit();
	static RenderingManager* m_Renderer;
	CollisionManager m_CollisionManager;
	void CheckGOForObserver(GameObject* go, std::vector<GameObject*>* GOList);
	unsigned int m_frameCount;
	ClientSystem m_clientSystem;
public:
	RenderingManagerBase* GetRenderManager();
};

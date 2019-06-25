#pragma once
#include "Renderer.h"
#include "RenderingManager.h"
#include "SceneManager.h"

#include "Scene.h"
#include "TestScene.h"

#include "Logger.h"
#include "Locator.h"
#include "WindowData.h"

#define LOG_UPDATE_RATE 1

class Engine
{
	friend class Application;
private:
	Engine();
	~Engine();

	float m_fLogUpdateTimer;
	void Init();
	void Update(double dt);
	void Exit();
	static Renderer* m_Renderer;
public:
};

#include "Scene.h"
#include "Application.h"
Scene::Scene()
{
	m_bCursorEnabled = false;
	m_Player = nullptr;
	m_CameraGO = nullptr;
}

Scene::~Scene()
{
}
GameObject* Scene::GetCameraGameObject()
{
	return m_CameraGO;
}
Camera* Scene::GetCamera()
{
	return m_Camera;
}
GameObjectManager* Scene::GetGameObjectManager()
{
	return &m_GOM;
}
LightManager* Scene::GetLightManager()
{
	return &m_LightManager;
}
void Scene::SetCursorEnabled(bool b)
{
	Application::SetCursorEnabled(b);
	m_bCursorEnabled = b;
}
GameObject* Scene::GetGO(std::string s)
{
	return DataContainer::GetInstance()->GetGameObject(s);
}
GameObject* Scene::AddGO(std::string layer)
{
	return m_GOM.AddGameObject(layer);
}
Mesh* Scene::GetMesh(std::string s)
{
	return DataContainer::GetInstance()->GetMesh(s);
}
GameObject* Scene::GetPlayer()
{
	return m_Player;
}
bool Scene::GetCursorEnabled()
{
	return m_bCursorEnabled;
}
#include "DataContainer.h"
#include <time.h>
// Components================================================================================
#include "MeshController.h"
#include "Rigidbody.h"
#include "UIButtonComponent.h"
// Scripts--------------------------------------------------------------------------------
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "FPSScript.h"
DataContainer::DataContainer()
{
	m_bInitialsed = false;
}
void DataContainer::Init()
{
	clock_t begin = clock();
	if (m_bInitialsed)
	{
		DEFAULT_LOG("Attempted re-init of datacontainer");
		return;
	}
	m_bInitialsed = true;

	InitTextures();
	InitMeshes();
	InitTerrain();
	InitParticles();
	InitGO();
	InitShaders();
	m_bInitialsed = true;

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	// CHENG_LOG("Time to load container: ", std::to_string(elapsed_secs));
}

void DataContainer::InitTextures()
{
	m_map_Textures["Text"] = LoadTGA("monoid");
	m_map_Textures["T7Seg"] = LoadTGA("7seg");
	m_map_Textures["Sky"] = LoadTGA("sky");
	m_map_Textures["Cube"] = LoadTGA("Cube");
	m_map_Textures["Dirt"] = LoadTGA("dirt");
	m_map_Textures["Ball"] = LoadTGA("Ball");
}
void DataContainer::InitMeshes()
{
	/// Meshes================================================================================
	/// DO NOT REMOVE--------------------------------------------------------------------------------
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16)->AddTexture("Text");
	m_map_Meshes["T7Seg"] = MeshBuilder::GenerateText("text", 16, 16)->AddTexture("T7Seg");
	//--------------------------------------------------------------------------------
	m_map_Meshes["SkyPlane"] = MeshBuilder::GenerateSkyPlane("SkyPlane", { 0,0,1 }, 24, 6, 400, 6, 6)->AddTexture("Sky");

	m_map_Meshes["Axis"] = MeshBuilder::GenerateAxes("Axes", 1000, 1000, 1000);

	m_map_Meshes["Cube"] = MeshBuilder::GenerateOBJ("Cube")->AddTexture("Cube");

	m_map_Meshes["Ball"] = MeshBuilder::GenerateOBJ("Ball");

	m_map_Meshes["Quad"] = MeshBuilder::GenerateQuadLeftCentered({}, 1);

	m_map_Meshes["QuadCentered"] = MeshBuilder::GenerateQuad("QuadCentered", {}, 1);
}
void DataContainer::InitTerrain()
{
}
void DataContainer::InitParticles()
{
}
void DataContainer::InitGO()
{
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	go = new GameObject;
	m_map_GO["fps"] = go;
	go->AddComponent(new RenderComponent(GetMesh("Text"), "0"));
	go->AddComponent(new FPSScript);

	go = AddGO("message");
	go->AddComponent(new RenderComponent(GetMesh("Text"), "", true));
}
void  DataContainer::InitShaders()
{
	m_map_Shaders["Default"] = LoadShaders("Default", "FancyFog");
	m_map_Shaders["Particles"] = LoadShaders("Default", "FancyFog");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");
	m_map_Shaders["UI"] = LoadShaders("Default", "Default");
}
GameObject* DataContainer::AddGO(std::string name)
{
	// TODO: check to existing key
	GameObject* go = new GameObject;
	m_map_GO[name] = go;
	return go;
}
DataContainer::~DataContainer()
{
	std::map<std::string, Mesh*>::iterator it;
	for (it = m_map_Meshes.begin(); it != m_map_Meshes.end(); it++)
	{
		// it->first == key
		// it->second == value
		delete it->second;
	}
	m_map_Meshes.clear();
	std::map<std::string, AnimatedMesh*>::iterator it2;
	for (it2 = m_map_Animated.begin(); it2 != m_map_Animated.end(); it2++)
	{
		// it->first == key
		// it->second == value
		delete it2->second;
	}
	m_map_Animated.clear();
	std::map<std::string, GameObject*>::iterator it3;
	for (it3 = m_map_GO.begin(); it3 != m_map_GO.end(); it3++)
	{
		// it->first == key
		// it->second == value
		delete it3->second;
	}
	m_map_GO.clear();
	for (it3 = m_map_GO.begin(); it3 != m_map_GO.end(); it3++)
	{
		// it->first == key
		// it->second == value
		delete it3->second;
	}
}
Mesh* DataContainer::GetMesh(std::string name)
{
	Mesh* mesh = m_map_Meshes[name];
	if (!mesh)
		DEFAULT_LOG("ERROR: Mesh not found of name: " + name);
	return mesh;
}

AnimatedMesh* DataContainer::GetAnimation(std::string name)
{
	AnimatedMesh* mesh = m_map_Animated[name];
	if (!mesh)
		DEFAULT_LOG("ERROR: Animation not found of name: " + name);
	return new AnimatedMesh(*mesh);
}
GameObject* DataContainer::GetGameObject(std::string name)
{
	GameObject* go = m_map_GO[name];
	if (!go)
	{
		DEFAULT_LOG("ERROR: GameObject not found of name: " + name);
		return nullptr;
	}
	return go->Clone();
}
GameObject* DataContainer::GetGameObjectRaw(std::string name)
{
	GameObject* go = m_map_GO[name];
	if (!go)
	{
		DEFAULT_LOG("ERROR: GameObject not found of name: " + name);
		return nullptr;
	}
	return go;
}
unsigned DataContainer::GetShader(std::string key)
{
	if (m_map_Shaders.count(key) <= 0)
		DEFAULT_LOG("ERROR: Shader not found of name: " + key);
	unsigned shader = m_map_Shaders[key];
	return shader;
}

unsigned DataContainer::GetTexture(std::string key)
{
	if (m_map_Textures.count(key) <= 0)
		DEFAULT_LOG("ERROR: Texture not found of name: " + key);
	unsigned tex = m_map_Textures[key];
	return tex;
}
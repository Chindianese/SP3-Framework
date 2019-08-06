#include "DataContainer.h"
#include "ChengRigidbody.h"
#include "BallScript.h"
#include "BulletScript.h"
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "RainScript.h"
#include "GoalScript.h"
#include "BouncerScript.h"
#include "PaddleScript.h"
#include "HoleScript.h"
#include "MeshController.h"
#include "GauntletScript.h"
#include "FPSScript.h"
#include "GunScript.h"
#include "Constrain.h"
#include "EnemyAIScript.h"
#include <time.h>
DataContainer::DataContainer()
{
	clock_t begin = clock();
	/// Meshes================================================================================
	m_map_Meshes["Text"] = MeshBuilder::GenerateText("text", 16, 16);
	m_map_Meshes["Text"]->m_uTextureArray[0] = LoadTGA("calibri");

	m_map_Meshes["Cube"] = MeshBuilder::GenerateCube("wall", Color(1, 1, 1), 1.f);
	/// Shaders================================================================================
	m_map_Shaders["Default"] = LoadShaders("Flare", "Flare");
	m_map_Shaders["GPass"] = LoadShaders("GPass", "GPass");

	//================================================================================
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	CHENG_LOG("Time to load container: ", std::to_string(elapsed_secs));
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
	m_map_GO.clear();
	for (auto const& x : m_map_HeightMaps)
	{
		delete x.second;
	}
	m_map_HeightMaps.clear();
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
unsigned DataContainer::GetShader(std::string key)
{
	if (m_map_Shaders.count(key) <= 0)
		DEFAULT_LOG("ERROR: Shader not found of name: " + key);
	unsigned shader = m_map_Shaders[key];
	return shader;
}
HeightMapData* DataContainer::GetHeightMap(std::string key)
{
	if (m_map_HeightMaps.count(key) <= 0)
		DEFAULT_LOG("ERROR: Heightmap not found of name: " + key);
	return m_map_HeightMaps[key];
}
Mesh* DataContainer::GenerateTerrain(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrain(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale, vPos);
	return mesh;
}
Mesh* DataContainer::GenerateTerrainTerrace(std::string key, std::string path, Vector3 vScale, Vector3 vPos)
{
	_heightmap* heightMap = new _heightmap;
	Mesh* mesh = MeshBuilder::GenerateTerrainTerrace(key, path, *heightMap, vScale);
	m_map_HeightMaps[key] = new HeightMapData(mesh, heightMap, vScale, vPos);
	return mesh;
}
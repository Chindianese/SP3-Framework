#pragma once

#include "Mesh.h"
#include "MeshBuilder.h"
#include "Singleton.h"
#include <map>
#include <string>
#include "LoadTGA.h"
#include "MeshBuilder.h"
#include "GameObject.h"
#include "ComponentMacros.h"
#include "HeightMapData.h"

#include "shader.hpp"

class DataContainer : public Singleton<DataContainer>
{
private:
	std::map<std::string, Mesh*> m_map_Meshes;
	std::map<std::string, AnimatedMesh*> m_map_Animated;
	std::map<std::string, GameObject*> m_map_GO;
	std::map<std::string, unsigned> m_map_Shaders;
	std::map<std::string, HeightMapData*> m_map_HeightMaps;

	Mesh* GenerateTerrain(std::string key, std::string path, Vector3 vScale, Vector3 vPos);
	Mesh* GenerateTerrainTerrace(std::string key, std::string path, Vector3 vScale, Vector3 vPos);

	bool m_bInitialsed;
	// Loading
	void InitMeshes();
	void InitTerrain();
	void InitGO();
	void InitShaders();
public:
	DataContainer();
	~DataContainer();

	std::vector<unsigned char> heightMap;
	void Init();
	Mesh* GetMesh(std::string name);
	AnimatedMesh* GetAnimation(std::string name);
	GameObject* GetGameObject(std::string name);
	unsigned GetShader(std::string key);
	HeightMapData* GetHeightMap(std::string key);
};

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
#include "shader.hpp"

class DataContainer : public Singleton<DataContainer>
{
private:
	std::map<std::string, Mesh*> m_map_Meshes;
	std::map<std::string, unsigned> m_map_Textures;
	std::map<std::string, AnimatedMesh*> m_map_Animated;
	std::map<std::string, GameObject*> m_map_GO;
	std::map<std::string, unsigned> m_map_Shaders;

	bool m_bInitialsed;
	// Loading
	void InitTextures();
	void InitMeshes();
	void InitTerrain();
	void InitParticles();
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
	GameObject* GetGameObjectRaw(std::string name);
	unsigned GetShader(std::string key);
	unsigned GetTexture(std::string key);
};

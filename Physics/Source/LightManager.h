#pragma once
#include "Light.h"
#include <vector>

#define SIZE m_vec_SceneLights.size()
#define MAX_NUMLIGHTS 8
#define MIN_NUMLIGHTS 1

class LightManager
{
private:
	//Default: 3 types of light in vector
	std::vector<Light*> m_vec_SceneLights;
	Light* m_currentLight;
	int m_iLightIndex;
	bool m_bLightChange;
public:
	LightManager();
	~LightManager();

	//Get a guranteed reference to scene lights
	std::vector<Light*>& GetSceneLights();
	Light* GetCurrentLight();

	int GetLightIndex();
	//bool GetLightChange();

	//void Update(float dt);

	//void AdjustLightPower(float dt, bool);
	//void CycleLight(bool);

	Light* AddLight(Light::LIGHT_TYPE type);
	void RemoveLight(Light* light);
};

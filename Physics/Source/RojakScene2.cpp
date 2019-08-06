#include "RojakScene2.h"
#include "AudioManager.h"
#include "GunScript.h"
#include "ChengPlayerScript.h"
#include "MeshController.h"
#include "Blackhole.h"
#include "GauntletScript.h"
#include "SunBrightnessScript.h"
#include "Constrain.h"
#include "Utility.h"
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "ChargeBarScript.h"
#include "WorldValues.h"
#include "AmmoDumpScript.h"
#include "ChengRigidbody.h"
#include "EnemyAIScript.h"
#include "LmaoPlayerScript.h"
RojakScene2::RojakScene2()
{
}

RojakScene2::~RojakScene2()
{
}
Vector3 RandColor(float min, float max)
{
	return Vector3(Math::RandFloatMinMax(min, max), Math::RandFloatMinMax(min, max), Math::RandFloatMinMax(min, max));
}
void RojakScene2::Init()
{
	WorldValues::GravityExponent.z = 0;
	WorldValues::DefaultGravityExponent.z = 0;
	WorldValues::GravityExponent.y = 1;
	WorldValues::DefaultGravityExponent.y = 1;
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObject* go;
	/// Create Camera================================================================================
	m_CameraGO = new GameObject;
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	m_GOM.AddGameObject(m_CameraGO);
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 300, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_ORTHO);
	m_CameraGO->CAMERA->SetMouseEnabled(false);
	m_Camera->SetDir(-90, -90);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 600;
	this->m_Camera->InitOrtho({ size, 0,10000 });
	/// UI================================================================================
	// Player--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject();
	go->AddComponent(new LmaoPlayerScript());
	/// WORLD===================================================================================
	float w = 400 / 16 * 9;
	int numWidth = 3;
	int numColors = numWidth * numWidth;
	float width = w / numWidth;
	float start = -(width / 2 * (numWidth - 1));
	float xoff = start;
	float zoff = start;
	for (int i = 0; i < numColors; ++i)
	{
		go = m_GOM.AddGameObject();
		go->TRANS->SetPosition({ xoff,0,zoff });
		go->TRANS->SetScale(w / numWidth, 1, w / numWidth);
		go->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
		go->RENDER->SetColor(RandColor(0.2f, 1.f));
		// go->RENDER->SetLightEnabled(false);

		xoff += width;
		if ((i + 1) % numWidth == 0)
		{
			xoff = start;
			zoff += width;
		}
	}
}
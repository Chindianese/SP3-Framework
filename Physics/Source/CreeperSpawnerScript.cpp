#include "CreeperSpawnerScript.h"
#include "PlayerScript.h"
#include "Constrain.h"
#include "Scene.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "PhysicsScript.h"
#include "Collider.h"
#include "EnemyScript.h"

CreeperSpawnerScript::CreeperSpawnerScript()
{
	timeout = 0;
}

CreeperSpawnerScript::~CreeperSpawnerScript()
{
}

void CreeperSpawnerScript::Update(double dt)
{
	timeout -= dt;
	if (timeout < 0)
	{
		SceneManager* sm = SceneManager::GetInstance();
		Scene* scene = sm->GetScene();
		GameObjectManager* gom = scene->GetGameObjectManager();
		GameObject* Creeper = gom->AddGameObject();
		Creeper->TRANS->SetPosition(Math::RandFloatMinMax(-60, 60), 50, Math::RandFloatMinMax(-60, 60));
		Creeper->TRANS->SetScale(3, 6, 3);
		Creeper->AddComponent(new RenderComponent(DataContainer::GetInstance()->GetMesh("Creeper")));
		Creeper->AddComponent(new PhysicsScript());
		Creeper->AddComponent(new Constrain(DataContainer::GetInstance()->GetHeightMap("Terrain"), Constrain::LIMIT, -10.f));
		Creeper->AddComponent(new Collider(Vector3(5, 24, 1)));
		Creeper->AddComponent(new EnemyScript(9.8f));
		Creeper->RENDER->SetLightEnabled(false);
		Creeper->RENDER->SetBillboard(true);
		Creeper->SetActive(true);
		timeout = 5;
	}
}

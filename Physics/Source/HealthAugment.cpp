#include "..\HealthAugment.h"



HealthAugment::HealthAugment()
{
}


HealthAugment::~HealthAugment()
{
}

void HealthAugment::ActiveEffect(Component* proj, GameObject* go)
{
	//Bullet expands
	proj->TRANS->SetScale(1.5);
}

void HealthAugment::PassiveEffect(GameObject* go)
{

}
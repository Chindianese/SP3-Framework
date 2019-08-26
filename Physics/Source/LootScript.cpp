#include "LootScript.h"
#include "DataContainer.h"
#include "Rigidbody.h"
#include "ChunkCollider.h"
#include "SceneManager.h"
#include "ExplodeAugment.h"
#include "ReloadingAugment.h"
#include "BlackHoleAugment.h"
#include "ParticleSpawnerScript.h"

LootScript::LootScript()
{
	m_LootDrop = DataContainer::GetInstance()->GetGameObject("Loot");
}


LootScript::~LootScript()
{
}

void LootScript::Collide(GameObject * go)
{
	if (go->GetComponent<ChunkCollider>(true) != nullptr)
		return;

	//Vector3 chunkspacepos = TRANS->GetPosition() - go->TRANS->GetPosition();
	DropLoot();
	//DestroySelf();
	SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->QueueDestroyFromComponent(this);
	
}

WeaponPartScript* LootScript::GenerateWeaponPart(void)
{
	WeaponPartScript::SLOT_TYPE SlotType = static_cast<WeaponPartScript::SLOT_TYPE>(Math::RandIntMinMax(1, WeaponPartScript::SLOT_TYPE::MUZZLE));
	float Durability = Math::RandFloatMinMax(4.f, 6.f);
	float Multiplier;

	if (SlotType == WeaponPartScript::SLOT_TYPE::MUZZLE || SlotType == WeaponPartScript::SLOT_TYPE::SCOPE ||
		SlotType == WeaponPartScript::SLOT_TYPE::GRIP)
	{
		Multiplier = Math::RandFloatMinMax(0.5f, 0.65f);
		
		if (SlotType == WeaponPartScript::SLOT_TYPE::MUZZLE)
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Muzzle"));
		}
		else if(SlotType == WeaponPartScript::SLOT_TYPE::SCOPE)
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Scope"));
		}
		else
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Grip"));
		}
	}
	else if (SlotType == WeaponPartScript::SLOT_TYPE::CLIP)
	{
		Multiplier = 2;
		m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Clip"));

	}

	return new WeaponPartScript(SlotType, Multiplier, Durability);

}

void LootScript::GenerateAugment(GameObject* ptr)
{
	if (!ptr->PART)
		return;

	int GenerateAugmentChance = Math::RandIntMinMax(1, 10);

	if (GenerateAugmentChance > 7)
	{
		GenerateAugmentChance = Math::RandIntMinMax(1, 3);
		//if (GenerateAugmentChance == 1)
		//	ptr->PART->SetAugment(new ExplodeAugment);
		//else if (GenerateAugmentChance == 2)
			ptr->PART->SetAugment(new ReloadingAugment);
	/*	else if (GenerateAugmentChance == 3)
			ptr->PART->SetAugment(new BlackHoleAugment);*/
		ptr->AddComponent(new ParticleSpawnerScript(DataContainer::GetInstance()->GetGameObject("particleRareDrop"),
			5, { 0.1f,0.1f,0.1f }, 0.1f));
	}
}

void LootScript::DropLoot(void)
{

	//70% chance to drop loot
	int DropChance = Math::RandIntMinMax(0, 100);
	RYAN_LOG(std::to_string(DropChance));

	if (DropChance >= 30)
	{
		DropChance = Math::RandIntMinMax(0, 100);
		//30% chance to drop a part
		//70% chacne to drop other loot

		RYAN_LOG(std::to_string(DropChance));
		if (DropChance >= 30)
		{
			//Generate the part
			WeaponPartScript* NewWeaponPartScript = nullptr;
			NewWeaponPartScript = GenerateWeaponPart();

			GameObject* Loot = Instantiate(m_LootDrop, this->GetPosition());

			Loot->AddComponent(NewWeaponPartScript);
			Loot->RENDER->SetActive(true);
			Loot->RIGID->SetAffectedByGravity(true);

			GenerateAugment(m_LootDrop);
		}
		else
		{

		}
	}
}
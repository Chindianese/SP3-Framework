#include "BulletCollisionResponse.h"
#include "PlayerScript.h"
#include "PhysicsScript.h"
#include "EnemyScript.h"

BulletCollisionResponse::BulletCollisionResponse()
{
}

BulletCollisionResponse::~BulletCollisionResponse()
{
}

void BulletCollisionResponse::Update(double dt)
{
}

void BulletCollisionResponse::CollisionResponse(Collider* c)
{
	if (c->GetComponent<PlayerScript>() != nullptr) return;
	if (c->GetComponent<PhysicsScript>() != nullptr)
		c->GetComponent<PhysicsScript>()->SetVelocity(GetComponent<PhysicsScript>()->GetVelocity() * 0.3);
	if (c->GetComponent<EnemyScript>() != nullptr)
		c->GetComponent<EnemyScript>()->HealthModify(-2.5f);
	this->GetParent()->SetActive(false);
}

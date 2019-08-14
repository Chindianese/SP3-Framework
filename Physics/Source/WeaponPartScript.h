#pragma once
#include "PartScript.h"
class WeaponPartScript : public PartScript
{
public:
	WeaponPartScript(SLOT_TYPE slot, double Multiplier, float durability, bool isAttached = false);
	virtual ~WeaponPartScript();


	virtual WeaponPartScript* Clone() { return new WeaponPartScript(*this); }
	void Effect() override;

};

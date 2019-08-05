#pragma once
#include "ComponentBase.h"
#include "ComponentMacros.h"
#include "HeightMapData.h"
class Constrain :
	public ComponentBase
{
public:
	enum eConstrainTypes
	{
		FIXED,		// lock x height to height map
		LIMIT,		// set lowest y val to height map
	};
private:
	HeightMapData* m_Data;
	eConstrainTypes m_ConstrainType;
	float m_fDistance;
public:
	Constrain(HeightMapData*, eConstrainTypes type, float distance);
	virtual ~Constrain();
	virtual ComponentBase* Clone() { return new Constrain(*this); };
	virtual void Update(double dt) override;
	bool IsOnGround();
};

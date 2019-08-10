#pragma once
#include <vector>
#include "Locator.h"
#include <string>

class GameObject;

class ComponentBase
{
private:
	bool m_bStarted;
	bool m_bActive;
protected:
	std::vector<ComponentBase*>* m_vec_RefList = nullptr;
	GameObject* m_parent = nullptr;
public:
	ComponentBase();
	virtual ~ComponentBase();
	ComponentBase(ComponentBase& com);

	void Init(std::vector<ComponentBase*>* refList);
	void SetParent(GameObject* g);
	virtual void Update(double dt);

	template <class t>
	t* GetComponent(bool bOptional = false)
	{
		for (unsigned i = 0; i < (*m_vec_RefList).size(); ++i)
		{
			t* out = dynamic_cast<t*>((*m_vec_RefList)[i]);
			if (out)
				return out;
		}
		std::string sTypeName = typeid(t).name();
		if (!bOptional)
			DEFAULT_LOG("Component of type " + sTypeName + " not found");
		return nullptr;
	};
	virtual ComponentBase* Clone() = 0;

	virtual void CheckStarted();
	virtual void Start();

	bool IsActive();
	virtual void SetActive(bool b);
	GameObject* GetParent();
	bool IsStarted();
	void SetStarted(bool);
};

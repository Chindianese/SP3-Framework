#include "LayerData.h"
LayerData::LayerData(unsigned Shader)
	:m_Shader(Shader)
{
	m_vec_GameObjects = new std::vector<GameObject*>;
}

LayerData::~LayerData()
{
	//for (auto p : *m_vec_GameObjects)
	//{
	//	delete p;
	//}
	for (unsigned i = 0; i < m_vec_GameObjects->size(); ++i)
	{
		delete m_vec_GameObjects->at(i);
	}
	//m_vec_GameObjects->clear();
	delete m_vec_GameObjects;
}
std::vector<GameObject*>* LayerData::GetGOList()
{
	return m_vec_GameObjects;
}
unsigned LayerData::GetShader()
{
	return m_Shader;
}
void LayerData::SetShader(unsigned u)
{
	this->m_Shader = u;
}
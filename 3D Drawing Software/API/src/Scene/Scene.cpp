#include "Scene.h"

dra::Scene::Scene()
{
}

dra::Scene::~Scene()
{
}

void dra::Scene::InsertUpdateFunction(std::function<void()> t)
{
	m_Updates.push_back(t);
}

void dra::Scene::InsertRenderFunction(std::function<void(Camera*)> t)
{
	m_Renders.push_back(t);
}

void dra::Scene::RunUpdates() const
{
	for (auto& func : m_Updates) {
		func();
	}
}

void dra::Scene::RunRenders(Camera* camera) const
{
	for (auto& func : m_Renders) {
		func(camera);
	}
}

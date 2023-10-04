#include "Scene.h"
#include "../Core/CoreGL.h"
namespace dra {
	Scene::Scene() : m_Camera(60, 960.0f, 540.0f), m_Line(&m_Camera) {
		ShaderArena::Instance().LoadShader("LineShader", "shaders/line.shader");
	}
	Scene::~Scene()
	{
	}
	void Scene::Render()
	{
		

		m_Line.Draw();
		
	}
}
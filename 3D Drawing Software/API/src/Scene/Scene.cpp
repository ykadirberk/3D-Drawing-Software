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
		GLCall(glClearColor(0.0f, 0.0f, 0.15f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_Line.Draw();
		
	}
}
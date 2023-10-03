#include "Scene.h"
#include "../Core/CoreGL.h"
namespace dra {
	Scene::Scene() : m_Line(), m_Camera(60, 960.0f, 540.0f) {
		ShaderArena::Instance().LoadShader("LineShader", "shaders/line.shader");
		float positions[] = {
			-0.50f, 0.0f, 0.0f,
			 0.50f, 0.0f, 0.0f,
		};
		 
		unsigned int indices[] = {
			0, 1
		};

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 3 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 2);

		m_Line.GetTransform().SetPosition(0.0f, 0.0f, -5.0f);
	}
	Scene::~Scene()
	{
	}
	void Scene::Render()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.15f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		auto t = ShaderArena::Instance().GetShader("LineShader");
		if (t.has_value()) {
			auto& shader = t.value();
			m_Color_r += m_Change_r;
			if (m_Color_r >= 1.0 || m_Color_r <= 0.0) {
				m_Change_r *= -1;
			}
			shader->Bind();
			shader->SetUniform4f("u_Color", m_Color_r, 0.3f, 0.8f, 1.0f);
			m_Line.GetTransform().SetPosition(0.0f, 0.0f, -5.0f);
			m_Line.GetTransform().SetRotation(0.0f, 180.0f * m_Color_r, 360.0f * m_Color_r);

			shader->SetUniformMat4f("u_MVP", m_Camera.GetPxV() * m_Line.GetTransform().GetAsMat4f());
			m_VAO->Bind();
			m_IndexBuffer->Bind();

			GLCall(glDrawElements(GL_LINES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
			//m_Line.Draw();
		}
		
	}
}
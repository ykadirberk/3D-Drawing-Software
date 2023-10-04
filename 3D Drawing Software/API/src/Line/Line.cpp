#include "Line.h"
#include <iostream>


namespace dra {
	Line::Line(Camera* camera)
		:	m_Camera(camera),
			m_Positions({
				-0.50f, 0.0f, 0.0f,
				 0.50f, 0.0f, 0.0f
			}),
			m_Indices({ 0, 1 }),
			m_Transform()
	{
		auto t = ShaderArena::Instance().GetShader("LineShader");
		if (!t.has_value()) {
			ShaderArena::Instance().LoadShader("LineShader", "shaders/line.shader");
		}

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(m_Positions.data(), m_Positions.size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size());
		m_Transform.SetPosition(0.0f, 0.0f, -3.0f);
		std::cout << "Line is created." << std::endl;
	}

	Line::~Line() {
		std::cout << "Line is destroyed." << std::endl;
	}

	[[nodiscard]] Transform& Line::GetTransform() {
		return m_Transform;
	}

	void Line::Update()
	{
		m_Transform.Rotate(0.0f, 0.0f, 1.0f);
	}

	void Line::Draw() {

		auto t = ShaderArena::Instance().GetShader("LineShader");
		if (t.has_value()) {
			auto& shader = t.value();
			shader->Bind();
			shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

			shader->SetUniformMat4f("u_MVP", m_Camera->GetProjection() * m_Camera->GetView() * m_Transform.GetAsMat4f());
			m_VAO->Bind();
			m_IndexBuffer->Bind();

			GLCall(glDrawElements(GL_LINES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
		}
	}
}
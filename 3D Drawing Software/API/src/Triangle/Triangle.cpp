#include "Triangle.h"
#include <iostream>

namespace dra {
	Triangle::Triangle( Object* parent)
		: m_Positions({
			-0.50f, -0.50f, 0.0f,
			 0.50f, -0.50f, 0.0f,
			 0.0f,  0.50f, 0.0f
			}),
		m_Indices({ 0, 1, 2 }), Shape(parent)
	{
		m_Transform = Transform(this);

		auto t = ShaderArena::Instance().GetShader("TriangleShader");
		if (!t.has_value()) {
			ShaderArena::Instance().LoadShader("TriangleShader", "shaders/triangle.shader");
		}

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(m_Positions.data(), m_Positions.size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size());
		std::cout << "Triangle is created." << std::endl;
	}

	Triangle::~Triangle() {
		std::cout << "Triangle is destroyed." << std::endl;
	}

	void Triangle::Update()
	{
		// TODO: Implement update logic if needed
	}

	void Triangle::Draw(Camera* camera) {
		if (auto t = ShaderArena::Instance().GetShader("TriangleShader"); t.has_value()) {
			auto& shader = t.value();
			shader->Bind();
			shader->SetUniform4f("u_Color", 0.2f, 0.8f, 0.4f, 1.0f);

			shader->SetUniformMat4f("u_MVP", camera->GetProjection() * camera->GetView() * m_Transform.GetWorldAsMat4f());
			m_VAO->Bind();
			m_IndexBuffer->Bind();

			GLCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
		}
	}
}
#include "Line.h"
#include <iostream>
#include <numbers>

namespace dra {
	Line::Line() : Shape() {
		if (!Defaults::s_IsSet) {
			
			Defaults::s_Positions = { -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f };
			float r = 0.01f;

			Vector<float> rotvec(-0.5f, 0.00f, 0.00f);

			for (int i = 0; i < 12; i++) {
				Defaults::s_Positions.push_back(rotvec.x());
				Defaults::s_Positions.push_back(rotvec.y() + r * std::sin(std::numbers::pi / 6 * i));
				Defaults::s_Positions.push_back(rotvec.z() + r * std::cos(std::numbers::pi / 6 * i));

				Defaults::s_Indices.push_back(0);
				Defaults::s_Indices.push_back(2 + i);
				Defaults::s_Indices.push_back(2 + (i + 1) % 12);
			}

			rotvec = Vector<float>(0.5f, 0.00f, 0.0f);

			for (int i = 0; i < 12; i++) {
				Defaults::s_Positions.push_back(rotvec.x());
				Defaults::s_Positions.push_back(rotvec.y() + r * std::sin(std::numbers::pi / 6 * i));
				Defaults::s_Positions.push_back(rotvec.z() + r * std::cos(std::numbers::pi / 6 * i));

				Defaults::s_Indices.push_back(1);
				Defaults::s_Indices.push_back(14 + (i + 1) % 12);
				Defaults::s_Indices.push_back(14 + i);
			}

			for (int i = 0; i < 12; i++) {
				Defaults::s_Indices.push_back(2 + (i + 1) % 12);
				Defaults::s_Indices.push_back(2 + i);
				Defaults::s_Indices.push_back(14 + i);

				Defaults::s_Indices.push_back(14 + i);
				Defaults::s_Indices.push_back(14 + (i + 1) % 12);
				Defaults::s_Indices.push_back(2 + (i + 1) % 12);
			}
			Defaults::s_IsSet = true;
		}
		
		m_Positions = Defaults::s_Positions;
		m_Indices = Defaults::s_Indices;

		m_Transform = Transform(this);

		auto t = ShaderArena::Instance().GetShader("LineShader");
		if (!t.has_value()) {
			ShaderArena::Instance().LoadShader("LineShader", "shaders/line.shader");
		}

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(Defaults::s_Positions.data(), Defaults::s_Positions.size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(Defaults::s_Indices.data(), Defaults::s_Indices.size());
		std::cout << "Line::" << ((uint64_t)this) << " is created." << std::endl;
	}

	Line::Line(Object* parent)
		: Shape(parent)
	{
		if (!Defaults::s_IsSet) {

			Defaults::s_Positions = { -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f };
			float r = 0.01f;

			Vector<float> rotvec(-0.5f, 0.00f, 0.00f);

			for (int i = 0; i < 12; i++) {
				Defaults::s_Positions.push_back(rotvec.x());
				Defaults::s_Positions.push_back(rotvec.y() + r * std::sin(std::numbers::pi / 6 * i));
				Defaults::s_Positions.push_back(rotvec.z() + r * std::cos(std::numbers::pi / 6 * i));

				Defaults::s_Indices.push_back(0);
				Defaults::s_Indices.push_back(2 + i);
				Defaults::s_Indices.push_back(2 + (i + 1) % 12);
			}

			rotvec = Vector<float>(0.5f, 0.00f, 0.0f);

			for (int i = 0; i < 12; i++) {
				Defaults::s_Positions.push_back(rotvec.x());
				Defaults::s_Positions.push_back(rotvec.y() + r * std::sin(std::numbers::pi / 6 * i));
				Defaults::s_Positions.push_back(rotvec.z() + r * std::cos(std::numbers::pi / 6 * i));

				Defaults::s_Indices.push_back(1);
				Defaults::s_Indices.push_back(14 + (i + 1) % 12);
				Defaults::s_Indices.push_back(14 + i);

			}

			for (int i = 0; i < 12; i++) {
				Defaults::s_Indices.push_back(2 + (i + 1) % 12);
				Defaults::s_Indices.push_back(2 + i);
				Defaults::s_Indices.push_back(14 + i);

				Defaults::s_Indices.push_back(14 + i);
				Defaults::s_Indices.push_back(14 + (i + 1) % 12);
				Defaults::s_Indices.push_back(2 + (i + 1) % 12);
			}
			Defaults::s_IsSet = true;
		}

		m_Positions = Defaults::s_Positions;
		m_Indices = Defaults::s_Indices;

		m_Transform = Transform(this);

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
		std::cout << "Line::" << ((uint64_t)this) << " is created." << std::endl;
	}

	Line::~Line() {
		std::cout << "Line::" << ((uint64_t)this) << " is destroyed." << std::endl;
	}

	void Line::Update()
	{
		// TODO
	}

	void Line::Draw(Camera* camera) {

		if (auto t = ShaderArena::Instance().GetShader("LineShader"); t.has_value()) {
			auto& shader = t.value();
			shader->Bind();
			shader->SetUniform4f("u_Color", 0.7f, 0.3f, 0.8f, 1.0f);
			
			shader->SetUniformMat4f("u_MVP", camera->GetProjection() * Matrix4<float>::Inverse(camera->GetView()) * m_Transform.GetWorldAsMat4f());
			//shader->SetUniformMat4f("u_MVP", m_Transform.GetWorldAsMat4f() * Matrix4<float>::Inverse(camera->GetView()) * camera->GetProjection());
			m_VAO->Bind();
			m_IndexBuffer->Bind();

			GLCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
		}
	}
}
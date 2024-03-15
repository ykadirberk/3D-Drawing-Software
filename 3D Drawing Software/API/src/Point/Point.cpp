#include "Point.h"
#include <numbers>

namespace dra {
	Point::Point() : Shape(nullptr)
	{
		if (!Defaults::s_IsSet) {

			float r = 0.02f;

			Defaults::s_Positions = { 
				0.0f,  r, 0.0f, 
				0.0f, -r, 0.0f
			};

			glm::vec3 rotvec(0.00f, 0.00f, 0.00f);

			for (int y = 1; y < 6; y++) {
				for (int xz = 0; xz < 12; xz++) {
					Defaults::s_Positions.push_back(r * std::sin(std::numbers::pi / 6 * y) * std::sin(std::numbers::pi / 6 * xz));
					Defaults::s_Positions.push_back(r * std::cos(std::numbers::pi / 6 * y));
					Defaults::s_Positions.push_back(r * std::sin(std::numbers::pi / 6 * y) * std::cos(std::numbers::pi / 6 * xz));
				}
			}

			auto offset = 2;

			for (int i = 0; i < 12; i++) {
				Defaults::s_Indices.push_back(0);
				Defaults::s_Indices.push_back(offset + i);
				Defaults::s_Indices.push_back(offset + (i + 1) % 12);
				
			}
			for (int k = 0; k < 4; k++) {
				offset += 12;
				for (int i = 0; i < 12; i++) {
					Defaults::s_Indices.push_back(offset - 12 + i);
					Defaults::s_Indices.push_back(offset + i);
					Defaults::s_Indices.push_back(offset + (i + 1) % 12);

					Defaults::s_Indices.push_back(offset + (i + 1) % 12);
					Defaults::s_Indices.push_back(offset - 12 + (i + 1) % 12);
					Defaults::s_Indices.push_back(offset - 12 + i);
				}
			}

			auto __size = Defaults::s_Positions.size() - 1;
			offset += 12;
			for (int i = 0; i < 12; i++) {
				Defaults::s_Indices.push_back(1);
				Defaults::s_Indices.push_back(offset - 12 + (i + 1) % 12);
				Defaults::s_Indices.push_back(offset - 12 + i);
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
		std::cout << "Point::" << ((uint64_t)this) << " is created." << std::endl;
	}
	Point::Point(Object* parent) : Shape(parent)
	{
		if (!Defaults::s_IsSet) {

			float r = 0.02f;

			Defaults::s_Positions = {
				0.0f,  r, 0.0f,
				0.0f, -r, 0.0f
			};

			glm::vec3 rotvec(0.00f, 0.00f, 0.00f);

			for (int y = 1; y < 6; y++) {
				for (int xz = 0; xz < 12; xz++) {
					Defaults::s_Positions.push_back(r * std::sin(std::numbers::pi / 6 * y) * std::sin(std::numbers::pi / 6 * xz));
					Defaults::s_Positions.push_back(r * std::cos(std::numbers::pi / 6 * y));
					Defaults::s_Positions.push_back(r * std::sin(std::numbers::pi / 6 * y) * std::cos(std::numbers::pi / 6 * xz));
				}
			}

			auto offset = 2;

			for (int i = 0; i < 12; i++) {
				Defaults::s_Indices.push_back(0);
				Defaults::s_Indices.push_back(offset + i);
				Defaults::s_Indices.push_back(offset + (i + 1) % 12);

			}
			for (int k = 0; k < 4; k++) {
				offset += 12;
				for (int i = 0; i < 12; i++) {
					Defaults::s_Indices.push_back(offset - 12 + i);
					Defaults::s_Indices.push_back(offset + i);
					Defaults::s_Indices.push_back(offset + (i + 1) % 12);

					Defaults::s_Indices.push_back(offset + (i + 1) % 12);
					Defaults::s_Indices.push_back(offset - 12 + (i + 1) % 12);
					Defaults::s_Indices.push_back(offset - 12 + i);
				}
			}

			auto __size = Defaults::s_Positions.size() - 1;
			offset += 12;
			for (int i = 0; i < 12; i++) {
				Defaults::s_Indices.push_back(1);
				Defaults::s_Indices.push_back(offset - 12 + (i + 1) % 12);
				Defaults::s_Indices.push_back(offset - 12 + i);
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
		std::cout << "Point::" << ((uint64_t)this) << " is created." << std::endl;
	}

	Point::~Point()
	{
		std::cout << "Point::" << ((uint64_t)this) << " is destroyed." << std::endl;
	}

	void Point::Update()
	{

	}

	void Point::Draw(Camera* camera)
	{
		if (auto t = ShaderArena::Instance().GetShader("LineShader"); t.has_value()) {
			auto& shader = t.value();
			shader->Bind();
			shader->SetUniform4f("u_Color", 1.0f, 0.1f, 0.5f, 1.0f);

			shader->SetUniformMat4f("u_MVP", camera->GetProjection() * glm::inverse(camera->GetView()) * m_Transform.GetWorldAsMat4f());
			m_VAO->Bind();
			m_IndexBuffer->Bind();

			GLCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
		}

	}
}


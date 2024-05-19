#include "Sphere.h"
#include <numbers>

namespace dra {
	Sphere::Sphere(int precision) : Shape(nullptr)
	{
		ConstructDefaults(precision);
	}
	Sphere::Sphere(Object* parent, int precision) : Shape(parent)
	{
		ConstructDefaults(precision);
	}

	Sphere::~Sphere()
	{
		std::cout << "Sphere::" << ((uint64_t)this) << " is destroyed." << std::endl;
	}

	void Sphere::Update()
	{

	}

	void Sphere::Draw(Camera* camera)
	{
		if (auto t = ShaderArena::Instance().GetShader("LineShader"); t.has_value()) {
			auto& shader = t.value();
			shader->Bind();
			shader->SetUniform4f("u_Color", 0.9f, 0.70f, 0.30f, 1.0f);

			shader->SetUniformMat4f("u_MVP", camera->GetProjection() * glm::inverse(camera->GetView()) * m_Transform.GetWorldAsMat4f());
			m_VAO->Bind();
			m_IndexBuffer->Bind();

			GLCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
		}

	}
	void Sphere::ConstructDefaults(int precision)
	{
		if (!Defaults::s_IsSet) {

			float r = 1.0f;

			Defaults::s_Positions = {
				0.0f,  r, 0.0f,
				0.0f, -r, 0.0f
			};


			for (int y = 1; y < (precision / 2) + 1; y++) {
				for (int xz = 0; xz < precision; xz++) {
					Defaults::s_Positions.push_back(r * std::sin(std::numbers::pi / (precision / 2) * y) * std::sin(std::numbers::pi / (precision / 2) * xz));
					Defaults::s_Positions.push_back(r * std::cos(std::numbers::pi / (precision / 2) * y));
					Defaults::s_Positions.push_back(r * std::sin(std::numbers::pi / (precision / 2) * y) * std::cos(std::numbers::pi / (precision / 2) * xz));
				}
			}

			auto offset = 2;

			for (int i = 0; i < precision; i++) {
				Defaults::s_Indices.push_back(0);
				Defaults::s_Indices.push_back(offset + i);
				Defaults::s_Indices.push_back(offset + (i + 1) % precision);

			}
			for (int k = 0; k < precision; k++) {
				offset += precision;
				for (int i = 0; i < precision; i++) {
					Defaults::s_Indices.push_back(offset - precision + i);
					Defaults::s_Indices.push_back(offset + i);
					Defaults::s_Indices.push_back(offset + (i + 1) % precision);

					Defaults::s_Indices.push_back(offset + (i + 1) % precision);
					Defaults::s_Indices.push_back(offset - precision + (i + 1) % precision);
					Defaults::s_Indices.push_back(offset - precision + i);
				}
			}

			auto __size = Defaults::s_Positions.size() - 1;
			offset += precision;
			for (int i = 0; i < precision; i++) {
				Defaults::s_Indices.push_back(1);
				Defaults::s_Indices.push_back(offset - precision + (i + 1) % precision);
				Defaults::s_Indices.push_back(offset - precision + i);
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
		std::cout << "Sphere::" << ((uint64_t)this) << " is created." << std::endl;
	}
}


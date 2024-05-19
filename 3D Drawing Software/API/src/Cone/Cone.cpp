#include "Cone.h"
#include <numbers>

dra::Cone::Cone(int precision, Object* parent) : Shape(parent)
{
	ConstructDefaults(precision);
}

dra::Cone::~Cone()
{
	std::cout << "Cone::" << ((uint64_t)this) << " is destroyed." << std::endl;
}

void dra::Cone::Update()
{
}

void dra::Cone::Draw(Camera* camera)
{
	if (auto t = ShaderArena::Instance().GetShader("LineShader"); t.has_value()) {
		auto& shader = t.value();
		shader->Bind();
		shader->SetUniform4f("u_Color", 0.40f, 0.70f, 0.30f, 1.0f);

		shader->SetUniformMat4f("u_MVP", camera->GetProjection() * glm::inverse(camera->GetView()) * m_Transform.GetWorldAsMat4f());
		m_VAO->Bind();
		m_IndexBuffer->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}

void dra::Cone::ConstructDefaults(int precision)
{
	if (!Defaults::s_IsSet) {

		float r = 0.5f;

		Defaults::s_Positions = {
			0.0f,  r, 0.0f,
			0.0f, -r, 0.0f
		};

		for (int i = 0; i < precision; i++) {
			Defaults::s_Positions.push_back(r * std::cos(i * 2 * std::numbers::pi / precision));
			Defaults::s_Positions.push_back(-r);
			Defaults::s_Positions.push_back(r * std::sin(i * 2 * std::numbers::pi / precision));
		}

		for (int i = 0; i < precision + 1; i++) {
			Defaults::s_Indices.push_back(1);
			Defaults::s_Indices.push_back(2 + i);
			Defaults::s_Indices.push_back(2 + (i + 1) % precision);

			Defaults::s_Indices.push_back(0);
			Defaults::s_Indices.push_back(2 + precision - i - 1);
			Defaults::s_Indices.push_back(2 + precision - ((i + 1) % precision) - 1);
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
	std::cout << "Cone::" << ((uint64_t)this) << " is created." << std::endl;
}

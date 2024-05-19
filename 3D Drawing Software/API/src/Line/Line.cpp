#include "Line.h"
#include <iostream>
#include <numbers>

namespace dra {
	Line::Line(Object* parent)
		: Shape(parent)
	{
		Construct();
	}

	/*Line::Line(glm::vec3 start_location, glm::vec3 end_location, Object* parent)
	{
		Construct();
		glm::vec3 temp((end_location.x - start_location.x) / 2, (end_location.y - start_location.y) / 2, (end_location.z - start_location.z) / 2);
		glm::vec3 angles(atan(temp.y / temp.z), -atan(temp.z / temp.x), atan(temp.y / temp.x));
		glm::vec3 temp2(start_location.x + temp.x, start_location.y + temp.y, start_location.z + temp.z);

		m_Transform.SetLocalPosition(temp2.x, temp2.y, temp2.z);
		m_Transform.Rotate(angles.x * 180 / std::numbers::pi, angles.y * 180 / std::numbers::pi, angles.z * 180 / std::numbers::pi);

		float len = sqrt(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
		m_Transform.SetLocalScale(len * 2, 1.0f, 1.0f);
	}

	Line::Line(glm::vec3 start_location, glm::vec3 axis, float length, Object* parent)
	{
	}*/

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
			glm::mat4 res = camera->GetProjection() * glm::inverse(camera->GetView()) * m_Transform.GetWorldAsMat4f();
			shader->SetUniformMat4f("u_MVP", res);
			m_VAO->Bind();
			m_IndexBuffer->Bind();

			GLCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
		}
	}
	void Line::Construct()
	{
		if (!Defaults::s_IsSet) {

			Defaults::s_Positions = { -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f };
			float r = 0.02f;

			glm::vec3 rotvec(-0.5f, 0.00f, 0.00f);

			for (int i = 0; i < 12; i++) {
				Defaults::s_Positions.push_back(rotvec.x);
				Defaults::s_Positions.push_back(rotvec.y + r * std::sin(std::numbers::pi / 6 * i));
				Defaults::s_Positions.push_back(rotvec.z + r * std::cos(std::numbers::pi / 6 * i));

				Defaults::s_Indices.push_back(0);
				Defaults::s_Indices.push_back(2 + i);
				Defaults::s_Indices.push_back(2 + (i + 1) % 12);
			}

			rotvec = glm::vec3(0.5f, 0.00f, 0.0f);

			for (int i = 0; i < 12; i++) {
				Defaults::s_Positions.push_back(rotvec.x);
				Defaults::s_Positions.push_back(rotvec.y + r * std::sin(std::numbers::pi / 6 * i));
				Defaults::s_Positions.push_back(rotvec.z + r * std::cos(std::numbers::pi / 6 * i));

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
}
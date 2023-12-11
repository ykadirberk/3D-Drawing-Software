#include "Vertex.h"

namespace dra {
	Vertex::Vertex() : m_Center(0.0f) {
		auto t = ShaderArena::Instance().GetShader("VertexSphereShader");
		if (!t.has_value()) {
			ShaderArena::Instance().LoadShader("VertexSphereShader", "shaders/vertexsphere.shader");
		}

		float radius = 0.1;
		int density = 10;
		const float pi = std::acos(-1);
		

		m_Positions.push_back(0.0f);
		m_Positions.push_back(1.0f * radius);
		m_Positions.push_back(0.0f);

		// generate vertices per stack / slice
		for (int i = 0; i < density - 1; i++) {
			auto phi = pi * double(i + 1) / double(density);
			for (int j = 0; j < density; j++) {
				auto theta = 2.0 * pi * double(j) / double(density);
				auto x = std::sin(phi) * std::cos(theta);
				auto y = std::cos(phi);
				auto z = std::sin(phi) * std::sin(theta);
				m_Positions.push_back(x * radius);
				m_Positions.push_back(y * radius);
				m_Positions.push_back(z * radius);
			}
		}

		// add bottom vertex
		//auto v1 = mesh.add_vertex(Point(0, -1, 0));
		m_Positions.push_back(0.0f);
		m_Positions.push_back(-1.0f * radius);
		m_Positions.push_back(0.0f);



		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(m_Positions.data(), m_Positions.size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size());
	}

	Vertex::~Vertex() {
		
	}

	[[nodiscard]] glm::vec3 Vertex::GetPosition() const noexcept {
		return m_Center;
	}
}
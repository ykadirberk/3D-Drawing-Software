#include "PolygonalSurface.h"

dra::PolygonalSurface::PolygonalSurface(std::vector<glm::vec2> polygon_edges, float thickness) : Shape(nullptr)
{
	ConstructSurface(polygon_edges, thickness);
}

dra::PolygonalSurface::PolygonalSurface(std::vector<glm::vec2> polygon_edges, float thickness, Object* parent) : Shape(parent)
{
	ConstructSurface(polygon_edges, thickness);
}

dra::PolygonalSurface::~PolygonalSurface()
{
	std::cout << "PolygonalSurface::" << ((uint64_t)this) << " is destroyed." << std::endl;
}

void dra::PolygonalSurface::Update()
{
}

void dra::PolygonalSurface::Draw(Camera* camera)
{
	if (auto t = ShaderArena::Instance().GetShader("LineShader"); t.has_value()) {
		auto& shader = t.value();
		shader->Bind();
		shader->SetUniform4f("u_Color", 0.45f, 0.15f, 0.70f, 1.0f);
		glm::mat4 res = camera->GetProjection() * glm::inverse(camera->GetView()) * m_Transform.GetWorldAsMat4f();
		shader->SetUniformMat4f("u_MVP", res);
		m_VAO->Bind();
		m_IndexBuffer->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}

void dra::PolygonalSurface::ConstructSurface(std::vector<glm::vec2>& polygon_edges, float thickness)
{
	m_Positions.push_back(0.0f);
	m_Positions.push_back(0.0f);
	m_Positions.push_back(-thickness/2);

	m_Positions.push_back(0.0f);
	m_Positions.push_back(0.0f);
	m_Positions.push_back(thickness / 2);

	for (auto& point : polygon_edges) {
		m_Positions.push_back(point.x);
		m_Positions.push_back(point.y);
		m_Positions.push_back(-thickness / 2);
	}

	for (auto& point : polygon_edges) {
		m_Positions.push_back(point.x);
		m_Positions.push_back(point.y);
		m_Positions.push_back(thickness / 2);
	}

	int offset = 2;

	for (int i = 0; i < polygon_edges.size(); i++) {
		m_Indices.push_back(0);
		m_Indices.push_back(offset + ((i + 1) % polygon_edges.size()));
		m_Indices.push_back(offset + i);
	}

	offset += polygon_edges.size();

	for (int i = 0; i < polygon_edges.size(); i++) {
		m_Indices.push_back(1);
		m_Indices.push_back(offset + i);
		m_Indices.push_back(offset + ((i + 1) % polygon_edges.size()));
	}

	for (int i = 0; i < polygon_edges.size(); i++) {
		m_Indices.push_back(2 + i);
		m_Indices.push_back(offset + ((i + 1) % polygon_edges.size()));
		m_Indices.push_back(offset + i);

		m_Indices.push_back(2 + ((i + 1) % polygon_edges.size()));
		m_Indices.push_back(offset + ((i + 1) % polygon_edges.size()));
		m_Indices.push_back(2 + i);
		
	}

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
	std::cout << "PolygonalSurface::" << ((uint64_t)this) << " is created." << std::endl;
}

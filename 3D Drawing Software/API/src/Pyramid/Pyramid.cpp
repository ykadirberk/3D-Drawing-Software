#include "Pyramid.h"

#include "../Line/Line.h"
#include "../Point/Point.h"
#include "../PolygonalSurface/PolygonalSurface.h"

dra::Pyramid::Pyramid(Object* parent) : Shape(parent)
{
	Construct();
}

dra::Pyramid::~Pyramid()
{
}

void dra::Pyramid::Update()
{
}

void dra::Pyramid::Draw(Camera* camera)
{
	for (auto& s : m_Shapes) {
		s->Draw(camera);
	}
}

void dra::Pyramid::Construct()
{
	m_Transform = Transform(this);

	// lines 
	m_Shapes.push_back(std::make_shared<Line>(this));
	std::shared_ptr<Shape> temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.5f, 0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.5f, -0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, -0.5f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, -0.5f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.25f, -0.15f, 0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, 45.0f, 45.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.25f, -0.15f, -0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, 45.0f, -45.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.25f, -0.15f, -0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, -45.0f, 45.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.25f, -0.15f, 0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, -45.0f, -45.0f);

	// points
	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, -0.5f, 0.5f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, -0.5f, 0.5f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, -0.5f, -0.5f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, -0.5f, -0.5f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.2f, 0.0f);
	
	// Polygonal Surfaces

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {-0.5f, -0.5f}, { 0.5f, -0.5f }, { 0.5f,  0.5f }, { -0.5f,  0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.5f, 0.0f);
	temp->GetTransform().Rotate(90.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {0.0f, 0.366f}, { -0.5f,  -0.5f } ,{ 0.5f, -0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.10f, 0.214f);
	temp->GetTransform().Rotate(-35.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {0.0f, 0.366f}, { -0.5f,  -0.5f }, { 0.5f, -0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.10f, -0.214f);
	temp->GetTransform().Rotate(35.0f, 0.0f, 0.0f);
	 
	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {0.0f, 0.366f}, { -0.5f,  -0.5f }, { 0.5f, -0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.214f, -0.10f, 0.0f);
	temp->GetTransform().Rotate(35.0f, -90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {0.0f, 0.366f}, { -0.5f,  -0.5f }, { 0.5f, -0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.214f, -0.10f, 0.0f);
	temp->GetTransform().Rotate(35.0f, 90.0f, 0.0f);

}

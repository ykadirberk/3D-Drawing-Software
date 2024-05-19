#include "Cube.h"

#include "../Line/Line.h"
#include "../Point/Point.h"
#include "../PolygonalSurface/PolygonalSurface.h"

dra::Cube::Cube() : Shape(nullptr)
{
	Construct();
}

dra::Cube::Cube(Object* parent) : Shape(parent)
{
	Construct(); 
}

dra::Cube::~Cube()
{

}

void dra::Cube::Update()
{

}

void dra::Cube::Draw(Camera* camera)
{
	for (auto& s : m_Shapes) {
		s->Draw(camera);
	}
}

void dra::Cube::Construct()
{
	m_Transform = Transform(this);
	// front lines
	m_Shapes.push_back(std::make_shared<Line>(this));
	std::shared_ptr<Shape> temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.5f, 0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.5f, 0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, 0.0f, 0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 90.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, 0.0f, 0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 90.0f);

	// back lines
	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.5f, -0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.5f, -0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, 0.0f, -0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 90.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, 0.0f, -0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 90.0f);


	// side lines
	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, 0.5f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, -0.5f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, 0.5f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, -0.5f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	// points
	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, 0.5f, -0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, 0.5f, 0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, -0.5f, -0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, -0.5f, 0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, 0.5f, -0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, 0.5f, 0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, -0.5f, -0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Point>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, -0.5f, 0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	// Surfaces

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {-0.5f, -0.5f}, { 0.5f, -0.5f}, { 0.5f,  0.5f}, {-0.5f,  0.5f} }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.0f, 0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {-0.5f, -0.5f}, { 0.5f, -0.5f }, { 0.5f,  0.5f }, { -0.5f,  0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.0f, -0.5f);
	temp->GetTransform().Rotate(0.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {-0.5f, -0.5f}, { 0.5f, -0.5f }, { 0.5f,  0.5f }, { -0.5f,  0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, 0.0f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {-0.5f, -0.5f}, { 0.5f, -0.5f }, { 0.5f,  0.5f }, { -0.5f,  0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, 0.0f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {-0.5f, -0.5f}, { 0.5f, -0.5f }, { 0.5f,  0.5f }, { -0.5f,  0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.5f, 0.0f);
	temp->GetTransform().Rotate(90.0f, 0.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<PolygonalSurface>(std::vector<glm::vec2>{ {-0.5f, -0.5f}, { 0.5f, -0.5f }, { 0.5f,  0.5f }, { -0.5f,  0.5f } }, 0.025f, this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, -0.5f, 0.0f);
	temp->GetTransform().Rotate(90.0f, 0.0f, 0.0f);
}

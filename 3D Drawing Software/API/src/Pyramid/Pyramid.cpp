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
	// front lines
	m_Shapes.push_back(std::make_shared<Line>(this));
	std::shared_ptr<Shape> temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.0f, 0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.0f, 0.0f, -0.5f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.5f, 0.0f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.5f, 0.0f, 0.0f);
	temp->GetTransform().Rotate(0.0f, 90.0f, 0.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.25f, 0.35f, 0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, 45.0f, 45.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.25f, 0.35f, -0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, 45.0f, -45.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(-0.25f, 0.35f, -0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, -45.0f, 45.0f);

	m_Shapes.push_back(std::make_shared<Line>(this));
	temp = *(--m_Shapes.end());
	temp->GetTransform().SetLocalPosition(0.25f, 0.35f, 0.25f);
	temp->GetTransform().SetLocalRotation(0.0f, -45.0f, -45.0f);
}

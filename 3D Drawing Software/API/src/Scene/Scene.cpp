#include "Scene.h"

#include "../PerspectiveCamera/PerspectiveCamera.h"

dra::Scene::Scene()
{
	m_focusPoint = std::make_shared<Object>();
	m_focusPoint->GetTransform().Translate(0.0f, 0.5f, 0.0f);
	SetProjectionCamera(45.0f, 960.0f ,540.0f);
}

dra::Scene::~Scene()
{
}

void dra::Scene::SetCamera(std::shared_ptr<Camera> camera, float focus_x, float focus_y, float focus_z)
{

}

void dra::Scene::SetProjectionCamera(float field_of_view, float width, float height)
{
	m_MainCamera = std::make_shared<dra::PerspectiveCamera>(field_of_view, width, height, nullptr);
	m_MainCamera->GetTransform().Translate(0.0f, 0.5f, 3.0f);
	m_MainCamera->SetParent(m_focusPoint.get());
}

void dra::Scene::SetOrthogonalCamera(float width, float height)
{
}

void dra::Scene::InsertUpdateFunction(std::function<void()> t)
{
	m_Updates.push_back(t);
}

void dra::Scene::InsertRenderFunction(std::function<void(Camera*)> t)
{
	m_Renders.push_back(t);
}

void dra::Scene::RotateMainCameraAroundFocus(float x, float y, float z)
{
	m_focusPoint->GetTransform().Rotate(x, y, z);
}

void dra::Scene::ZoomMainCamera(float zoom_amount)
{
	m_MainCamera->GetTransform().Translate(0.0f, 0.0f, -zoom_amount);
	std::cout << m_MainCamera->GetTransform().GetLocalPosition().z << std::endl;
}

void dra::Scene::RunUpdates() const
{
	for (auto& func : m_Updates) {
		func();
	}
}

void dra::Scene::RunRenders() const
{
	for (auto& func : m_Renders) {
		func(m_MainCamera.get());
	}
}

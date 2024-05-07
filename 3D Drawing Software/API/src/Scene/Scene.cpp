#include "Scene.h"

#include "../PerspectiveCamera/PerspectiveCamera.h"
#include "../OrthogonalCamera/OrthogonalCamera.h"

dra::Scene::Scene()
{
	m_focusPoint = std::make_shared<Object>();
	m_focusPoint->GetTransform().Translate(0.0f, 0.5f, 0.0f);
	SetProjectionCamera(45.0f, 960.0f ,540.0f);
	//SetOrthogonalCamera(960.0f, 540.0f);
}

dra::Scene::~Scene()
{
}

void dra::Scene::SetCamera(std::shared_ptr<Camera> camera, float focus_x, float focus_y, float focus_z)
{

}

void dra::Scene::SetProjectionCamera(float field_of_view, float width, float height)
{
	m_ScreenWidth = width;
	m_ScreenHeight = height;
	m_MainCamera = std::make_shared<dra::PerspectiveCamera>(field_of_view, width, height, nullptr);
	m_MainCamera->GetTransform().Translate(0.0f, 0.5f, 3.0f);
	m_MainCamera->SetParent(m_focusPoint.get());
}

void dra::Scene::SetOrthogonalCamera(float width, float height)
{
	m_ScreenWidth = width;
	m_ScreenHeight = height;
	m_MainCamera = std::make_shared<dra::OrthogonalCamera>(width, height, nullptr);
	m_MainCamera->GetTransform().Translate(0.0f, 0.5f, 3.0f);
	m_MainCamera->SetParent(m_focusPoint.get());
}

void dra::Scene::InsertUpdateFunction(std::function<void()> t)
{
	m_Updates.push_back(t);
}

void dra::Scene::InsertRenderFunction(std::function<void(Camera*)> t)
{
	m_Renders.push_back(t);
}

void dra::Scene::SendMousePosition(float x, float y) {
	m_PrevMousePositionX = m_MousePositionX;
	m_PrevMousePositionY = m_MousePositionY;
	m_MousePositionX = x;
	m_MousePositionY = y;
}

void dra::Scene::RotateMainCameraAroundFocus() {
	auto t = m_MainCamera->GetTransform().GetLocalPosition();
	m_focusPoint->GetTransform().Rotate(-(m_MousePositionY - m_PrevMousePositionY) / 15.0f * std::log2f(t.z), -(m_MousePositionX - m_PrevMousePositionX) / 15.0f * std::log2f(t.z), 0.0f);
	auto loc_rot = m_focusPoint->GetTransform().GetLocalRotation();
	if (loc_rot.x > 90.0f) {
		m_focusPoint->GetTransform().SetLocalRotation(90.0f, loc_rot.y, loc_rot.z);
	}  
	if (loc_rot.x < -90.0f) {
		m_focusPoint->GetTransform().SetLocalRotation(-90.0f, loc_rot.y, loc_rot.z);
	}
}

void dra::Scene::ZoomMainCamera(float zoom_direction)
{
	/*if (zoom_amount != 0) {
		std::cout << zoom_amount << std::endl;
		auto t = m_MainCamera->GetTransform().GetLocalPosition();
		std::cout << "x: " << t.x << ", y: " << t.y << ", z: " << t.z << std::endl;
	}*/



	if (zoom_direction < 0) {
		auto t = m_MainCamera->GetTransform().GetLocalPosition();
		m_MainCamera->GetTransform().Translate(0.0f, 0.0f, t.z / 19.0f * 20.0f - t.z);
	}

	if (zoom_direction > 0) {
		auto t = m_MainCamera->GetTransform().GetLocalPosition();
		m_MainCamera->GetTransform().Translate(0.0f, 0.0f, -t.z / 20.0f);
	}

	if (auto t = m_MainCamera->GetTransform().GetLocalPosition(); t.z < 1.11f) {
		m_MainCamera->GetTransform().SetLocalPosition(t.x, t.y, 1.11f);
	}

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
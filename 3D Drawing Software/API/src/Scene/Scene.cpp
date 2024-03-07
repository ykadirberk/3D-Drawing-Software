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

void dra::Scene::RotateMainCameraAroundFocus()
{
	glm::vec3 va = get_arcball_vector(m_PrevMousePositionX, m_PrevMousePositionY);
	glm::vec3 vb = get_arcball_vector(m_MousePositionX, m_MousePositionY);
	float angle = acos(glm::min(1.0f, glm::dot(va, vb)));
	glm::vec3 axis_in_camera_coord = glm::cross(va, vb);

	m_focusPoint->GetTransform().Rotate(-axis_in_camera_coord.x * 100, -axis_in_camera_coord.y * 100, /*-axis_in_camera_coord.z * 100*/ 0.0f);
	auto loc_rot = m_focusPoint->GetTransform().GetLocalRotation();
	if (loc_rot.x > 90.0f) {
		m_focusPoint->GetTransform().SetLocalRotation(90.0f, loc_rot.y, loc_rot.z);
	}  
	if (loc_rot.x < -90.0f) {
		m_focusPoint->GetTransform().SetLocalRotation(-90.0f, loc_rot.y, loc_rot.z);
	}
}

void dra::Scene::ZoomMainCamera(float zoom_amount)
{
	m_MainCamera->GetTransform().Translate(0.0f, 0.0f, -zoom_amount);
	//std::cout << m_MainCamera->GetTransform().GetLocalPosition().z << std::endl;
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

glm::vec3 dra::Scene::get_arcball_vector(int x, int y)
{
	glm::vec3 P = glm::vec3(1.0 * x / m_ScreenWidth * 2 - 1.0,
		1.0 * y / m_ScreenHeight * 2 - 1.0,
		0);
	P.y = -P.y;
	float OP_squared = P.x * P.x + P.y * P.y;
	if (OP_squared <= 1 * 1)
		P.z = sqrt(1 * 1 - OP_squared);  // Pythagoras
	else
		P = glm::normalize(P);  // nearest point
	return P;
}

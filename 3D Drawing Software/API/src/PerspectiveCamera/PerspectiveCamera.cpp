#include "PerspectiveCamera.h"


namespace dra {
	PerspectiveCamera::PerspectiveCamera(float field_of_view, float width, float height, Object* parent)
	: m_Fov(field_of_view), m_Width(width), m_Height(height), Camera(parent)
	{
		m_Projection = glm::perspective(glm::radians(m_Fov), m_Width / m_Height, 0.1f, 100.0f);
	}

	PerspectiveCamera::~PerspectiveCamera() {

	}

	void PerspectiveCamera::SetFieldOfView(float fov) noexcept {
		m_Fov = fov;
		UpdateProjection();
	}

	void PerspectiveCamera::SetResolution(float width, float height) noexcept {
		m_Width = width;
		m_Height = height;
		UpdateProjection();
	}

	[[nodiscard]] glm::mat4 PerspectiveCamera::GetProjection() const noexcept
	{
		return m_Projection;
	}

	[[nodiscard]] glm::mat4 PerspectiveCamera::GetView() const noexcept
	{
		return m_Transform.GetWorldAsMat4f();
	}

	[[nodiscard]] glm::mat4 PerspectiveCamera::GetProjectionXView() const noexcept {
		return m_Projection * m_Transform.GetWorldAsMat4f();
	}

	[[nodiscard]] Transform& PerspectiveCamera::GetTransform() noexcept {
		return m_Transform;
	}

	
	void PerspectiveCamera::UpdateProjection() noexcept {
		m_Projection = glm::perspective(glm::radians(m_Fov), m_Width / m_Height, 0.1f, 100.0f);
	}
}
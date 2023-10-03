#include "PerspectiveCamera.h"


namespace dra {
	PerspectiveCamera::PerspectiveCamera(float field_of_view, float width, float height)
	: m_Fov(field_of_view), m_Width(width), m_Height(height)
	{
		m_Projection = glm::perspective(glm::radians(m_Fov), m_Width / m_Height, 0.1f, 100.0f);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
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

	[[nodiscard]] glm::mat4 PerspectiveCamera::GetPxV() const noexcept
	{
		return m_Projection * m_View;
	}

	[[nodiscard]] glm::mat4 PerspectiveCamera::GetVxP() const noexcept
	{
		return m_View * m_Projection;
	}
	
	void PerspectiveCamera::UpdateProjection() noexcept {
		m_Projection = glm::perspective(glm::radians(m_Fov), m_Width / m_Height, 0.1f, 100.0f);
	}
}
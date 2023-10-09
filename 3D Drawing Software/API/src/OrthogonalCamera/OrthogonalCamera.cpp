#include "OrthogonalCamera.h"
#include "../ext/glm/gtc/matrix_transform.hpp"

namespace dra { 
	OrthogonalCamera::OrthogonalCamera(float width, float height, Object* parent) 
		: Camera(parent), m_Width(width), m_Height(height) {
		m_Projection = glm::ortho(-m_Width/ m_Height, m_Width/ m_Height, -m_Height/ m_Height, m_Height/ m_Height, 0.0f, 1000.0f);
	}
	OrthogonalCamera::~OrthogonalCamera()
	{
	}
	void OrthogonalCamera::SetResolution(float width, float height)
	{
		m_Width = width;
		m_Height = height;
		UpdateProjection();
	}
	glm::mat4 OrthogonalCamera::GetProjection() const noexcept
	{
		return m_Projection;
	}
	glm::mat4 OrthogonalCamera::GetView() const noexcept {
		return m_Transform.GetWorldAsMat4f(); 
	}
	void OrthogonalCamera::UpdateProjection() noexcept {
		m_Projection = glm::ortho(-m_Width / m_Height, m_Width / m_Height, -m_Height / m_Height, m_Height / m_Height, 0.0f, 1000.0f);
	}
}
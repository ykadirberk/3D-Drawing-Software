#include "PerspectiveCamera.h"


namespace dra {
	PerspectiveCamera::PerspectiveCamera(float field_of_view, float width, float height, Object* parent)
	: m_Fov(field_of_view), m_Width(width), m_Height(height), Camera(parent)
	{
		float m_Fova = m_Fov * 0.01745329251994329576923690768489;
		m_Projection = Matrix4<float>::Perspective(m_Fova, m_Width / m_Height, 0.1f, 100.0f);
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

	[[nodiscard]] Matrix4<float> PerspectiveCamera::GetProjection() const noexcept
	{
		return m_Projection;
	}

	[[nodiscard]] Matrix4<float> PerspectiveCamera::GetView() const noexcept
	{
		return m_Transform.GetWorldAsMat4f();
	}

	[[nodiscard]] Matrix4<float> PerspectiveCamera::GetProjectionXView() const noexcept {
		return m_Projection * m_Transform.GetWorldAsMat4f();
	}
	
	void PerspectiveCamera::UpdateProjection() noexcept {
		float m_Fova = m_Fov * 0.01745329251994329576923690768489;
		m_Projection = m_Projection.Perspective(m_Fova, m_Width / m_Height, 0.1f, 100.0f);
	}
}
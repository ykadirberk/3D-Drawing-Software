#pragma once
#include "../Core/DLLBuild.h"
#include "../Core/Mat4/Matrix4.h"

#include "../Camera/Camera.h"
#include "../Core/Transform/Transform.h"

namespace dra {
	class _API PerspectiveCamera : public Camera{
		public:
			PerspectiveCamera(float field_of_view, float width, float height, Object* parent);
			~PerspectiveCamera() override;

			void SetFieldOfView(float fov) noexcept;
			void SetResolution(float width, float height) noexcept;

			[[nodiscard]] Matrix4<float> GetProjection() const noexcept override;
			[[nodiscard]] Matrix4<float> GetView() const noexcept override;

			[[nodiscard]] Matrix4<float> GetProjectionXView() const noexcept;

		private:
			Matrix4<float> m_Projection;

			float m_Fov;
			float m_Width;
			float m_Height;

			void UpdateProjection() noexcept;
	};
}
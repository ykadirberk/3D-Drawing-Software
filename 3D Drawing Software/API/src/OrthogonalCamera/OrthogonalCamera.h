#pragma once
#include "../Core/DLLBuild.h"
#include "../Camera/Camera.h"
#include "../Core/Mat4/Matrix4.h"


namespace dra {
	class _API OrthogonalCamera : public Camera {
		public:
			OrthogonalCamera(float width, float height, Object* parent);
			~OrthogonalCamera();

			void SetResolution(float width, float height) override;

			[[nodiscard]] Matrix4<float> GetProjection() const noexcept override;
			[[nodiscard]] Matrix4<float> GetView() const noexcept override;

		private:
			Matrix4<float> m_Projection;

			float m_Width;
			float m_Height;

			void UpdateProjection() noexcept;
	};
}
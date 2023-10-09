#pragma once
#include "../Core/DLLBuild.h"
#include "../Camera/Camera.h"
#include "../ext/glm/glm.hpp"


namespace dra {
	class _API OrthogonalCamera : public Camera {
		public:
			OrthogonalCamera(float width, float height, Object* parent);
			~OrthogonalCamera();

			void SetResolution(float width, float height) override;

			[[nodiscard]] glm::mat4 GetProjection() const noexcept override;
			[[nodiscard]] glm::mat4 GetView() const noexcept override;

		private:
			glm::mat4 m_Projection;

			float m_Width;
			float m_Height;

			void UpdateProjection() noexcept;
	};
}
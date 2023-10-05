#pragma once
#include "../Core/DLLBuild.h"
#include "../ext/glm/glm.hpp"
#include "../ext/glm/gtc/matrix_transform.hpp"

#include "../Camera/Camera.h"
#include "../Core/Transform/Transform.h"

namespace dra {
	class _API PerspectiveCamera : public Camera{
		public:
			PerspectiveCamera(float field_of_view, float width, float height, Object* parent);
			~PerspectiveCamera() override;

			void SetFieldOfView(float fov) noexcept;
			void SetResolution(float width, float height) noexcept;

			[[nodiscard]] glm::mat4 GetProjection() const noexcept override;
			[[nodiscard]] glm::mat4 GetView() const noexcept override;

			[[nodiscard]] glm::mat4 GetProjectionXView() const noexcept;
			
			[[nodiscard]] Transform& GetTransform() noexcept;

		private:
			glm::mat4 m_Projection;

			float m_Fov;
			float m_Width;
			float m_Height;

			void UpdateProjection() noexcept;
	};
}
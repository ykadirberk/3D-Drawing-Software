#pragma once
#include "../Core/DLLBuild.h"
#include "../ext/glm/glm.hpp"
#include "../ext/glm/gtc/matrix_transform.hpp"

namespace dra {
	class _API PerspectiveCamera {
		public:
			PerspectiveCamera(float field_of_view, float width, float height);
			~PerspectiveCamera();

			void SetFieldOfView(float fov) noexcept;
			void SetResolution(float width, float height) noexcept;

			[[nodiscard]] glm::mat4 GetPxV() const noexcept;
			[[nodiscard]] glm::mat4 GetVxP() const noexcept;

		private:
			glm::mat4 m_Projection;
			glm::mat4 m_View;

			float m_Fov;
			float m_Width;
			float m_Height;

			void UpdateProjection() noexcept;
	};
}
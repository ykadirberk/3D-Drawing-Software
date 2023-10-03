#pragma once
#include "../Core/DLLBuild.h"
#include "../ext/glm/glm.hpp"

namespace dra {
	class _API Camera {
		public:
			Camera() {}
			virtual ~Camera() {}

			virtual void SetResolution(float width, float height) = 0;

			virtual glm::mat4 GetProjection() const noexcept = 0;
			virtual glm::mat4 GetView() const noexcept = 0;
	};
}

#pragma once
#include "../Core/DLLBuild.h"
#include "../ext/glm/glm.hpp"
#include "../Core/Object/Object.h"

namespace dra {
	class _API Camera : public Object {
		public:
			Camera(Object* parent) : Object(parent) {}
			virtual ~Camera() {}

			virtual void SetResolution(float width, float height) = 0;

			virtual glm::mat4 GetProjection() const noexcept = 0;
			virtual glm::mat4 GetView() const noexcept = 0;
	};
}

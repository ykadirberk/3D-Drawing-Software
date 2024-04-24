#pragma once
#include "../Core/DLLBuild.h"
#include "../Core/Mat4/Matrix4.h"
#include "../Core/Object/Object.h"

namespace dra {
	class _API Camera : public Object {
		public:
			Camera(Object* parent) : Object(parent) {}
			virtual ~Camera() {}

			virtual void SetResolution(float width, float height) = 0;

			virtual Matrix4<float> GetProjection() const noexcept = 0;
			virtual Matrix4<float> GetView() const noexcept = 0;
	};
}

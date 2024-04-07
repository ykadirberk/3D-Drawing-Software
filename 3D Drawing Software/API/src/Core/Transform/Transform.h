#pragma once

#include <memory>

#include "../DLLBuild.h"
#include "../../ext/glm/glm.hpp"
#include "../Vector/Vector.h"
#include "../Mat4/Matrix4.h"

namespace dra {

	class _API Object;

	class _API Transform {
		public:
			Transform();
			Transform(Object* owner);
			~Transform();
			
			void SetLocalPosition(float x, float y, float z) noexcept;
			void SetLocalRotation(float x, float y, float z) noexcept;
			void SetLocalScale(float x, float y, float z) noexcept;

			void Translate(float x, float y, float z) noexcept;
			void Rotate(float x, float y, float z) noexcept;

			[[nodiscard]] Vector<float> GetLocalPosition() const noexcept;
			[[nodiscard]] Vector<float> GetLocalRotation() const noexcept;
			[[nodiscard]] Vector<float> GetLocalScale() const noexcept;

			[[nodiscard]] Vector<float> GetWorldPosition() const noexcept;
			[[nodiscard]] Vector<float> GetWorldRotation() const noexcept;
			[[nodiscard]] Vector<float> GetWorldScale() const noexcept;

			[[nodiscard]] Matrix4<float> GetLocalAsMat4f() const noexcept;
			[[nodiscard]] Matrix4<float> GetWorldAsMat4f() const noexcept;


			
		private:
			Object* m_Owner;

			/*Vector m_Position;
			Vector m_Rotation;
			Vector m_Scale;*/

			Vector<float> m_Position;
			Vector<float> m_Rotation;
			Vector<float> m_Scale;

			[[nodiscard]] float Interval(float current, float min, float max) const noexcept;
			[[nodiscard]] Matrix4<float> AsMat4f() const noexcept;
			[[nodiscard]] Matrix4<float> ParentOrientationMat4f(Object* obj) const noexcept;
			[[nodiscard]] Vector<float> ParentOrientedRotationVec3f(Object* obj, Vector<float> current) const noexcept;
			
	};
}
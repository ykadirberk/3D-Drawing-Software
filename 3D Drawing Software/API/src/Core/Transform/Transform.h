#pragma once

#include <memory>

#include "../DLLBuild.h"
#include "../../ext/glm/glm.hpp"
#include "../Vector/Vector.h"

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

			[[nodiscard]] glm::vec3 GetLocalPosition() const noexcept;
			[[nodiscard]] glm::vec3 GetLocalRotation() const noexcept;
			[[nodiscard]] glm::vec3 GetLocalScale() const noexcept;

			[[nodiscard]] glm::vec3 GetWorldPosition() const noexcept;
			[[nodiscard]] glm::vec3 GetWorldRotation() const noexcept;
			[[nodiscard]] glm::vec3 GetWorldScale() const noexcept;

			[[nodiscard]] glm::mat4 GetLocalAsMat4f() const noexcept;
			[[nodiscard]] glm::mat4 GetWorldAsMat4f() const noexcept;


			
		private:
			Object* m_Owner;

			glm::vec3 m_Position;
			glm::vec3 m_Rotation;
			glm::vec3 m_Scale;

			/*Vector m_Position;
			Vector m_Rotation;
			Vector m_Scale;*/

			[[nodiscard]] float Interval(float current, float min, float max) const noexcept;
			[[nodiscard]] glm::mat4 AsMat4f() const noexcept;
			[[nodiscard]] glm::mat4 ParentOrientationMat4f(Object* obj) const noexcept;
			[[nodiscard]] glm::vec3 ParentOrientedRotationVec3f(Object* obj, glm::vec3 current) const noexcept;
			
	};
}
#pragma once

#include "../DLLBuild.h"

#include "../../ext/glm/glm.hpp"

namespace dra {
	class _API Transform {
		public:
			Transform();
			~Transform();

			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);
			void SetScale(float x, float y, float z);

			[[nodiscard]] glm::vec3 GetPosition() const noexcept;
			[[nodiscard]] glm::vec3 GetRotation() const noexcept;
			[[nodiscard]] glm::vec3 GetScale() const noexcept;

			[[nodiscard]] glm::mat4 GetAsMat4f() const noexcept;

		private:
			glm::vec3 m_Position;
			glm::vec3 m_Rotation;
			glm::vec3 m_Scale;
	};
}